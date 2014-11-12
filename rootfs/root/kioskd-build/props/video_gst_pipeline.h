#include <gst/gst.h>

typedef struct video_pipeline VideoPipeline;

VideoPipeline* InitPipeline(const char* uri);
void TickPipeline(VideoPipeline* p);
void DestroyPipeline(VideoPipeline* p);