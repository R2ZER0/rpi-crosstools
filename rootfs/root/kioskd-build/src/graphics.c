// Low-level graphics management

#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include <SDL_ttf.h>

// Graphics data struct
struct graphics {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

// It's probably not a good idea to call this more than once right now.
Graphics* InitGraphics() {
    
    // (Globally) initialise SDL
    if(SDL_Init(0) == -1) {
        fprintf(stderr, "Cannot initialise SDL: %s \n", SDL_GetError());
    }
    atexit(SDL_Quit);
    
    // (Globally) initialise SDL_ttf
    if(TTF_Init() == -1) {
        fprintf(stderr, "Cannot initialise TTF: %s \n", TTF_GetError());
        return NULL;
    }
    atexit(TTF_Quit);
    
    
    //////////
    // Print the available video drivers
    int driver_index = 0;
    int driver_num = SDL_GetNumVideoDrivers();
    for(driver_index = 0; driver_index < driver_num; ++driver_index) {
        SDL_Log("Driver: %s", SDL_GetVideoDriver(driver_index));
    }
    
    
    //////////
  
    Graphics* gfx = (Graphics*) calloc(1, sizeof(Graphics));
    
    if(SDL_WasInit(SDL_INIT_VIDEO) != 0) {
    
        // Initialise SDL and create our Video surface
        if(SDL_InitSubSystem( SDL_INIT_VIDEO ) < 0) {
            fprintf( stderr, "Cannot initialise SDL: %s \n", SDL_GetError() );
            return NULL;
        }
       
    }
    
    // Create the window!
    gfx->window = SDL_CreateWindow(
        "kioskd display",           // window title
        SDL_WINDOWPOS_UNDEFINED,    // X position
        SDL_WINDOWPOS_UNDEFINED,    // Y position
        //1280,        // Width
        //720,        // Height   //FIXME BEFORE RELEASE
        0,
        0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL /*| SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN*/
    );
    
    
    if(!gfx->window) {
        fprintf(stderr, "Cannot create window: %s \n", SDL_GetError());
        return NULL;
    }
    
    // Create SDL Renderer (why?)
    gfx->renderer = SDL_CreateRenderer(gfx->window, -1, SDL_RENDERER_ACCELERATED);
    if(!gfx->renderer) {
        fprintf(stderr, "Cannot create renderer: %s \n", SDL_GetError());
        return NULL;
    }
    
    SDL_ShowWindow(gfx->window);
    SDL_assert( SDL_ShowCursor(0) >= 0 );
    
    return gfx;
}

void DestroyGraphics(Graphics* gfx) {
    if(gfx != NULL) {
        /* Crashes things, not sure why, undestroyed textures?
        if(gfx->renderer != NULL) SDL_DestroyRenderer(gfx->renderer);
        if(gfx->window != NULL) SDL_DestroyWindow(gfx->window);
        */
    
        free(gfx);
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Renderer* GetRenderer(Graphics* gfx) {
    return gfx->renderer;
}

void ClearScreen(Graphics* gfx) {
    SDL_Renderer* renderer = GetRenderer(gfx);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// okay, so maybe this is actually useful...
void DrawText(SDL_Renderer* renderer, int point_size, const char* text, int x, int y) {
    // For now, really slow, but works?
    
    TTF_Font* font = TTF_OpenFont("fonts/quartzregulardb.ttf", point_size);
    
    if(!font) {
        fprintf(stderr, "Failed to load font: %s \n", TTF_GetError());
    }
    
    SDL_Color colour_white = { 255, 255, 255, 255 };
    SDL_Surface* text_surface = NULL;
    
    if(!(text_surface = TTF_RenderUTF8_Blended(font, text, colour_white))) {
        fprintf(stderr, "Couldn't render text: %s \n", TTF_GetError());
    }
    
    SDL_Rect text_pos;
    text_pos.x = x;
    text_pos.y = y;
    text_pos.w = text_surface->w;
    text_pos.h = text_surface->h;
    
    //SDL_BlitSurface(text_surface, NULL, screen_surface, &text_pos);
    //SDL_UpdateWindowSurface(gfx->window);
    
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    SDL_RenderCopy(renderer, text_texture, NULL, &text_pos);
    //SDL_RenderPresent(renderer);
    
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}
