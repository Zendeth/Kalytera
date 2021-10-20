/*
// Binarization
// Author: Hafid HOUSNI
*/

#include "binarize.h"

// Convert a color SDL_Surface to grayscaled one
SDL_Surface *Img_to_Grayscale(SDL_Surface *image)
{
    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    Uint32 pixel;
    Uint8 r,g,b,v;

    for (int j = 0; j < image->h; ++j)
    {
        for (int i = 0; i < image->w; ++i)
        {
            pixel = get_pixel(image, i, j);

            r = pixel >> 16 & 0xFF;
            g = pixel >> 8 & 0xFF;
            b = pixel & 0xFF;

            v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;

            put_pixel(image, i, j, pixel);

        }
    }

    return image;
}

// Convert a grayscaled SDL_Surface to a binarized one
SDL_Surface *Grayscale_to_Binarization(SDL_Surface *image, int s)
{
    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    Uint32 pixel;
    Uint8 r, g, b, v;

    for (int j = 0; j < image->h; ++j)
    {
        for (int i = 0; i < image->w; ++i)
        {
            pixel = get_pixel(image, i, j);

            r = pixel >> 16 & 0xFF;
            g = pixel >> 8 & 0xFF;
            b = pixel & 0xFF;

            v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            if(v <= s)
            {
                r = 0;
                g = 0;
                b = 0;
            }
            else
            {
                r = 255;
                g = 255;
                b = 255;
            }

            pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;
            put_pixel(image, i, j, pixel);
        }
    }

    return image;
}

// Otsu method to calculate the threshold for binarization
int Otsu(SDL_Surface *image)
{
    Uint32 pixel;
    Uint8 r, g, b, v;
    int total_pixels = 0;
    int *histo = calloc(256, sizeof(int));

    for (int j = 0; j < image->h; j++)
    {
        for (int i = 0; i < image->w; i++)
        {
            pixel = get_pixel(image, i, j);

            r = pixel >> 16 & 0xFF;
            g = pixel >> 8 & 0xFF;
            b = pixel & 0xFF;

            v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            histo[v]++;
            total_pixels++;
        }
    }

    double q1 = 0, q2 = 0, m1 = 0, m2 = 0, w1 = 0, w2 = 0;
    double sum1 = 0, sum2 = 0, between = 0, max = 0;
    int threshold = 0;

	for (int i = 0; i < 256; i++) 
    {
		sum1 += histo[i];
		sum2 += histo[256 - i];

		w1 = sum1/ total_pixels;
        w2 = sum2 / total_pixels;
        q1 += i * histo[i];
        q2 += (256 - i) * histo[256 - i];
        m1 = q1 / sum1;
        m2 = q2 / sum2;
        between = w1 * w2 * (m1 - m2) * (m1 - m2);

		if (between > max) 
        {
			threshold = i;
			max = between;
		}
	}

    free(histo);
    
    return threshold;   
}

// Creates a binarized image file from a colorized one
SDL_Surface *Binarize(SDL_Surface *image)
{
    // Apply grayscale
    SDL_Surface *grayscaled = Img_to_Grayscale(image);

    // Find threshold using Otsu
    int threshold = Otsu(grayscaled);

    // Apply binarization on a grayscale image
    SDL_Surface *binarized = Grayscale_to_Binarization(grayscaled, threshold);

    IMG_SavePNG(binarized, "tmp/binarized.png");

    return binarized;
}