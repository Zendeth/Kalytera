#ifndef HOUGH_H
#define HOUGH_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "pixel_operations.h"
#include "loader.h"

void hough(SDL_Surface *image);
void drawLine(SDL_Surface *image, int x0, int y0, int x1, int y1, Uint32 pixel);

#endif