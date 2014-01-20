#include "gui.h"

TTF_Font *font;

void load_font (char *fonts)
{
	if (!font)
		if ((font = TTF_OpenFont (fonts, 24)) == NULL)
		{
			printf ("Error: %s.\n", TTF_GetError ());
			exit (0);
		}
}

void paint_text (SDL_Surface *screen, char *text, int x, int y)
{
	SDL_Surface *textsf;
	SDL_Color color;
	SDL_Rect dest;

	color.r = 255;
	color.g = 0;
	color.b = 0;

	if((textsf = TTF_RenderText_Solid(font, text, color))==NULL)
	{
		printf ("Error: %s.\n", TTF_GetError ());
		exit (0);
	}

	dest.x=x; dest.y=y;
	dest.h=textsf->h;
	dest.w=textsf->w;

	SDL_BlitSurface (textsf, NULL, screen, &dest);
}
