#include "controls.h"
#include "map.h"

void walk (character_t *player ,int direction, map_t *map)
{
	int xsum=0, ysum=0;

	switch ((player->face_direction = direction))
	{
		case 0: // up
			if (!map->map[player->xpos][player->ypos-1].solid && player->ypos > 0)
				ysum=-1;
			else
				return;			
		break;
		case 1: // right
			if (!map->map[player->xpos+1][player->ypos].solid && player->xpos < MAX_W)
				xsum=1;
			else
				return;
		break;
		case 2: // down
			if (!map->map[player->xpos][player->ypos+1].solid && player->ypos < MAX_H)
				ysum=1;
			else			
				return;
		break;	
		case 3: // left
			if (!map->map[player->xpos-1][player->ypos].solid && player->xpos > 0)
				xsum=-1;
			else
				return;
		break;
	}	

	map->map[player->xpos][player->ypos].con = 'e';		
	map->map[player->xpos][player->ypos].solid=0;
			
	player->xpos += xsum;
	player->ypos += ysum;
	
	if (map->map[player->xpos][player->ypos].con == 'c')
	{
		player->points++;
		map->coins--;
	}

	map->map[player->xpos][player->ypos].player = player;
	map->map[player->xpos][player->ypos].con = 'p';
}
