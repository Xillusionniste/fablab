/* --------------------------------------------
	File Name	: SDL_functions.h
 	Object		:
 	Creation	: DENECHAUD / HERIN
 ----------------------------------------------*/

#ifndef __SDL_FUNCTIONS_H
#define __SDL_FUNCTIONS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mutex.h>

#define WIDTH		1280
#define HEIGHT		720
#define NB_OF_COLORS	24
#define NB_PICTURES	15
#define X_POSITION	0
#define Y_POSITION	0

SDL_Surface *SDLOpenWindow (int options);
SDL_Surface *SetBackgroundPicture (	SDL_Surface *backgroundPicture,
					SDL_Surface *screen,
					int x_position,
					int y_position	);

#endif
