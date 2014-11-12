// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include "video_gst_pipeline.h"

static const char* PROP_TYPE = "video";

// Plugin Init/Shutdown stuff
int Init() {
    gst_init(NULL, NULL);
    return 1;
}

void Destroy() {
    return;
}

const char* GetPropTypeStr() {
    return PROP_TYPE;
}


// Our actual prop stuff
typedef struct prop_video {
    
    VideoPipeline* pipeline;
    
    SDL_Texture* frame_texture;
    char* video_path;
    
} Prop_Video;


// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) calloc(1, sizeof(Prop_Video));

    pvideo->frame_texture = NULL;
    pvideo->video_path = NULL;
    
    pvideo->pipeline = NULL;
   
    prop->data = (void*) pvideo;
}

// Called when this prop has been sent data
void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_Video* pv = (Prop_Video*) prop->data;
    
    int load_video = 0;
    
    if(prop_changed) {
        load_video = 1;
    }
    
    cJSON* video_path_node = cJSON_GetObjectItem(obj, "video_path");
    if(video_path_node != NULL && video_path_node->type == cJSON_String) {
        if(pv->video_path != NULL) { free((void*) pv->video_path); }
        pv->video_path = strdup(video_path_node->valuestring);
        load_video = 1;
    }
    
    if(load_video && pv->video_path != NULL) {
        if(pv->frame_texture != NULL) {
            SDL_DestroyTexture(pv->frame_texture);
            pv->frame_texture = NULL;
        }
        
        pv->frame_texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
            (int) prop->w,
            (int) prop->h
        );
        
        SDL_assert( pv->frame_texture != NULL );
        
        if(pv->pipeline != NULL) {
            DestroyPipeline(pv->pipeline);
        }
        
        pv->pipeline = InitPipeline(pv->video_path);

    }
    
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    TickPipeline(pvideo->pipeline);
    
}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    if(pvideo->frame_texture != NULL) {
        SDL_DestroyTexture(pvideo->frame_texture);
        pvideo->frame_texture = NULL;
    }
    
    if(pvideo->pipeline != NULL) {
        DestroyPipeline(pvideo->pipeline);
    }
    
    free(pvideo);
    prop->data = NULL;
}    