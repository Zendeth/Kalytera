#ifndef BINARIZE_H
#define BINARIZE_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

int Grayscale(char *file);
SDL_Surface * Img_to_Grayscale(SDL_Surface *image);

int Otsu(SDL_Surface *image);
SDL_Surface * Grayscale_to_Binarization(SDL_Surface *image, int s);

int Binarize(char *file);

#endif