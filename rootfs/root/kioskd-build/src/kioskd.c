// Kioskd - A 3D(not yet) rendering daemon with JSON API

#include <stdlib.h>
#include <stdio.h>
#include "kioskd.h"
#include "graphics.h"
#include "propmanager.h"
#include "jsonrpc-c.h"
#include <ev.h>
#include <SDL_log.h>
#include <SDL.h>

struct kioskd {
    Graphics* gfx;
    PropManager* prm;
    
    struct jrpc_server rpc;
    
    struct ev_loop* loop;
    ev_timer render_timer;
    ev_signal sigint_handler;
};

static void RegisterRPCProcs(Kioskd* kioskd);
static void on_render(EV_P_ ev_timer *w, int revents);
static void on_sigint(EV_P_ ev_signal *w, int revents);

Kioskd* InitKioskd(int server_port, double render_interval) {
    Kioskd* kioskd = (Kioskd*) calloc(1, sizeof(Kioskd));
    
    kioskd->loop = EV_DEFAULT;
    
    SDL_Log("Using render interval %f", render_interval);
    ev_timer_init(&(kioskd->render_timer), &on_render, render_interval, render_interval);
    kioskd->render_timer.data = (void*) kioskd;
    
    ev_signal_init(&(kioskd->sigint_handler), on_sigint, SIGINT);
    kioskd->sigint_handler.data = (void*) kioskd;
    
    kioskd->gfx = InitGraphics();
    ClearScreen(kioskd->gfx);
    
    jrpc_server_init_with_ev_loop(&kioskd->rpc, server_port, kioskd->loop);
    RegisterRPCProcs(kioskd);
    
    kioskd->prm = InitPropManager();
    if(!LoadPropPlugin(kioskd->prm, "prop_generic")) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load prop_generic!");
    }
    if(!LoadPropPlugin(kioskd->prm, "prop_text") ){
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load prop_text!");
    }
    if(!LoadPropPlugin(kioskd->prm, "prop_image") ){
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load prop_image!");
    }
    
    return kioskd;
}

void RunKioskd(Kioskd* kioskd) {
    ev_timer_start(kioskd->loop, &(kioskd->render_timer));
    ev_signal_start(kioskd->loop, &(kioskd->sigint_handler));
    ev_run(kioskd->loop, 0);
}

void DestroyKioskd(Kioskd* kioskd) {
    DestroyPropManager(kioskd->prm);
    DestroyGraphics(kioskd->gfx);
    jrpc_server_destroy(&kioskd->rpc);
    free(kioskd);
}

void RenderFrame(Kioskd* kioskd) {
    //SDL_Log("Begin Render @ %d", SDL_GetTicks());
    
    SDL_Renderer* renderer = GetRenderer(kioskd->gfx);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    Prop* prop = GetFirstProp(kioskd->prm);
    while(prop != NULL) {
        prop->type->RenderProp(prop, renderer);
        prop = prop->next;
    }
    
    //SDL_Log("Present Render @ %d", SDL_GetTicks());
    SDL_RenderPresent(renderer);
    //SDL_Log("Finish Render @ %d", SDL_GetTicks());
}

static void on_render(EV_P_ ev_timer *w, int revents) {
    Kioskd* kioskd = (Kioskd*) w->data;
    
    RenderFrame(kioskd);
}

static void on_sigint(EV_P_ ev_signal *w, int revents) {
    Kioskd* kioskd = (Kioskd*) w->data;
    
    ev_break(kioskd->loop, EVBREAK_ALL);
}

///////////// rpc methods ////////////////////

static cJSON* rpc_Hello(jrpc_context* ctx, cJSON* params, cJSON* id) {
    return cJSON_CreateString("Hello!");
}

static cJSON* rpc_ExitKiosk(jrpc_context* ctx, cJSON* params, cJSON* id) {
    Kioskd* kioskd = (Kioskd*) ctx->data;
    
    ev_break(kioskd->loop, EVBREAK_ALL);
    return cJSON_CreateString("Bye!");
}

static cJSON* rpc_Update(jrpc_context* ctx, cJSON* params, cJSON* id) {
    Kioskd* kioskd = (Kioskd*) ctx->data;
    
    int prop_changed = 0;
    
    if(params->type != cJSON_Object) {
        ctx->error_code = -43;
        ctx->error_message = "Update requires a prop object.";
        return NULL;
    }
    
    cJSON* name_node = cJSON_GetObjectItem(params, "name");
    if(!name_node) {
        ctx->error_code = -44;
        ctx->error_message = "Update requires a prop name.";
        return NULL;
    }
    
    cJSON* type_node = cJSON_GetObjectItem(params, "type");
    if(!type_node) {
        ctx->error_code = -45;
        ctx->error_message = "Update requires a prop type.";
        return NULL;
    }
    
    Prop* prop = GetProp(kioskd->prm, type_node->valuestring, name_node->valuestring);
    if(!prop) {
        ctx->error_code = -46;
        ctx->error_message = "Could not create prop.";
        return NULL;
    }
    
    cJSON* x_node = cJSON_GetObjectItem(params, "x");
    if(x_node != NULL && prop->x != x_node->valuedouble) {
        prop->x = x_node->valuedouble;
        prop_changed |= PROP_CHANGED_X;
    }
    
    cJSON* y_node = cJSON_GetObjectItem(params, "y");
    if(y_node != NULL && prop->y != y_node->valuedouble) {
        prop->y = y_node->valuedouble;
        prop_changed |= PROP_CHANGED_Y;
    }
    
    cJSON* w_node = cJSON_GetObjectItem(params, "w");
    if(w_node != NULL && prop->w != w_node->valuedouble) {
        prop->w = w_node->valuedouble;
        prop_changed |= PROP_CHANGED_W;
    }
    
    cJSON* h_node = cJSON_GetObjectItem(params, "h");
    if(h_node != NULL && prop->h != h_node->valuedouble) {
        prop->h = h_node->valuedouble;
        prop_changed |= PROP_CHANGED_H;
    }
    
    prop->type->UpdateProp(prop, params, GetRenderer(kioskd->gfx), prop_changed);
    
    return cJSON_CreateString("Done");
}

static cJSON* rpc_Destroy(jrpc_context* ctx, cJSON* params, cJSON* id) {
    Kioskd* kioskd = (Kioskd*) ctx->data;
    
    if(params->type != cJSON_Object) {
        ctx->error_code = -43;
        ctx->error_message = "Destroy requires a prop object.";
        return cJSON_CreateNull();
    }
    
    cJSON* name_node = cJSON_GetObjectItem(params, "name");
    if(!name_node) {
        ctx->error_code = -44;
        ctx->error_message = "Destroy requires a prop name.";
        return cJSON_CreateNull();
    }
    
    cJSON* type_node = cJSON_GetObjectItem(params, "type");
    if(!type_node) {
        ctx->error_code = -45;
        ctx->error_message = "Destroy requires a prop type.";
        return cJSON_CreateNull();
    }
    
    Prop* prop = GetProp(kioskd->prm, type_node->valuestring, name_node->valuestring);
    UnlinkProp(kioskd->prm, prop);
    
    return cJSON_CreateString("Done");
}

static void RegisterRPCProcs(Kioskd* kioskd) {
#define RegisterProc( procname ) jrpc_register_procedure(&kioskd->rpc, rpc_ ## procname, #procname, kioskd )
    RegisterProc( Hello );
    RegisterProc( ExitKiosk );
    RegisterProc( Update );
    RegisterProc( Destroy );
}
