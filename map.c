#include "map.h"

/*
* load_map ()
* Load a map from a file and pack it into a struct
* Todo: 
*	- Output Error not to stdio but to screen
*/
void MAP_loadMap (char *filename, map_t *temp)
{
	FILE *fp;
	char c;
	int x, y, oldx;
	
	if ((fp = fopen (filename, "r")) == NULL)
	{
		perror ("MAP_loadMap");
		exit (1);
	}
	
	x=0; y=0;
	temp->coins=0;
	temp->ghosts=0;
	
	while ((c = fgetc (fp)) != EOF)
	{
		switch (c)
		{
			case 'w':
				temp->map[x][y].solid=1;
				if (x==MAX_W)
				{
					printf ("Error. Invalid mapfile!");
					exit (0);
				}
			break;
			case 'p':
				temp->map[x][y].solid=0;
				getx = x;
				gety = y;
				if (x==MAX_W)
				{
					printf ("Error. Invalid mapfile!");
					exit (0);
				}			
			break;			
			case 'c':
				temp->map[x][y].solid=0;
				temp->coins++;
				if (x==MAX_W)
				{
					printf ("Error. Invalid mapfile!");
					exit (0);
				}				
			break;
			case 'g':
				temp->map[x][y].solid=1;
				temp->ghost[temp->ghosts].xpos=x;
				temp->ghost[temp->ghosts].ypos=y;
				temp->ghost[temp->ghosts].direction=1;
				temp->ghost[temp->ghosts].leave_coin = 0;
				temp->ghosts++;
				if (x==MAX_W)
				{
					printf ("Error. Invalid mapfile!");
					exit (0);
				}				
			break;
			case '\n':
				if (y==MAX_H)
				{
					printf ("Error. Invalid mapfile!");
					exit (0);
				}
				oldx=x;
				x=0;
				y++;

				continue;
			break;
			default:
				continue;
			break;
		}

		//temp->map[x][y].sf = load_tile (c);
		temp->map[x][y].con = c;
		x++;
	}
	
	temp->mapname = filename;
	temp->w = oldx;
	temp->h = y;
	//temp->bg = load_tile ('e');
}




