// The interface that a prop must implement
#include <stdlib.h>
#include "graphics.h"
#include "cJSON.h"
#include "prop.h"
#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif


// called on startup and shutdown of kioskd (or when the plugin is loaded/unloaded)
extern int Init();  // return 1 on success, anything else on failure
extern void Destroy();

// returns a string naming the type, e.g. "text", "image"
extern const char* GetPropTypeStr();

// functions for managing individual prop instances
extern void InitProp(Prop* prop);
extern void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed);
extern void RenderProp(Prop* prop, SDL_Renderer* renderer);
extern void DestroyProp(Prop* prop);

#ifdef __cplusplus
}; // extern "C"
#endif