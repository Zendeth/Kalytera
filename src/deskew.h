#ifndef DESKEW_H
#define DESKEW_H

// Include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "pixel_operations.h"
#include "loader.h"

#define M_PI 3.14159265358979323846

double find_angle2(SDL_Surface *image);

double find_angle(SDL_Surface *image);
SDL_Surface *Rotate(SDL_Surface *image, double angle);
SDL_Surface *AutoDeskew(SDL_Surface *image);
SDL_Surface *Deskew(SDL_Surface *image, double angle);

#endif