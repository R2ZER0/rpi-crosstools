// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include <mgl2/mgl_cf.h>
#include <SDL.h>

static const char* PROP_TYPE = "linegraph";

// Plugin Init/Shutdown stuff
int Init() {
    return 1;
}

void Destroy() {
    return;
}

const char* GetPropTypeStr() {
    return PROP_TYPE;
}


// Our actual prop stuff
typedef struct prop_linegraph {
    HMGL graph;
    HMDT graph_data;
    
    SDL_Texture* texture;
} Prop_LineGraph;



void InitProp(Prop* prop) {
    Prop_LineGraph* plg = (Prop_LineGraph*) calloc(1, sizeof(Prop_LineGraph));
    
    plg->graph = NULL;
    plg->graph_data = NULL;
    plg->texture = NULL;
    
    prop->data = (void*) plg;
}


void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_LineGraph* plg = (Prop_LineGraph*) prop->data;
    
    int resize_graph = 0;
    int redraw_graph = 0;
    
    if((prop_changed & PROP_CHANGED_W) || (prop_changed & PROP_CHANGED_H)) {
        resize_graph = 1;
        redraw_graph = 1;
    }
    
    if(plg->graph != NULL) { mgl_delete_graph(plg->graph); }
    if(plg->graph_data != NULL) { mgl_delete_data(plg->graph_data); }
    if(plg->texture != NULL) { SDL_DestroyTexture(plg->texture); }
    
    plg->graph_data = mgl_create_data_size(100, 1, 1);
    //plg->graph_data = mgl_create_data();
    
    int i = 0;
    for(i = 0; i < 100; ++i) {
        mgl_data_set_value(plg->graph_data, 
            sin((double) i/2.0),
        i, 0, 0);
    }
    
    plg->graph = mgl_create_graph((int) prop->w, (int) prop->h);
    mgl_clf_str(plg->graph, "a{A5}");
    mgl_set_origin(plg->graph, 0., 0., 0.);
    mgl_plot(plg->graph, plg->graph_data, "", "");
    
    const unsigned char* bitmap = mgl_get_rgba(plg->graph);
    
    plg->texture = SDL_CreateTexture(renderer,
                                     SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     (int) prop->w, (int) prop->h);
    
    SDL_UpdateTexture(plg->texture, NULL, bitmap, ((int) prop->w)*4);
    
}


void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_LineGraph* plg = (Prop_LineGraph*) prop->data;
    
    if(plg->texture == NULL) { return; }
    
    SDL_Rect destrect;
    destrect.x = (int) prop->x;
    destrect.y = (int) prop->y;
    destrect.w = (int) prop->w;
    destrect.h = (int) prop->h;
    
    SDL_RenderCopy(renderer, plg->texture, NULL, &destrect);
}


void DestroyProp(Prop* prop) {
    Prop_LineGraph* plg = (Prop_LineGraph*) prop->data;
    
    mgl_delete_graph(plg->graph);
    mgl_delete_data(plg->graph_data);
    
    free(plg);
}

    