#ifndef _gui_h
#define _gui_h

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

TTF_Font *font;

void load_font (char *fonts);
void paint_text (SDL_Surface *screen, char *text, int x, int y);

#endif
