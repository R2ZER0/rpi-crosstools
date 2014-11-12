// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#define TARGET_FORMAT       AV_PIX_FMT_YUV420P
#define TARGET_FORMAT_SDL   SDL_PIXELFORMAT_YV12 

static const char* PROP_TYPE = "video";

// Plugin Init/Shutdown stuff
int Init() {
    av_register_all();
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
    AVFormatContext* formatctx;
    AVCodecContext* codecctx;
    struct SwsContext* img_convert_ctx;
    
    AVCodec* codec;
    int stream_video;
    
    AVFrame* frame;
    AVFrame* frame_converted;
    
    SDL_Texture* frame_texture;
    double fps;
    
    uint32_t frameno;
    uint32_t start_time;
    
    int use_software_scaling;    
    char* video_path;
    
} Prop_Video;


// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) calloc(1, sizeof(Prop_Video));
    
    pvideo->formatctx = NULL;
    pvideo->codecctx = NULL;
    pvideo->img_convert_ctx = NULL;
    
    pvideo->codec = NULL;
    pvideo->stream_video = -1;
    
    pvideo->frame_converted = NULL;
    pvideo->frame = NULL;
    pvideo->fps = 25.0;
    
    pvideo->frame_texture = NULL;
    
    pvideo->use_software_scaling = 0;
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
    
    cJSON* fps_node = cJSON_GetObjectItem(obj, "fps");
    if(fps_node != NULL && fps_node->type == cJSON_Number) {
        pvideo->fps = fps_node->valuedouble;
    }
    
    if(load_video && pvideo->video_path != NULL) {
        if(pvideo->frame_texture != NULL) {
            SDL_DestroyTexture(pvideo->frame_texture);
            pvideo->frame_texture = NULL;
        }
        
        // open the video file!
        SDL_assert( avformat_open_input(&pvideo->formatctx, pvideo->video_path, NULL, NULL) == 0 );
        SDL_assert( avformat_find_stream_info(pvideo->formatctx, NULL) >= 0 );
        av_dump_format(pvideo->formatctx, 0, pvideo->video_path, 0);        
        
        // find the (first) video stream
        int stream_video = -1;
        int i = 0;
        for(i = 0; i < pvideo->formatctx->nb_streams; ++i) {
            if( pvideo->formatctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ) {
                stream_video = i;
                break;
            }
        }
        
        pvideo->stream_video = stream_video;    
        SDL_assert( stream_video != -1 );
        
        pvideo->codecctx = pvideo->formatctx->streams[stream_video]->codec;
        SDL_assert(pvideo->codecctx != NULL);
        
        SDL_Log("Finding decoder");
        pvideo->codec = avcodec_find_decoder(pvideo->codecctx->codec_id); // try to find the decoder
        SDL_assert( pvideo->codec != NULL );
        
        // try to open the decoder
        SDL_Log("Opening decoder");
        AVDictionary* optionsDict = NULL;
        int result = avcodec_open2(pvideo->codecctx, pvideo->codec, &optionsDict);
        SDL_assert( result == 0 );
        
        SDL_Log("Allocating frames");
        // Allocate our frames
        pvideo->frame_converted = avcodec_alloc_frame();
        pvideo->frame = avcodec_alloc_frame();
        SDL_assert( pvideo->frame != NULL );
        SDL_assert( pvideo->frame_converted != NULL );
        
        int target_video_w, target_video_h;
        if(pvideo->use_software_scaling) {
            target_video_w = (int) prop->w;
            target_video_h = (int) prop->h;
        } else {
            target_video_w = pvideo->codecctx->width;
            target_video_h = pvideo->codecctx->height;
        }
        
        // create a buffer for our (converted) frames
        int buffer_size = avpicture_get_size(TARGET_FORMAT, target_video_w, target_video_h);
        
        SDL_Log("Allocating conversion frame buffer %d x %d (%d)", target_video_w, target_video_h, buffer_size);
        uint8_t* buffer = (uint8_t*) av_malloc( buffer_size * sizeof(uint8_t) ); //meh, memory leaks
        
        SDL_assert(buffer != NULL);
        
        result = avpicture_fill(
            (AVPicture*) pvideo->frame_converted,
            buffer,
            TARGET_FORMAT,
            target_video_w,
            target_video_h
        );   
        if(result < 0) {
            char errbuf[1000];
            av_strerror(errno, &(errbuf[0]), 999);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "avpicture_fill: %s", &(errbuf[0]));
        }
        
        
        if(pvideo->codecctx->pix_fmt != TARGET_FORMAT) {
            SDL_Log("on-the-fly conversion to YUV420P required.");
        }
        
        // create our conversion context 
        pvideo->img_convert_ctx = sws_getContext(
            pvideo->codecctx->width,
            pvideo->codecctx->height,
            pvideo->codecctx->pix_fmt,
            target_video_w,
            target_video_h,
            TARGET_FORMAT,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
        );
        
        SDL_assert( pvideo->img_convert_ctx != NULL );
        
        
        pvideo->frame_texture = SDL_CreateTexture(renderer,
            TARGET_FORMAT_SDL, SDL_TEXTUREACCESS_STREAMING,
            target_video_w,
            target_video_h
        );
        
        SDL_assert( pvideo->frame_texture != NULL );

        pvideo->frameno = 0;
        pvideo->start_time = SDL_GetTicks();
    }
    
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    if(pvideo->frame == NULL) { return; }
    
    //uint32_t wanted_frameno = av_q2d(pvideo->codecctx->time_base) * ((double)(SDL_GetTicks() - pvideo->frameno)/1000.0);
    uint32_t time_difference = SDL_GetTicks() - pvideo->start_time;
    double time_diff_seconds = (double)time_difference / 1000.0;
    double time_base = 1.0/pvideo->fps;
    double frames_diff = time_diff_seconds/time_base;
    uint32_t wanted_frameno = (uint32_t)frames_diff;
    
