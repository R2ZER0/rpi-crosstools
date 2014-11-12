#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "prop_interface.h"
#include "SDL.h"
#include "SDL_ttf.h"

static const char* PROP_TYPE = "text";

// Plugin Init/Shutdown stuff
extern int Init() {
    if(TTF_Init() < 0) {
        fprintf(stderr, "Cannot initialise TTF: %s \n", TTF_GetError());
        return 0;
    }
    return 1;
}

extern void Destroy() {
    TTF_Quit();
}

extern const char* GetPropTypeStr() {
    return PROP_TYPE;
}


// Our actual prop stuff
typedef struct prop_text {
    TTF_Font* font;
    const char* font_path;
    int font_point_size;
    
    const char* text;
    int text_w, text_h;
    SDL_Texture* text_texture;
    SDL_Color colour;
    int wrap;
} Prop_Text;


extern void InitProp(Prop* prop) {
    Prop_Text* proptext = (Prop_Text*) calloc(1, sizeof(Prop_Text));
    
    static const char* DEFAULT_FONT_PATH = "fonts/quartzregulardb.ttf";
    
    proptext->font = NULL;
    proptext->font_path = (const char*) strdup(DEFAULT_FONT_PATH);
    proptext->font_point_size = 16;
    proptext->text = NULL;
    proptext->text_w = 0;
    proptext->text_h = 0;
    proptext->text_texture = NULL;
    proptext->colour.r = 255;
    proptext->colour.g = 255;
    proptext->colour.b = 255;
    proptext->colour.a = 255;
    proptext->wrap = 1;
    
    prop->data = (void*) proptext;
}

extern void UpdateProp(Prop* prop, cJSON* obj, SDL_Renderer* renderer, PropChanged prop_changed) {
    Prop_Text* proptext = (Prop_Text*) prop->data;
    SDL_assert( proptext != NULL );
    
    int reopen_font = 0;
    int redraw_surface = 0;
    
    if((prop_changed&PROP_CHANGED_W) || (prop_changed&PROP_CHANGED_H)) {
        redraw_surface = 1;
    }
    
    // Check if font has changed
    cJSON* font_path_node = cJSON_GetObjectItem(obj, "font_path");
    if(font_path_node != NULL && font_path_node->type == cJSON_String) {
        if(proptext->font_path != NULL) { free((void*) proptext->font_path); }
        proptext->font_path = strdup(font_path_node->valuestring);
        reopen_font = 1;
    }
    
    // Set point size if specified
    cJSON* font_point_size_node = cJSON_GetObjectItem(obj, "font_point_size");
    if(font_point_size_node != NULL && font_point_size_node->type == cJSON_Number) {
        proptext->font_point_size = font_point_size_node->valueint;
        reopen_font = 1;
    }
    
    // Update text if specified
    cJSON* text_node = cJSON_GetObjectItem(obj, "text");
    if(text_node != NULL && text_node->type == cJSON_String) {
        if(proptext->text != NULL) { free((void*) proptext->text); }
        proptext->text = strdup(text_node->valuestring);        
        redraw_surface = 1;
    }
    
    // Update colour if specified
    cJSON* colour_node = cJSON_GetObjectItem(obj, "colour");
    if(colour_node != NULL && colour_node->type == cJSON_Array) {
        int array_size = cJSON_GetArraySize(colour_node);
        if(array_size == 3 || array_size == 4) {
            proptext->colour.r = (Uint8) cJSON_GetArrayItem(colour_node, 0)->valueint;
            proptext->colour.g = (Uint8) cJSON_GetArrayItem(colour_node, 1)->valueint;
            proptext->colour.b = (Uint8) cJSON_GetArrayItem(colour_node, 2)->valueint;
            if(array_size == 4) {
                proptext->colour.a = (Uint8) cJSON_GetArrayItem(colour_node, 3)->valueint;
            } else {
                proptext->colour.a = 255;
            }
            redraw_surface = 1;
            SDL_Log("Setting text colour %d %d %d %d", proptext->colour.r, proptext->colour.g, proptext->colour.b, proptext->colour.a);
        } else {
            SDL_Log("Invalid colour specified (size %d)", array_size);
        }
    }
    
    // Update wrapping if specified
    cJSON* wrap_node = cJSON_GetObjectItem(obj, "wrap");
    if(wrap_node != NULL) {
        if(wrap_node->type == cJSON_True) {
            proptext->wrap = 1;
            redraw_surface = 1;
            
        } else if(wrap_node->type == cJSON_False) {
            proptext->wrap = 0;
            redraw_surface = 1;
            
        } else if(wrap_node->type == cJSON_Number) {
            proptext->wrap = !!wrap_node->valueint;
        }
    }
    
    if(proptext->text == NULL ) { return; } // there's no point rendering nothing
     
    // If our font has changed, reload it
    if(reopen_font) {
        if(proptext->font != NULL) {
            TTF_CloseFont(proptext->font);
        }
        proptext->font = TTF_OpenFont(proptext->font_path, proptext->font_point_size);
        if(proptext->font == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load font %s : %s", proptext->font_path, TTF_GetError());
        }
    }
    
    // If the font or text has changed, redraw it
    if(reopen_font || redraw_surface) {
        if(proptext->text_texture != NULL) { SDL_DestroyTexture(proptext->text_texture); }
        
        SDL_Surface* text_surface = NULL;
        
        if(proptext->wrap) {
            text_surface = TTF_RenderText_Blended_Wrapped(proptext->font, proptext->text, proptext->colour, (int) prop->w);
        } else {
            text_surface = TTF_RenderText_Blended(proptext->font, proptext->text, proptext->colour);
        }
        
        if( text_surface == NULL ) { 
            fprintf(stderr, "Couldn't Render Text: %s | %s \n", proptext->text, TTF_GetError());
        }
        
        proptext->text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        proptext->text_w = text_surface->w;
        proptext->text_h = text_surface->h;
        
        if(proptext->text_texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create text surface texture: %s", SDL_GetError());
        }
        
        SDL_FreeSurface(text_surface);
        text_surface = NULL;
    }
}

extern void RenderProp(Prop* prop, SDL_Renderer* renderer) {
    Prop_Text* proptext = (Prop_Text*) prop->data;
    if(proptext->text_texture == NULL) { return; }
    
    SDL_Rect destrect;
    
    destrect.x = prop->x;
    destrect.y = prop->y;
    destrect.w = proptext->text_w;
    destrect.h = proptext->text_h;
    
    if( SDL_RenderCopy(renderer, proptext->text_texture, NULL, &destrect) != 0 ) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't render text texture: %s", SDL_GetError());
    }
}

extern void DestroyProp(Prop* prop) {
    Prop_Text* proptext = (Prop_Text*) prop->data;
    
    SDL_DestroyTexture(proptext->text_texture);
    TTF_CloseFont(proptext->font);
    free((void*) proptext->font_path);
    free(proptext);
}

    