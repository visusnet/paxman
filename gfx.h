#ifndef _gfx_h
#define _gfx_h

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "map.h"

static SDL_Surface *GFX_loadTile (char tilename);

void GFX_initScreen (int h, int w, int res);
void GFX_initFont (char *path, int size);
void GFX_setFontColor (int r, int g, int b);
void GFX_printText (char *text, int x, int y);
void GFX_copySurface (SDL_Surface *surface, int x, int y);
SDL_Surface *GFX_loadImage (char *path);
void GFX_updateScreen ();
void GFX_clearScreen ();
void GFX_copyFullMap (map_t *map);
	
#endif
