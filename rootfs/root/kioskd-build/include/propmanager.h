// Prop data structure(s)
#ifndef _PROPMANAGER_H_
#define _PROPMANAGER_H_

#include "prop.h"
#include "SDL_render.h"

typedef struct propmanager PropManager;

extern PropManager* InitPropManager();
extern void DestroyPropManager(PropManager* prm);
extern int LoadPropPlugin(PropManager* prm, const char* plugin_path);
extern Prop* GetProp(PropManager* prm, const char* type, const char* name);
extern Prop* GetFirstProp(PropManager* prm);
extern void UnlinkProp(PropManager* prm, Prop* prop);

#endif //_PROPMANAGER_H_