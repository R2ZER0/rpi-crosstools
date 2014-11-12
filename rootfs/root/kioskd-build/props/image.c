// An example generic plugin

#include <stdlib.h>
#include "prop_interface.h"
#include <SDL_image.h>

static const char* PROP_TYPE = "image";

// Plugin Init/Shutdown stuff
int Init() {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    return 1;
}

void Destroy() {
    IMG_Quit();
}

const char* GetPropTypeStr() {
    return PROP_TYPE;
}


// Our actual prop stuff
typedef struct prop_image {
    
    SDL_Texture* texture;
    
} Prop_Image;


// This is called to create and initialise a new prop
void InitProp(Prop* prop) {
    Prop_Image* pimage = (Prop_Image*) calloc(1, sizeof(Prop_Image));
    
    // Initialise prop defaults here
    pimage->texture = NULL;
    
    prop->data = (void*) pimage;
}

// Called when this prop has been sent data
void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_Image* pimage = (Prop_Image*) prop->data;
    
    cJSON* image_path_node = cJSON_GetObjectItem(obj, "image_path");
    if(image_path_node != NULL && image_path_node->type == cJSON_String) {
        char* image_path = strdup(image_path_node->valuestring);
        
        if(pimage->texture != NULL) {
            SDL_DestroyTexture(pimage->texture);
            pimage->texture = NULL;
        }
        
        SDL_Surface* image = IMG_Load(image_path);
        if(image == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load image %s : %s", image_path, SDL_GetError());
            return;
        }
        
        pimage->texture = SDL_CreateTextureFromSurface(renderer, image);
        
        //SDL_FreeSurface(image);
        image = NULL;
        
        if(pimage->texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create image texture: %s", SDL_GetError());
            return;
        }
        SDL_Log("Created image texture %s", image_path);
    }
       
}

// When this prop needs to be rendered to the screen
void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Image* pimage = (Prop_Image*) prop->data;
    
    SDL_Rect rect;
    rect.x = (int) prop->x;
    rect.y = (int) prop->y;
    rect.w = (int) prop->w;
    rect.h = (int) prop->h;
    
    SDL_RenderCopy(renderer, pimage->texture, NULL, &rect);

}

// Clean up and free memory
void DestroyProp(Prop* prop) {
    Prop_Image* pimage = (Prop_Image*) prop->data;
    
    if(pimage->texture != NULL) {
        SDL_DestroyTexture(pimage->texture);
        pimage->texture = NULL;
    }
    
    free(pimage);
}

    