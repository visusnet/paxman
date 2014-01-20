#ifndef _ghost_h
#define _ghost_h

#include "map.h"
#include <time.h>

#define RNDM_LIMIT 20
#define RNDM_BORDER 10

int move_ghosts (map_t *map);
int check4pax (map_t *map, int dir, int i);
int GHOST_getNewDirection ();

#endif
