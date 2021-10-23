#ifndef BINARIZE_H
#define BINARIZE_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "pixel_operations.h"
#include "loader.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

SDL_Surface *Img_to_Grayscale(SDL_Surface *image);

int OtsuThreshold(SDL_Surface *image);
SDL_Surface *OtsuBinarization(SDL_Surface *image);

SDL_Surface *AdaptiveThresholdingBinarization(SDL_Surface *image, double k);

SDL_Surface *Binarize(SDL_Surface *image, int k);

#endif