// Gstreamer video pipeline implementation
#include "video_gst_pipeline.h"
#include <SDL_assert.h>
#include <SDL_log.h>

struct video_pipeline
{    
    GstBus* bus;
    guint bus_watch_id;
    
    GstElement* pipeline;
    GstElement* player;
    GstElement* sink;
};

// callbacks



static gboolean has_gst_init = FALSE;

VideoPipeline* InitPipeline(const char* path)
{
    if(!has_gst_init)
    {
        gst_init(NULL, NULL);
        has_gst_init = TRUE;
        SDL_Log("Init Gstreamer");
    }
    
    VideoPipeline* p = (VideoPipeline*) calloc(1, sizeof(VideoPipeline));
    SDL_Log("Creating pipeline");
    
    gchar* file_uri = g_filename_to_uri(path, NULL, NULL);
    SDL_Log("Media URI: %s", file_uri);
    
    // Create our pipeline
    p->pipeline = gst_pipeline_new("kioskd-video-pipeline");
    SDL_assert( p->pipeline );
    
    p->bus = gst_pipeline_get_bus(GST_PIPELINE(p->pipeline));
    SDL_assert( p->bus );
    
    // Create the elements
    p->player = gst_element_factory_make("playbin", "player");
    p->sink = gst_element_factory_make("xvimagesink", "sink");
    
    SDL_assert( p->player );
    SDL_assert( p->sink );
    
    // Add the elements to the pipeline
    gst_bin_add(GST_BIN(p->pipeline), p->player);
    gst_bin_add(GST_BIN(p->pipeline), p->sink);
    
    g_object_set(G_OBJECT(p->player), "uri", file_uri, NULL);
    g_free(file_uri);
    
    // Link the elements together
    int result = 1;//gst_element_link_many(p->player, p->sink, NULL);
    
    if(!result) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not link elements!");
    }
    
    
    
    return p;
}

void TickPipeline(VideoPipeline* p)
{
    GstMessage* message = NULL;
    
    while(message = gst_bus_peek(p->bus))
    {
        gchar* debug;
        GError* error;
        switch(message->type)
        {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(message, &error, &debug);
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GstBus Error: %s", debug);
                g_free(error);
                g_free(debug);
                break;
                
            case GST_MESSAGE_EOS:
                // end-of-stream?
                SDL_Log("End-of-Stream reached");
                break;
            
            default:
                SDL_Log("Unknown GST message arrived");
        }
    }
}


void DestroyPipeline(VideoPipeline* p)
{
    SDL_Log("Destroying pipeline");
    gst_object_unref(GST_OBJECT(p->pipeline));
    
    free(p);
}


/////////// callbacks /////////
