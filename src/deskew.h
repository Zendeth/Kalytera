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

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

struct values {
    double rho;
    double theta;
};

struct values *winner(int maxrho, int maxtheta, int maxrholen,
                                            int accu[maxtheta][maxrholen]);
void vote(int x, int y, int maxrho, int maxtheta, int maxrholen,
                    int accu[maxtheta][maxrholen], SDL_Surface *img);

double find_angle(SDL_Surface *image);
SDL_Surface *Rotate(SDL_Surface *image, double angle);
SDL_Surface *AutoRotate(SDL_Surface *image);
SDL_Surface *ManualRotate(SDL_Surface *image, double angle);

#endif