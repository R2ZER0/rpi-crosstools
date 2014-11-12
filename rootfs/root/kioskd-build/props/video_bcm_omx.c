// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include <bcm_host.h>
#include <ilclient.h>

static const char* PROP_TYPE = "video";

// Plugin Init/Shutdown stuff
int Init() {
    bcm_host_init();
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
    
    OMX_VIDEO_PARAM_PORTFORMATTYPE format;
    OMX_TIME_CONFIG_CLOCKSTATETYPE cstate;
    COMPONENT_T *video_decode, *video_scheduler, *video_render, *clock;
    COMPONENT_T *list[5];
    TUNNEL_T tunnel[4];
    ILCLIENT_T *client;
    FILE *in;
    unsigned int data_len;
    
    
    SDL_Texture* frame_texture;
    char* video_path;
    
} Prop_Video;


// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) calloc(1, sizeof(Prop_Video));
    
    pvideo->data_len = 0;
    
    pvideo->video_decode = NULL;
    pvideo->video_scheduler = NULL;
    pvideo->video_render = NULL;
    pvideo->clock = NULL;

    pvideo->frame_texture = NULL;
    pvideo->video_path = NULL;
   
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
        
        /////////////////////////////////////////
        
        int status = 0;
        pv->data_len = 0;
        
        memset(pv->list, 0, sizeof(pv->list));
        memset(pv->tunnel, 0, sizeof(pv->tunnel));
        
        if((pv->in = fopen(pv->video_path, "rb")) == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not open video file");
            return;
        }

        if((pv->client = ilclient_init()) == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialise ilclient");
            fclose(pv->in);
            return;
        }

        if(OMX_Init() != OMX_ErrorNone) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialise OMX");
            
            ilclient_destroy(pv->client);
            fclose(pv->in);
            return;
        }
        
        // create video_decode
        if(ilclient_create_component(pv->client, &pv->video_decode, "video_decode", ILCLIENT_DISABLE_ALL_PORTS | ILCLIENT_ENABLE_INPUT_BUFFERS) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create video_decode component");
            status = -14;
        }
        pv->list[0] = pv->video_decode;

        // create video_render
        if(status == 0 && ilclient_create_component(pv->client, &pv->video_render, "video_render", ILCLIENT_DISABLE_ALL_PORTS) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create video_render component");
            status = -14;
        }
        pv->list[1] = pv->video_render;

        // create clock
        if(status == 0 && ilclient_create_component(pv->client, &pv->clock, "clock", ILCLIENT_DISABLE_ALL_PORTS) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "could not create clock component");
            status = -14;
        }
        pv->list[2] = pv->clock;

        memset(&pv->cstate, 0, sizeof(pv->cstate));
        pv->cstate.nSize = sizeof(pv->cstate);
        pv->cstate.nVersion.nVersion = OMX_VERSION;
        pv->cstate.eState = OMX_TIME_ClockStateWaitingForStartTime;
        pv->cstate.nWaitMask = 1;
        if(pv->clock != NULL && OMX_SetParameter(ILC_GET_HANDLE(pv->clock), OMX_IndexConfigTimeClockState, &pv->cstate) != OMX_ErrorNone) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set clock state");
            status = -13;
        }

        // create video_scheduler
        if(status == 0 && ilclient_create_component(pv->client, &pv->video_scheduler, "video_scheduler", ILCLIENT_DISABLE_ALL_PORTS) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create video_scheduler component");
            status = -14;
        }
        pv->list[3] = pv->video_scheduler;

        set_tunnel(pv->tunnel, pv->video_decode, 131, pv->video_scheduler, 10);
        set_tunnel(pv->tunnel+1, pv->video_scheduler, 11, pv->video_render, 90);
        set_tunnel(pv->tunnel+2, pv->clock, 80, pv->video_scheduler, 12);

        // setup clock tunnel first
        if(status == 0 && ilclient_setup_tunnel(pv->tunnel+2, 0, 0) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't setup clock tunnel");
            status = -15;
        } else {
            ilclient_change_component_state(pv->clock, OMX_StateExecuting);
        }

        if(status == 0) {
            ilclient_change_component_state(pv->video_decode, OMX_StateIdle);
        }

        memset(&pv->format, 0, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
        pv->format.nSize = sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE);
        pv->format.nVersion.nVersion = OMX_VERSION;
        pv->format.nPortIndex = 130;
        pv->format.eCompressionFormat = OMX_VIDEO_CodingAVC;
        
        if(status != 0) {
            SDL_Log("Status non-zero (see above error)");
            return;
        }
        
        if(!(
            OMX_SetParameter(ILC_GET_HANDLE(pv->video_decode), OMX_IndexParamVideoPortFormat, &pv->format) == OMX_ErrorNone &&
            ilclient_enable_port_buffers(pv->video_decode, 130, NULL, NULL, NULL) == 0
        )) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not set decode port format");
        }
        
        /////// setup complete!
        OMX_BUFFERHEADERTYPE *buf;
        int port_settings_changed = 0;
        int first_packet = 1;

        ilclient_change_component_state(pv->video_decode, OMX_StateExecuting);
        
        SDL_Log("Staring raw data feed");

        while((buf = ilclient_get_input_buffer(pv->video_decode, 130, 1)) != NULL)
        {
            // feed data and wait until we get port settings changed
            unsigned char *dest = buf->pBuffer;

            pv->data_len += fread(dest, 1, (buf->nAllocLen)-(pv->data_len), pv->in);

            if(port_settings_changed == 0 &&
                ((pv->data_len > 0 && ilclient_remove_event(pv->video_decode, OMX_EventPortSettingsChanged, 131, 0, 0, 1) == 0) ||
                (pv->data_len == 0 && ilclient_wait_for_event(pv->video_decode, OMX_EventPortSettingsChanged, 131, 0, 0, 1,
                                                        ILCLIENT_EVENT_ERROR | ILCLIENT_PARAMETER_CHANGED, 10000) == 0)))
            {
                port_settings_changed = 1;
                SDL_Log("Port settings changed");

                if(ilclient_setup_tunnel(pv->tunnel, 0, 0) != 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not setup decoder<->scheduler tunnel");
                    status = -7;
                    break;
                }

                ilclient_change_component_state(pv->video_scheduler, OMX_StateExecuting);

                // now setup tunnel to video_render
                if(ilclient_setup_tunnel(pv->tunnel+1, 0, 1000) != 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not setup render<->scheduler tunnel");
                    status = -12;
                    break;
                }

                ilclient_change_component_state(pv->video_render, OMX_StateExecuting);
            }
            if(!pv->data_len) {
                SDL_Log("Finished data feed");
                break;
            }

            buf->nFilledLen = pv->data_len;
            pv->data_len = 0;

            buf->nOffset = 0;
            if(first_packet)
            {
                buf->nFlags = OMX_BUFFERFLAG_STARTTIME;
                first_packet = 0;
            }
            else
                buf->nFlags = OMX_BUFFERFLAG_TIME_UNKNOWN;

            if(OMX_EmptyThisBuffer(ILC_GET_HANDLE(pv->video_decode), buf) != OMX_ErrorNone)
            {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not empty video_decode buffer");
                status = -6;
                break;
            }
        }

        buf->nFilledLen = 0;
        buf->nFlags = OMX_BUFFERFLAG_TIME_UNKNOWN | OMX_BUFFERFLAG_EOS;

        if(OMX_EmptyThisBuffer(ILC_GET_HANDLE(pv->video_decode), buf) != OMX_ErrorNone) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not empty video decode buffer");
            status = -20;
        }
        
        SDL_Log("Waiting for end-of-stream");

        // wait for EOS from render
        ilclient_wait_for_event(pv->video_render, OMX_EventBufferFlag, 90, 0, OMX_BUFFERFLAG_EOS, 0,
                                ILCLIENT_BUFFER_FLAG_EOS, 10000);
        
        SDL_Log("Got. Flushing tunnels");

        // need to flush the renderer to allow video_decode to disable its input port
        ilclient_flush_tunnels(pv->tunnel, 0);

        ilclient_disable_port_buffers(pv->video_decode, 130, NULL, NULL, NULL);
        
        SDL_Log("OMX Finished.");
            
        
        
        
        
        
        
        
        
        
        pv->frame_texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,
            100,
            100
        );
        
        SDL_assert( pv->frame_texture != NULL );

    }
    
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
   
}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    if(pvideo->frame_texture != NULL) {
        SDL_DestroyTexture(pvideo->frame_texture);
        pvideo->frame_texture = NULL;
    }
    
    fclose(pvideo->in);

    ilclient_disable_tunnel(pvideo->tunnel);
    ilclient_disable_tunnel(pvideo->tunnel+1);
    ilclient_disable_tunnel(pvideo->tunnel+2);
    ilclient_teardown_tunnels(pvideo->tunnel);

    ilclient_state_transition(pvideo->list, OMX_StateIdle);
    ilclient_state_transition(pvideo->list, OMX_StateLoaded);

    ilclient_cleanup_components(pvideo->list);

    OMX_Deinit();

    ilclient_destroy(pvideo->client);
    pvideo->client = NULL;
    
    free(pvideo);
    prop->data = NULL;
}    