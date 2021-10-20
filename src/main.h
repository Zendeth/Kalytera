#ifndef MAIN_H
#define MAIN_H

#include <err.h>

#include "loader.h"
#include "binarize.h"
#include "noisereduction.h"
#include "deskew.h"

void display(char *path);
void image2binarized(SDL_Surface *image);
void noisereduc(SDL_Surface *image);
void Rot(SDL_Surface *image);

int main(int argc, char *argv[]);
#endif