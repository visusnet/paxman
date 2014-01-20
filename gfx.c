#include "gfx.h"

TTF_Font *font;
SDL_Color fontcolor;
SDL_Surface *screen;

/*
* Function to create the main Surface
* w = width, h = height, res = bits
*/ 
void GFX_initScreen (int h, int w, int res)
{
	if ((screen = SDL_SetVideoMode (h, w, res, SDL_DOUBLEBUF | SDL_HWSURFACE)) == NULL)
	{
		printf ("Error: %s\n", SDL_GetError ());
		exit (0);
	}
}

/*
* Function to load a font
* path = Path to font, size = fontsize
*/
void GFX_initFont (char *path, int size)
{
	if ((font = TTF_OpenFont (path, size)) == NULL)
	{
		printf ("Error: %s\n", TTF_GetError ());
		exit (0);
	}	
}

/*
* Function to print text on the screen
* text = the text, x = xposition, y = yposition
*/
void GFX_printText (char *text, int x, int y)
{
	SDL_Rect dest;
	SDL_Surface *textsf;
	
	if ((textsf = TTF_RenderText_Solid (font, text, fontcolor)) == NULL)
		printf ("Error %s\n", TTF_GetError ());
		
	dest.x=x;
	dest.y=y;
	dest.h=textsf->h;
	dest.w=textsf->w;
	SDL_BlitSurface (textsf, NULL, screen, &dest);
	SDL_FreeSurface (textsf);
}

/*
* Function to set the default Font-color
* r = rvalue, g = gvalue, b=bvalue
*/
void GFX_setFontColor (int r, int g, int b)
{
	fontcolor.r = r;
	fontcolor.g = g;
	fontcolor.b = b;
}

/* 
* Function to blit a raw SDL_Surface on the screen
* surface = the surface, x = xpos, y=ypos
*/
void GFX_copySurface (SDL_Surface *surface, int x, int y)
{
	SDL_Rect dest;
	
	dest.x=x;
	dest.y=y;
	dest.h=20;
	dest.w=20;
	SDL_BlitSurface (surface, NULL, screen, &dest);
}

/*
* Function to load an SDL_Surface from a bmp-file
* target = the surface the image is loaded in, path = path to image
*/
SDL_Surface * GFX_loadImage (char *path)
{
	SDL_Surface *target;
	
	if ((target = SDL_LoadBMP (path)) == NULL)
		printf ("Error: %s\n", SDL_GetError());
		
	return target;
};

/*
* Function to update the entire screen, it's moer a wrapper
*/
void GFX_updateScreen ()
{
	SDL_UpdateRect (screen, 0, 0, 0, 0);
}

void GFX_clearScreen ()
{
	SDL_FillRect (screen, NULL, 0x000000);
}

/*
* load_tile
* Load a SDL_Surface tile from a bmpfile
* Todo: 
*	- Error to screen
*	- Support other image-formats
*/
static SDL_Surface *GFX_loadTile (char tilename)
{
	static SDL_Surface *coin, *wall, *empty, *pm, *ghost;
	char tmp[512];
	extern img_directory[256];

	// Will only be executed once
	if (coin == NULL)
	{
		snprintf (tmp, sizeof (tmp), "%scoin.bmp", img_directory);
		if ((coin = SDL_LoadBMP (tmp)) == NULL)
		{
			printf ("Error loading %s: %s.\n", tmp, SDL_GetError ());
			return NULL;
		}
	}
	if (wall == NULL)
	{
		snprintf (tmp, sizeof (tmp), "%swall.bmp", img_directory);
		if ((wall = SDL_LoadBMP (tmp)) == NULL)
		{
			printf ("Error loading %s: %s.\n", tmp, SDL_GetError ());
			return NULL;
		}
	}
	if (empty == NULL)
	{
		snprintf (tmp, sizeof (tmp), "%sempty.bmp", img_directory);
		if ((empty = SDL_LoadBMP (tmp)) == NULL)
		{
			printf ("Error loading %s: %s.\n", tmp, SDL_GetError ());
			return NULL;
		}
	}
	if (pm == NULL)
	{
		snprintf (tmp, sizeof (tmp), "%spacman.bmp", img_directory);
		if ((pm = SDL_LoadBMP (tmp)) == NULL)
		{
			printf ("Error loading %s: %s.\n", tmp, SDL_GetError ());
			return NULL;
		}
	}
	if (ghost == NULL)
	{
		snprintf (tmp, sizeof (tmp), "%sghost.bmp", img_directory);
		if ((ghost = SDL_LoadBMP (tmp)) == NULL)
		{
			printf ("Error loading %s: %s.\n", tmp, SDL_GetError ());
			return NULL;
		}
	}

	switch (tilename)
	{
		case 'c':
			return coin;
		break;
		case 'w':
			return wall;
		break;	
		case 'e':
			return empty;
		break;	
		case 'p':
			return pm;
		break;
		case 'g':
			return ghost;
		break;
		case 'q': 
			// Clear all the surfaces
			SDL_FreeSurface (coin); SDL_FreeSurface (wall); SDL_FreeSurface (empty);
		break;	
	}
	
	return NULL;
}

void GFX_copyFullMap (map_t *map)
{
	SDL_Rect dest;
	int x;
	int y;

	// Change that to make it dynamic
	dest.h = TILE_H;
	dest.w = TILE_W;

	for (x=0; x<=map->w-1; x++)
	{
		dest.x = x*TILE_W;
		
		for (y=0; y<=map->h-1; y++)
		{	
			dest.y = y*TILE_H;
			if (map->map[x][y].con == 'p')
				SDL_BlitSurface (map->map[x][y].player->view[map->map[x][y].player->face_direction], NULL, screen, &dest);
			else
				SDL_BlitSurface (GFX_loadTile(map->map[x][y].con), NULL, screen, &dest);
		}
	} 
			
	return;	
}
