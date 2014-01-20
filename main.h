#ifndef _main_h
#define _main_h

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>

#include "character.h"
#include "map.h"
#include "controls.h"
#include "gfx.h"
#include "configuration.h"

#define SIZE_X 800
#define SIZE_Y 600

void printscore (int x, int y, char *pretext, int value);
void printtime (int x, int y, char *pretext, int value);

#endif
