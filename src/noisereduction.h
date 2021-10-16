#ifndef NOISEREDUCTION_H
#define NOISEREDUCTION_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "pixel_operations.h"
#include "loader.h"

SDL_Surface *NoiseReduction(SDL_Surface *image);
int Reduct_noise(char *file);

#endif