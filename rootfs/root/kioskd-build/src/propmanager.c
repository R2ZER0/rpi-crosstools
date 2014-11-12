#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "propmanager.h"
#include <SDL_loadso.h>
#include <SDL_render.h>
#include <cJSON.h>
#include <SDL_assert.h>
#include <SDL_log.h>
#include "graphics.h"

struct propmanager {
    Prop* props;
    PropType* types;
};

// Helper functions
static Prop* _CreateProp(PropManager* prm, const char* type, const char* name);
static void _DestroyProp(Prop* prop);
static Prop* _TryFindProp(PropManager* prm, PropType* type, const char* name);
static PropType* _GetPropType(PropManager* prm, const char* type);

PropManager* InitPropManager() {
    PropManager* prm = (PropManager*) calloc(1, sizeof(PropManager));
    
    prm->props = NULL;
    
    return prm;
}

void DestroyPropManager(PropManager* prm) {
    
    PropType* ptype = prm->types;
    while(ptype != NULL) {
        ptype->Destroy();
        
        PropType* next_ptype = ptype->next;
        free(ptype);
        
        ptype = next_ptype;
    }
    
    Prop* prop = prm->props;
    while(prop != NULL) {
        Prop* next_prop = prop->next;
        _DestroyProp(prop);
        prop = next_prop;
    }
    
    free(prm);
}

Prop* GetProp(PropManager* prm, const char* type, const char* name) {
    Prop* prop = _TryFindProp(prm, _GetPropType(prm, type), name);
    
    if(prop == NULL) {
        prop = _CreateProp(prm, type, name);
        if(prop == NULL) {
            fprintf(stderr, "Could not create prop %s of type %s \n", name, type);
            return NULL;
        }
        prop->next = prm->props;
        prm->props = prop;
    }
    
    return prop;
}

Prop* GetFirstProp(PropManager* prm) {
    return prm->props;
}

void UnlinkProp(PropManager* prm, Prop* prop) {
    Prop* props_prev = GetFirstProp(prm);
    Prop* props_next = props_prev->next;
    
    if(props_prev == prop && props_prev != NULL) {
        prm->props = props_next;
        
        _DestroyProp(props_prev);
        
        return;
        
    } else {
    
        while(props_next != prop && props_next != NULL) {
            props_prev = props_prev->next;
            props_next = props_next->next;
        }
    
        if(props_next != NULL) {
        
            props_prev->next = props_next->next;
        
            _DestroyProp(props_next);
            
            return;
        }
    }

    fprintf(stderr, "Couldn't Unlink prop %s %s %d \n", prop->type->GetPropTypeStr(), prop->name, prop);
}

int LoadPropPlugin(PropManager* prm, const char* plugin_name) {
    
    char* plugin_filename = (char*) calloc(strlen(plugin_name)+1+6, sizeof(char));
    strcpy(plugin_filename, "lib");
    strcat(plugin_filename, plugin_name);
    strcat(plugin_filename, ".so");
    
    // first check for plugin in cwd
    void* plugin = SDL_LoadObject(plugin_filename);
    
    //otherwise check in PROP_PLUGIN_PATH
    char* prop_plugin_path = getenv("PROP_PLUGIN_PATH");
    
    if(prop_plugin_path != NULL) {
        prop_plugin_path = strdup(prop_plugin_path);
        char* cur_path = prop_plugin_path;
        char* p = NULL;
        
        while(plugin == NULL) { 
            p = strchr(cur_path, ':');
            if(p != NULL) { p[0] = 0; }
            
            // Put together the full filepath
            int path_len = strlen(cur_path);
            char* full_path = (char*) calloc(path_len + strlen(plugin_filename) + 2, sizeof(char));
            
            strcpy(full_path, cur_path);
            if(full_path[path_len-1] != '/') { full_path[path_len] = '/'; }
            strcat(full_path, plugin_filename);

            plugin = SDL_LoadObject(full_path);
            
            
            if(plugin == NULL) {
                SDL_Log("Failed to load plugin %s : %s", full_path, SDL_GetError());
            }
            
            free(full_path);
            
            cur_path = p + 1;
            if(p == NULL) { break; }
        }
        
        free(prop_plugin_path);
    }
    
    if(plugin == NULL) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load plugin %s: Not found.", plugin_name);
        return 0;
    }
    
    PropType* proptype = (PropType*) calloc(1, sizeof(PropType));
    proptype->next = NULL;
    proptype->plugin = plugin;
    
    proptype->Init = SDL_LoadFunction(plugin, "Init");
    proptype->Destroy = SDL_LoadFunction(plugin, "Destroy");
    
    proptype->GetPropTypeStr = SDL_LoadFunction(plugin, "GetPropTypeStr");
    
    proptype->InitProp = SDL_LoadFunction(plugin, "InitProp");
    proptype->UpdateProp = SDL_LoadFunction(plugin, "UpdateProp");
    proptype->RenderProp = SDL_LoadFunction(plugin, "RenderProp");
    proptype->DestroyProp = SDL_LoadFunction(plugin, "DestroyProp");
    
    if(!(
        ( proptype->Init != NULL) &&
        ( proptype->Destroy != NULL ) &&
        ( proptype->GetPropTypeStr != NULL ) &&
        ( proptype->InitProp != NULL ) &&
        ( proptype->UpdateProp != NULL ) &&
        ( proptype->RenderProp != NULL ) &&
        ( proptype->DestroyProp != NULL )
    )) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load plugin %s: Missing symbols.", plugin_name);
        return 0;
    }
    
    if( !proptype->Init() ) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not load plugin %s: Initialisation failed.", plugin_name);
        return 0;
    }
    
    SDL_Log("Successfully loaded prop plugin \"%s\".", proptype->GetPropTypeStr());
    
    proptype->next = prm->types;
    prm->types = proptype;
    
    return 1;
}


static Prop* _CreateProp(PropManager* prm, const char* type, const char* name) {
    Prop* prop = (Prop*) calloc(1, sizeof(Prop));
    
    PropType* ptype = _GetPropType(prm, type);
    if(ptype == NULL) { return NULL; }
    
    prop->type = ptype;
    prop->name = (const char*) calloc(strlen(name)+1, sizeof(const char));
    strcpy((char *) prop->name, name);
    prop->next = NULL;
    prop->x = 0.0;
    prop->y = 0.0;
    prop->w = 0.0;
    prop->h = 0.0;
    prop->data = NULL;
    
    prop->type->InitProp(prop);
    
    return prop;
}

static void _DestroyProp(Prop* prop) {
    prop->type->DestroyProp(prop);
    free((void*) prop->name);
    free(prop);
}

static Prop* _TryFindProp(PropManager* prm, PropType* type, const char* name) {
    Prop* props = GetFirstProp(prm);
    while(props != NULL) {
        if( (props->type == type) && (strcmp(props->name, name) == 0) ) {
            return props;
        } else {
            props = props->next;
        }
    }
    return NULL;
}

static PropType* _GetPropType(PropManager* prm, const char* type) {
    PropType* ptype = prm->types;
    while(ptype != NULL) {
        if(strcmp( ptype->GetPropTypeStr(), type ) == 0) {
            return ptype;
        } else {
            ptype = ptype->next;
        }
    }
    return NULL;
}