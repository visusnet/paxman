#include "ghost.h"

int move_ghosts (map_t *map)
{
	int i, y, changedir=0, detected=0;
	int c, xsum=0, ysum=0;
	
	for (i=0; i<=map->ghosts-1; i++)
	{
		//printf ("(%d|%d) ", map->ghost[i].xpos, map->ghost[i].ypos);
		// Clear current location

		xsum=0; ysum=0;

		
		map->ghost[i].direction = check4pax (map, map->ghost[i].direction, i);
		
		switch (map->ghost[i].direction)
		{
			case 0:
				if (!map->map[map->ghost[i].xpos][map->ghost[i].ypos-1].solid && map->ghost[i].ypos > 0)
					ysum=-1;
				else
				{
					map->ghost[i].direction = getNewDirection ();
					continue;
				}
				
			break;
			case 1:
				if (!map->map[map->ghost[i].xpos+1][map->ghost[i].ypos].solid && map->ghost[i].xpos < MAX_W)
					xsum=1;
				else
				{
					map->ghost[i].direction = getNewDirection ();
					continue;
				}
			break;
			case 2:
				if (!map->map[map->ghost[i].xpos][map->ghost[i].ypos+1].solid && map->ghost[i].ypos < MAX_H)
					ysum=1;
				else			
				{
					map->ghost[i].direction = getNewDirection ();
					continue;
				}	
			break;	
			case 3:
				if (!map->map[map->ghost[i].xpos-1][map->ghost[i].ypos].solid && map->ghost[i].xpos > 0)
					xsum=-1;
				else				
				{
					map->ghost[i].direction = getNewDirection ();
					continue;
				}
			break;
		}
	
		if (map->ghost[i].leave_coin)
		{
			map->map[map->ghost[i].xpos][map->ghost[i].ypos].con = 'c';
			map->ghost[i].leave_coin = 0;
			
		}
		else
			map->map[map->ghost[i].xpos][map->ghost[i].ypos].con = 'e';
			
		map->map[map->ghost[i].xpos][map->ghost[i].ypos].solid=0;
				
		map->ghost[i].xpos += xsum;
		map->ghost[i].ypos += ysum;

		switch (map->map[map->ghost[i].xpos][map->ghost[i].ypos].con)
		{
			case 'p':
				return 0;
			break;
			case 'g':
				continue;
			break;
			case 'c':
				map->ghost[i].leave_coin = 1;
			break;				
		}

		map->map[map->ghost[i].xpos][map->ghost[i].ypos].con = 'g';
		map->map[map->ghost[i].xpos][map->ghost[i].ypos].solid=1;
	}
	return 1;
}

int check4pax (map_t *map, int dir, int i)
{		
	int y;
		
	for (y=map->ghost[i].ypos; y>=0; y--)
	{
		if (map->map[map->ghost[i].xpos][y].con=='w')
			break;
		if (map->map[map->ghost[i].xpos][y].con=='p')
			return 0;
	}

	for (y=map->ghost[i].ypos; y<=MAX_H; y++)
	{
		if (map->map[map->ghost[i].xpos][y].con=='w')
			break;
		if (map->map[map->ghost[i].xpos][y].con=='p')
			return 2;
	}

	for (y=map->ghost[i].xpos; y>=0; y--)
	{
		if (map->map[y][map->ghost[i].ypos].con=='w')
			break;
		if (map->map[y][map->ghost[i].ypos].con=='p')
			return 3;
	}
		
	for (y=map->ghost[i].xpos; y<=MAX_H; y++)
	{
		if (map->map[y][map->ghost[i].ypos].con=='w')
			break;
		if (map->map[y][map->ghost[i].ypos].con=='p')
			return 1;
	}	
	
	return dir;
	
}

int getNewDirection ()
{
	static int i=0;
	
	if (i==4)
	{
		i=0;
		srand (time(NULL));
	}
	else
		i++;
		
	return rand () % 4;
}
