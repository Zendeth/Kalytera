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

void drawHough (int *accu, SDL_Surface *image);
int parametricIntersect(float r1, int t1, float r2, int t2, int *x, int *y);
void detectAngle(SDL_Surface *image, int *accu, int *intersectList);
void drawIntersect(SDL_Surface *image, int *intersectList);
void recDetectLargestSquare(SDL_Surface *image, int *intersectList, int x1, int y1, int *x, int  *y, int *side);
void detectLargestSquare(SDL_Surface *image, int *intersectList, int *x, int  *y, int *side);
void drawLargestSquare(SDL_Surface *image, int *intersectList);
SDL_Surface *hough(SDL_Surface *image);

#endif