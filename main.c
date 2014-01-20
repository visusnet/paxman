#include "main.h"

int main (int argc, char **argv)
{
        SDL_Surface *screen, *tmp;
        SDL_Rect dest;
        SDL_Event e;
        map_t map;
        character_t player;
        int fc = 0, done = 0, ticks = 0, playtime = 0;
        char ptm[255];
        char fontpath[255];
	char std_map_directory[512];
	char tmptxt[255];

	extern char install_directory[256];
	extern char map_directory[256];
	extern char img_directory[256];
	extern char font_directory[256];
	extern char default_map[256];

	if (argc > 1)
	{
		if (strncmp (argv[1], "--help", sizeof(argv[1])) == 0)
		{
			shell_help (argv);
		}
		else if (strncmp (argv[1], "--maps", sizeof(argv[1])) == 0)
		{
			shell_maps ();
		}
		else if (strncmp (argv[1], "--config", sizeof(argv[1])) == 0)
		{
			dump_config ();
		}
	}

	if (SDL_Init (SDL_INIT_VIDEO)<0)
	{
		printf ("Error initializing SDL: %s.\n", SDL_GetError());
		exit (1);
	}

	atexit (SDL_Quit);

	// Init SDL_TTF
	if(TTF_Init()==-1) 
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	pm_configure (); //Load config

	snprintf (fontpath, sizeof(fontpath), "%s%s", font_directory, "font.ttf");
	
	GFX_initFont (fontpath, 12);
	GFX_setFontColor (0, 255, 0);

	GFX_initScreen (SIZE_X, SIZE_Y+30, 32);

	srand (time(NULL));

	snprintf (std_map_directory, sizeof (std_map_directory), "%s%s", map_directory, default_map);

	//Load map, default map if argv[1] is unset
	if (argc < 2)
		MAP_loadMap (std_map_directory, &map);
	else
	{
		snprintf (ptm,255, "%s%s", map_directory, argv[1]);
		MAP_loadMap (ptm, &map);
	}

	//Prepare character
	player.xpos = getx;
	player.ypos = gety;
	player.face_direction = 1;
	
	// Load paxmans faces
	sprintf (tmptxt, "%s%s", img_directory, "pmup.bmp");
	player.view[0] = GFX_loadImage (tmptxt);
	sprintf (tmptxt, "%s%s", img_directory, "pmright.bmp");
	player.view[1] = GFX_loadImage (tmptxt);
	sprintf (tmptxt, "%s%s", img_directory, "pmdown.bmp");
	player.view[2] = GFX_loadImage (tmptxt);
	sprintf (tmptxt, "%s%s", img_directory, "pmleft.bmp");
	player.view[3] = GFX_loadImage (tmptxt);
	
	if (player.view[2] == NULL)
		exit (0);

	player.points = 0;
	player.health = 100;
	// Write character into map
	map.map[getx][gety].con = 'p';
	map.map[getx][gety].player = &player;

	SDL_EnableKeyRepeat (10, 50);
	// Go into main loop
	while (1)
	{
		GFX_clearScreen ();

		if (map.coins == 0)
		{
			player.face_direction = 4;
			done=1;
		}

		while ( SDL_PollEvent(&e) )
		{
			switch (e.type)
			{
				case SDL_QUIT:
					exit(0);
				break;
				case SDL_KEYDOWN:
					if (!done)
					{
						switch (e.key.keysym.sym)
						{
							case 'w':
							case SDLK_UP:
								walk (&player, 0, &map);
							break;
							case 's':
							case SDLK_DOWN:
								walk (&player, 2, &map);
							break;
							case 'd':
							case SDLK_RIGHT:
								walk (&player, 1, &map);
							break;
							case 'a':
							case SDLK_LEFT:
								walk (&player, 3, &map);
							break;
						}
					}
				break;
			}
		}

		if (!done)
			if (SDL_GetTicks() >= ticks+200)
			{
				ticks = SDL_GetTicks ();
				if (move_ghosts (&map) == 0)
					done = 2;
			}

		GFX_copyFullMap (&map);
		
		// Print score
		printscore(10, SIZE_Y, "Score:", player.points);
		// Print time
		if(done == 0)
			playtime = SDL_GetTicks()/1000;
		printtime(SIZE_X-130, SIZE_Y, "Time:", playtime);
		
		GFX_setFontColor (255, 255, 255);		
		if (done == 1)
			GFX_printText ("You have won!", 365, 270);
		else if (done == 2)
		{
			GFX_printText ("Game over!", 365, 270);
			snprintf(tmptxt, sizeof(tmptxt), "Score: %d", player.points);
			GFX_printText (tmptxt, 370, 300);
		}

		GFX_updateScreen ();
	}
	return 0;
}

void printscore (int x, int y, char *pretext, int value)
{
	char tmptxt[255];
	GFX_setFontColor (255, 255, 255);
	GFX_printText (pretext, x, y+5);
	GFX_setFontColor (255, 0, 0);
	snprintf(tmptxt, sizeof(tmptxt), "%d", value);
	GFX_printText (tmptxt, x+50, y+5);
}

void printtime (int x, int y, char *pretext, int value)
{
	char tmptxt[255];
	int h,m,s;
	GFX_setFontColor (255, 255, 255);
	GFX_printText (pretext, x, y+5);
	
	GFX_setFontColor (255, 0, 0);
	h = value / 3600;
	m = value / 60;
	s = value;
	m = value / 60 - h*60;
	s = value - m*60;

	if(s < 10 && m < 10 && h < 10)
		snprintf(tmptxt, sizeof(tmptxt), "0%d : 0%d : 0%d", h, m, s); // 0:0:0
	else if(s < 10 && m < 10 && h >= 10)
		snprintf(tmptxt, sizeof(tmptxt), "%d : %d : 0%d", h, m, s); // x:x:0
	else if(s < 10 && m >= 10 && h < 10)
		snprintf(tmptxt, sizeof(tmptxt), "0%d : %d : %d", h, m, s); // 0:x:x
	else if(s >= 10 && m < 10 && h < 10)
		snprintf(tmptxt, sizeof(tmptxt), "0%d : 0%d : %d", h, m, s); // 0:0:x
	else if(s < 10 && m >= 10 && h >= 10)
		snprintf(tmptxt, sizeof(tmptxt), "0%d : %d : 0%d", h, m, s); // 0:x:0
	else if(s < 10 && m >= 10 && h >= 10)
		snprintf(tmptxt, sizeof(tmptxt), "%d : 0%d : 0%d", h, m, s); // x:0:0
	else if(s >= 10 && m >= 10 && h >= 10)
		snprintf(tmptxt, sizeof(tmptxt), "%d : %d : %d", h, m, s); // x:x:x
	else if(s >= 10 && m < 10 && h >= 10)
		snprintf(tmptxt, sizeof(tmptxt), "%d : %d : %d", h, m, s); // x:0:x
		
	GFX_printText (tmptxt, x+40, y+5);
}
