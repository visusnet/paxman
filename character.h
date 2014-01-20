#ifndef _character_h
#define _character_h

#include <SDL/SDL.h>

typedef struct 
{
	int xpos;
	int ypos;
	int face_direction;
	SDL_Surface *view[5];	// 4 views for 4 possible directions 0=l, 1=r, 2=u, 3=d
	int points;
	int health;
} character_t;

SDL_Surface *load_character_face (int face);

#endif