//     SDL_Log("diff %d, secs %f, fps %f, base %f, rbase %f, fdiff %f, fwant %d, at %d",
//             time_difference,
//             time_diff_seconds,
//             pvideo->fps,
//             time_base,
//             av_q2d(pvideo->codecctx->time_base),
//             frames_diff,
//             wanted_frameno,
//             pvideo->frameno
//     );
    
    //SDL_Log("fps %f", 1.0/(av_q2d(pvideo->codecctx->time_base)*(double)pvideo->codecctx->gop_size));
    
    //SDL_Log("Frames want %d / at %d", wanted_frameno, pvideo->frameno);
    
//     if(pvideo->frameno <= wanted_frameno) {
    
        int frame_finished = 0;
        AVPacket packet;
        
        int prop_w = (int) prop->w;
        int prop_h = (int) prop->h;   
        
        int i = 0;
        while(av_read_frame(pvideo->formatctx, &packet) >= 0) {
            if(packet.stream_index == pvideo->stream_video) {
                
                if( 0 > avcodec_decode_video2(
                    pvideo->codecctx,
                    pvideo->frame,
                    &frame_finished,
                    &packet
                )) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "decoding error");
                }
                
                if(frame_finished) {
                    pvideo->frameno = pvideo->frameno + 1;
                }
                
                //if(frame_finished && pvideo->frameno >= wanted_frameno) {
                if(frame_finished) {
                    
                    
                    AVFrame* result_frame = NULL;
                    if(
                        pvideo->codecctx->pix_fmt == TARGET_FORMAT &&
                        !pvideo->use_software_scaling
                    ) {
                        // no conversion neccessary
                        result_frame = pvideo->frame;
                    } else {
                        
                        int result = sws_scale(
                            pvideo->img_convert_ctx,
                            (const uint8_t * const*) pvideo->frame->data,
                            pvideo->frame->linesize,
                            0,
                            prop_h,
                            pvideo->frame_converted->data,
                            pvideo->frame_converted->linesize
                        );
                        
                        if(result < 0) {
                            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Format conversion failed");
                            return;
                        }
                        result_frame = pvideo->frame_converted;
                    }
                    
                    SDL_SetTextureBlendMode(pvideo->frame_texture, SDL_BLENDMODE_BLEND);
                    if(0 > SDL_UpdateYUVTexture(
                        pvideo->frame_texture,
                        NULL,
                        result_frame->data[0],
                        result_frame->linesize[0],
                        result_frame->data[1],
                        result_frame->linesize[1],
                        result_frame->data[2],
                        result_frame->linesize[2]
                    )) {
                        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Frame update error: %s", SDL_GetError());
                        return;
                    }    
                    
                    SDL_Rect rect;
                    rect.x = (int) prop->x;
                    rect.y = (int) prop->y;
                    rect.w = (int) prop->w;
                    rect.h = (int) prop->h;

                    SDL_RenderCopy(renderer, pvideo->frame_texture, NULL, &rect);
                    
                    return;
                }
                
                
            }
            av_free_packet(&packet);
        }
    /*
    } else {
        
        SDL_Rect rect;
        rect.x = (int) prop->x;
        rect.y = (int) prop->y;
        rect.w = (int) prop->w;
        rect.h = (int) prop->h;

        SDL_RenderCopy(renderer, pvideo->frame_texture, NULL, &rect);
    }
    */
}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Video* pvideo = (Prop_Video*) prop->data;
    
    if(pvideo->frame_texture != NULL) {
        SDL_DestroyTexture(pvideo->frame_texture);
        pvideo->frame_texture = NULL;
    }
    
    avcodec_free_frame(&pvideo->frame_converted);
    avcodec_free_frame(&pvideo->frame);
    
    free(pvideo);
    prop->data = NULL;
}    