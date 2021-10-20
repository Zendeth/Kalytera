/*
// Noise reduction functions
// Author: Hafid HOUSNI
*/
#include "noisereduction.h"

// Insertion sort function
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Noise reduction function
// using a medium filter using a 3*3 window
SDL_Surface *NoiseReduction(SDL_Surface *image)
{
    image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    Uint32 pixel;

    int window[9];

    for (int j = 0; j < image->h; ++j)
    {
        for (int i = 0; i < image->w; ++i)
        {
            // Border cases
            if (i==0)
            {
                if (j == 0)
                {
                    window[0] = get_pixel(image, i, j);
                    window[1] = get_pixel(image, i, j);
                    window[2] = get_pixel(image, i, j+1);
                    window[3] = get_pixel(image, i, j);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i+1, j);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j+1);
                }
                else if (j==(image->h-1))
                {
                    window[0] = get_pixel(image, i, j-1);
                    window[1] = get_pixel(image, i, j);
                    window[2] = get_pixel(image, i, j);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j);
                    window[6] = get_pixel(image, i+1, j-1);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j);
                }
                else
                {
                    window[0] = get_pixel(image, i, j-1);
                    window[1] = get_pixel(image, i, j);
                    window[2] = get_pixel(image, i, j+1);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i+1, j-1);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j+1);
                }
            }
            else if (i == (image->w-1))
            {
                if (j == 0)
                {
                    window[0] = get_pixel(image, i-1, j);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j+1);
                    window[3] = get_pixel(image, i, j);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i, j);
                    window[7] = get_pixel(image, i, j);
                    window[8] = get_pixel(image, i, j+1);
                }
                else if (j == (image->h-1))
                {
                    window[0] = get_pixel(image, i-1, j-1);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j);
                    window[6] = get_pixel(image, i, j-1);
                    window[7] = get_pixel(image, i, j);
                    window[8] = get_pixel(image, i, j);
                }
                else
                {
                    window[0] = get_pixel(image, i-1, j-1);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j+1);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i, j-1);
                    window[7] = get_pixel(image, i, j);
                    window[8] = get_pixel(image, i, j+1);
                }
            }
            else if (i<(image->w-1))
            {
                if (j==0)
                {
                    window[0] = get_pixel(image, i-1, j);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j+1);
                    window[3] = get_pixel(image, i, j);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i+1, j);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j+1);
                }
                else if (j==(image->h-1))
                {
                    window[0] = get_pixel(image, i-1, j-1);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j);
                    window[6] = get_pixel(image, i+1, j-1);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j);
                }
                else
                {
                    window[0] = get_pixel(image, i-1, j-1);
                    window[1] = get_pixel(image, i-1, j);
                    window[2] = get_pixel(image, i-1, j+1);
                    window[3] = get_pixel(image, i, j-1);
                    window[4] = get_pixel(image, i, j);
                    window[5] = get_pixel(image, i, j+1);
                    window[6] = get_pixel(image, i+1, j-1);
                    window[7] = get_pixel(image, i+1, j);
                    window[8] = get_pixel(image, i+1, j+1);
                }
            }

            insertionSort(window,9);

            // Apply medium value to the pixel and put it back to image
            pixel = window[4];
            put_pixel(image, i, j, pixel);
        }
    }
    return image;
}

SDL_Surface *Reduct_noise(SDL_Surface *image)
{
    SDL_Surface *noisereducted = NoiseReduction(image);
    IMG_SavePNG(noisereducted, "tmp/noisereducted.png");
    return noisereducted;
}