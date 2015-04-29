// ----------------------------------------------
// File Name		: SDL_functions.c
// Object		:
// Creation		: DENECHAUD / HERIN
// ----------------------------------------------

#include "SDL_functions.h"

extern int page_index;
extern char *picture[NB_PICTURES];

SDL_Surface *SDLOpenWindow (int options)
{
	// Starting SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	//Open a Window
	return SDL_SetVideoMode(WIDTH, HEIGHT, NB_OF_COLORS, options);
}

SDL_Surface *SetBackgroundPicture (	SDL_Surface *backgroundPicture,
					SDL_Surface *screen,
					int x_position,
					int y_position	)
{
	SDL_Rect backgroundPosition;
	backgroundPosition.x = x_position;
	backgroundPosition.y = y_position;

	backgroundPicture = SDL_LoadBMP(picture[page_index]);
	if ( backgroundPicture == NULL ) printf("Error:  Picture Loading\n");
	SDL_BlitSurface ( backgroundPicture, NULL, screen, &backgroundPosition);
	SDL_Flip(screen);
	printf("Screen Fliped\n");
	return backgroundPicture;
}			
