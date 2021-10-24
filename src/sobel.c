/*
// Sobel Edge Detection
// Author: Hafid HOUSNI
*/

#include "sobel.h"

// Sobel function
SDL_Surface *Sobel(SDL_Surface *image)
{
    Uint32 pixel;
    Uint8 r, g, b;
    int pixel_value;

    // Define kernals matrixes
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};

    int Gx_v, Gy_v;
    int kx, ky;

    SDL_Surface *output = SDL_CreateRGBSurface(0,image->w,image->h,32,0,0,0,0);

    // loop through the image
    for (int i = 1; i < image->w - 1; i++)
    {
        for (int j = 1; j < image->h - 1; j++)
        {
            Gx_v = 0;
            Gy_v = 0;

            for (int x = -1 ; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    kx = x + 1; // Kernel x index
                    ky = y + 1; // Kernel y index

                    int a = i + x;
                    int b = j + y;

                    pixel = get_pixel(image, a, b);
                    r = pixel >> 16 & 0xFF;
                    g = pixel >> 8 & 0xFF;
                    b = pixel & 0xFF;

                    pixel_value = (r+g+b)/3;

                    // Gx kernel value
                    Gx_v += (pixel_value * Gx[kx][ky]);
                    
                    // Gy kernel value
                    Gy_v += (pixel_value * Gy[kx][ky]);
                
                }
            }

            // Sobel pixel value
            pixel_value = sqrt(Gx_v*Gx_v + Gy_v*Gy_v);

            // Capping at 255 if superior/ 0 if inferior
            if (pixel_value > 255) pixel_value = 255;
            if (pixel_value < 0) pixel_value = 0;

            // apply sobel to pixel and assign it on output image
            pixel = (0xFF << 24) | (pixel_value << 16) |
                                            (pixel_value << 8) | pixel_value;
            put_pixel(output, i, j, pixel);
        }
    }

    SDL_FreeSurface(image);

    return output;
}

SDL_Surface *SobelMain(SDL_Surface *image)
{
    SDL_Surface *output = Sobel(image);

    IMG_SavePNG(output, "tmp/sobel.png");

    return output;
}