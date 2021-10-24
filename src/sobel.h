#ifndef SOBEL_H
#define SOBEL_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "pixel_operations.h"
#include "loader.h"

SDL_Surface *Sobel(SDL_Surface *image);
SDL_Surface *SobelMain(SDL_Surface *image);

#endif