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


// Otsu method to calculate the threshold for binarization
int OtsuThreshold(SDL_Surface *image)
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

// Use Otsu to binarize an image
SDL_Surface *OtsuBinarization(SDL_Surface *image)
{
    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    int s = OtsuThreshold(image);

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


// Adaptive Thresholding method for binarization
SDL_Surface *AdaptiveThresholdingBinarization(SDL_Surface *image, double k)
{
    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
    
    Uint32 pixel;
    Uint8 r, g, b;
    int pixel_value;

    long sum = 0;
    int x1, x2, y1,y2;
    int count = 0;
    unsigned long *intimg = (unsigned long*)
                        malloc(image->w*image->h*sizeof(unsigned long*));

    int win_length = image->w /16;
    int index;

    for (int i = 0; i < image->w; i++)
    {
        sum = 0;
        for (int j = 0; j < image->h; j++)
        {
            pixel = get_pixel(image, i, j);
            r = pixel >> 16 & 0xFF;
            g = pixel >> 8 & 0xFF;
            b = pixel & 0xFF;
            pixel_value = (r+g+b)/3;
            sum += pixel_value;

            index = j*image->w+i;

            if (i==0)
            {
                intimg[index] = sum;
            }
            else
            {
                intimg[index] = intimg[index - 1] + sum;
            }
        }
    }

    for (int i = 0; i < image->w; i++)
    {
        
        for (int j = 0; j < image->h; j++)
        {
            index = j*image->w+i;

            x1 = i - win_length;
            x2 = i + win_length;
            y1 = j - win_length;
            y2 = j + win_length;

            if (x1 < 0)
                x1 = 0;
            
            if (x2 >= image->w)
                x2 = image->w - 1;
            
            if (y1 < 0)
                y1 = 0;
            if (y2 >= image->h)
                y2 = image->h-1;
            
            count = (x2 - x1) * (y2 - y1);
            sum = intimg[y2 * image->w + x2] - 
                    intimg[y1 * image->w + x2] -
                    intimg[y2 * image->w + x1] + 
                    intimg[y1 * image->w + x1];
            
            pixel = get_pixel(image, i, j);
            r = pixel >> 16 & 0xFF;
            g = pixel >> 8 & 0xFF;
            b = pixel & 0xFF;
            pixel_value = (r+g+b)/3;

            if ((long)(pixel_value*count)<(long)(sum*(1.0-k)))
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
    free(intimg);
    return image;
}

// Creates a binarized image file from a colorized one
SDL_Surface *Binarize(SDL_Surface *image, int k)
{
    // Apply grayscale
    SDL_Surface *grayscaled = Img_to_Grayscale(image);
    IMG_SavePNG(grayscaled, "tmp/grayscaled.png");
    SDL_Surface *binarized;

    if (k)
    {
        // Apply binarization using Adaptive Threshold method
        binarized = AdaptiveThresholdingBinarization(grayscaled, 0.6); 
    }
    else
    {
        // Apply binarization using Otsu
        binarized = OtsuBinarization(grayscaled);
    }

    IMG_SavePNG(binarized, "tmp/binarized.png");
    SDL_FreeSurface(grayscaled);
    
    return binarized;
}