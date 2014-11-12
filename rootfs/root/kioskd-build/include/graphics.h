#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL_render.h>

typedef struct graphics Graphics;

extern Graphics* InitGraphics();
extern void DestroyGraphics(Graphics* gfx);

extern void ClearScreen(Graphics* gfx);
void DrawText(SDL_Renderer* renderer, int point_size, const char* text, int x, int y);

extern SDL_Renderer* GetRenderer(Graphics* gfx);

#endif //_GRAPHICS_H_