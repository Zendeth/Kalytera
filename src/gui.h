#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Include SDL libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "loader.h"
#include "binarize.h"
#include "noisereduction.h"
#include "deskew.h"
#include "hough.h"
#include "sobel.h"
#include "grid.h"
#include "main.h"

int launch_gui();
#endif