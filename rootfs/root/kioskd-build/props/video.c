// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include <vlc/vlc.h>

// See: https://wiki.videolan.org/LibVLC_SampleCode_SDL#SDL_2.0

static const char* PROP_TYPE = "video";

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
typedef struct prop_video {
    libvlc_instance_t* libvlc;
    libvlc_media_player_t* player;
    
    SDL_Surface* frame_surface;
    SDL_Texture* frame_texture;
    SDL_mutex* mutex;
    int frame_update;
    
    const char** vlc_argv;
    int vlc_argc;
    
    char* video_path;
    
} Prop_Video;

//libvlc callbacks
static void* _lock(void* data, void** p_pixels);
static void _unlock(void* data, void* id, void* const* p_pixels);
static void _display(void* data, void* id);

// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) calloc(1, sizeof(Prop_Video));
    
    static char const *vlc_argv[] = {

        //"--no-audio", // Don't play audio.
        "--no-xlib", // Don't use Xlib.
        "--loop",
        // Apply a video filter.
        //"--video-filter", "sepia",
        //"--sepia-intensity=200"
    };
    
    pvideo->vlc_argv = vlc_argv;
    pvideo->vlc_argc = sizeof(vlc_argv) / sizeof(*(pvideo->vlc_argv));
    
    pvideo->libvlc = libvlc_new(pvideo->vlc_argc, pvideo->vlc_argv);
    SDL_assert_release( pvideo->libvlc != NULL );
    
    pvideo->player = NULL;
    pvideo->frame_surface = NULL;
    pvideo->frame_texture = NULL;
    pvideo->frame_update = 0;
    pvideo->mutex = SDL_CreateMutex();
    pvideo->video_path = NULL;
   
    prop->data = (void*) pvideo;
}

// Called when this prop has been sent data
void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    int load_video = 0;
    
    if(prop_changed) {
        load_video = 1;
    }
    
    cJSON* video_path_node = cJSON_GetObjectItem(obj, "video_path");
    if(video_path_node != NULL && video_path_node->type == cJSON_String) {
        if(pvideo->video_path != NULL) { free((void*) pvideo->video_path); }
        pvideo->video_path = strdup(video_path_node->valuestring);
        load_video = 1;
    }
    
    if(load_video) {
        if(pvideo->player != NULL) {
            libvlc_media_player_stop(pvideo->player);
            libvlc_media_player_release(pvideo->player);
            pvideo->player = NULL;
        }
        if(pvideo->frame_surface != NULL) {
            SDL_FreeSurface(pvideo->frame_surface);
            pvideo->frame_surface = NULL;
        }
        if(pvideo->frame_texture != NULL) {
            SDL_DestroyTexture(pvideo->frame_texture);
            pvideo->frame_texture = NULL;
        }
        
        libvlc_media_t* media = libvlc_media_new_path(pvideo->libvlc, pvideo->video_path);
        pvideo->player = libvlc_media_player_new_from_media(media);
        libvlc_media_release(media);
        
        
        pvideo->frame_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, (int) prop->w, (int) prop->h,
                                    16, 0x001f, 0x07e0, 0xf800, 0);
        
        pvideo->frame_texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_BGR565, SDL_TEXTUREACCESS_STREAMING,
            (int) prop->w, (int) prop->h);
        
        libvlc_video_set_callbacks(pvideo->player, &_lock, &_unlock, &_display, prop);
        libvlc_video_set_format(pvideo->player, "RV16", (unsigned int) prop->w, (unsigned int) prop->h, (unsigned int) prop->w*2);
        libvlc_media_player_play(pvideo->player);
    }
    
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    SDL_Rect rect;
    rect.x = (int) prop->x;
    rect.y = (int) prop->y;
    rect.w = (int) prop->w;
    rect.h = (int) prop->h;
        
    
    if(pvideo->frame_update) {
        
        SDL_LockMutex(pvideo->mutex);
        SDL_LockSurface(pvideo->frame_surface);
        
        SDL_UpdateTexture(pvideo->frame_texture, NULL, pvideo->frame_surface->pixels, pvideo->frame_surface->pitch);
        
        SDL_UnlockSurface(pvideo->frame_surface);
        SDL_UnlockMutex(pvideo->mutex);
        
        pvideo->frame_update = 0;
        
    }
    
    SDL_RenderCopy(renderer, pvideo->frame_texture, NULL, &rect);
}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    libvlc_media_player_stop(pvideo->player);
    
    SDL_LockMutex(pvideo->mutex);
    libvlc_media_player_release(pvideo->player);
    
    SDL_DestroyMutex(pvideo->mutex);
    SDL_DestroyTexture(pvideo->frame_texture);
    SDL_FreeSurface(pvideo->frame_surface);
    
    free(pvideo);
    prop->data = NULL;
}


///// Callbacks for libvlc

static void* _lock(void* data, void** p_pixels) {
    Prop* prop = (Prop*) data;
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    SDL_LockMutex(pvideo->mutex);
    while(SDL_LockSurface(pvideo->frame_surface) == -1) {}
    *p_pixels = pvideo->frame_surface->pixels;
    
    return NULL; // Picture id not required
}

static void _unlock(void* data, void* id, void* const* p_pixels) {
    Prop* prop = (Prop*) data;
    Prop_Video* propvideo = (Prop_Video*) prop->data;
    
    uint16_t* pixels = (uint16_t*) *p_pixels;
    
    SDL_UnlockSurface(propvideo->frame_surface);
    SDL_UnlockMutex(propvideo->mutex);
    
}

static void _display(void* data, void* id) {
    Prop* prop = (Prop*) data;
    Prop_Video* propvideo = (Prop_Video*) prop->data;
    
    // instead render it in our own time
    propvideo->frame_update = 1;
}
    