// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"

static const char* PROP_TYPE = "generic";

// Plugin Init/Shutdown stuff
int Init() {
    return 1;
}

void Destroy() {
    
}

const char* GetPropTypeStr() {
    return PROP_TYPE;
}


// Our actual prop stuff
typedef struct prop_linegraph {
    // things you need to store here
} Prop_Generic;


// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Generic* propgeneric = (Prop_Generic*) calloc(1, sizeof(Prop_Generic));
    
    // Initialise prop defaults here
    
    prop->data = (void*) propgeneric;
}

// Called when this prop has been sent data
void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_Generic* propgeneric = (Prop_Generic*) prop->data;
       
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Generic* propgeneric = (Prop_Generic*) prop->data;

}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Generic* propgeneric = (Prop_Generic*) prop->data;
    
    free(propgeneric);
}

    