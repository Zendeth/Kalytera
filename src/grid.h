#ifndef GRID_H_
#define GRID_H_

#include <stdio.h>
#include <stdlib.h>

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "loader.h"

void file2grid(char *path);
SDL_Surface *GetNumberSurface(char *c);
int MakeGrid(char *path);

#endif
