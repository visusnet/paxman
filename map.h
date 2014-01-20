#ifndef _map_h
#define _map_h

#include <SDL/SDL.h>
#include "character.h"
int getx, gety;

#define MAX_W 40
#define MAX_H 30
#define MAX_GHOSTS 5
#define TILE_H 20
#define TILE_W 20

typedef struct 
{
	int xpos;
	int ypos;
	int leave_coin;
	int direction;
	SDL_Surface *sf;
} ghost_t;

typedef struct
{
	SDL_Surface *sf;		// Visible surface
	int solid;	 		// May pacman be on it
	char con;			// Of which type is its content
	character_t *player; 		// Space for saving a player on this field
} map_tile_t;

typedef struct 
{
	char *mapname;				// Name of the map
	map_tile_t map[MAX_W][MAX_H];	// The map itself
	ghost_t ghost[MAX_GHOSTS];
	int w;
	int h;
	SDL_Surface *bg;
	int coins;
	int ghosts;
} map_t;

#include "ghost.h"

void MAP_loadMap (char *filename, map_t *temp);

#endif

