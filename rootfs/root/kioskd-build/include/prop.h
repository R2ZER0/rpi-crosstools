#ifndef _PROP_H_
#define _PROP_H_

#include "cJSON.h"
#include "SDL_render.h"

typedef struct proptype PropType;
typedef struct prop Prop;
typedef enum propchanged PropChanged;

enum propchanged {
    PROP_CHANGED_X = 1,
    PROP_CHANGED_Y = 2,
    PROP_CHANGED_W = 4,
    PROP_CHANGED_H = 8,
};

struct proptype {
    PropType* next;
    void* plugin;
    
    int (*Init)(void);
    void (*Destroy)(void);

    const char* (*GetPropTypeStr)(void);

    void (*InitProp)(Prop*);
    void (*UpdateProp)(Prop*, cJSON*, SDL_Renderer*, PropChanged);
    void (*RenderProp)(Prop*, SDL_Renderer*);
    void (*DestroyProp)(Prop*);
};

struct prop {
    PropType* type;
    const char* name;
    Prop* next;
    
    double x, y;
    double w, h;
    
    void* data; // type-specific data
};

#endif //_PROP_H_