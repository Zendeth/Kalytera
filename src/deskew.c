/*
// Deskew functions
// Author: Hafid HOUSNI
*/
#include "deskew.h"

int maxofcol(int *matrix, int col, int length)
{
    int max = matrix[col];
    for (int i = 1; i < length; i++)
    {
        if (max < matrix[col+i])
        {
            max = matrix[col+i];
        }
    }
    return max;
}

int index_of_max(int array[], int length)
{
    int i = 0;
    int max = array[i];
    for (i = 1; i < length; i++)
    {
        if (max < array[i])
        {
            max = array[i];
        }
    }
    return i;
}

// Determine a skew angle using Hough transform method
// 2nd Method : better performance, not perfecty working
double find_angle2(SDL_Surface *image)
{
    double angle=0;
    double ro;
    int pmax = sqrt((image->w*image->w) + (image->h*image->h));
    int *htable = calloc(pmax*90, sizeof(int));
    int arraymax[450];
    int index_arraymax = 0;
    int p;
    int maxival;

    // Calculate distance for different angles
    // And increment votes on accumulator accordingly
    for (double theta = 0; theta < 45; theta += 0.2)
    {
        for (int j = 0; j < image->h; ++j)
        {
            for (int i = 0; i < image->w; ++i)
            {
                Uint32 pixel = get_pixel(image, i, j);
                if (pixel == 0)
                {
                    ro = i * cos((theta*M_PI)/180) + j *sin((theta*M_PI)/180);
                    p = (int) ro + (int)(theta * 10);
                    htable[p]++;
                }
            }
        }
        if (((int)theta*10+1) % 90 == 0)
        {
            for (int k = 0; k <= 90; k++)
            {
                arraymax[index_arraymax] = maxofcol(htable,k,90);
                index_arraymax++;
            }
            
        }
        memset(htable, 0, pmax*90);
    }
    maxival = index_of_max(arraymax, 450);
    angle = maxival/10;

    free(htable);
    return angle;
}

// Determine a skew angle using Hough transform method
// 1st method : bad performance, not perfectly working
double find_angle(SDL_Surface *image)
{
    double angle=0;
    double ro;
    int max = sqrt((image->w*image->w) + (image->h*image->h));
    int *accu = calloc(max*180, sizeof(int));

    int maxvote = 0;

    // Calculate distance for different angles
    // And increment votes on accumulator accordingly
    for (int j = 0; j < image->h; ++j)
    {
        for (int i = 0; i < image->w; ++i)
        {
            for (double theta = 0; theta < 180; theta += 0.2)
            {
                ro = i * cos(theta) + j *sin(theta);
                accu[(int) ro + (int)theta * max]++;
                if (accu[(int) ro + (int)theta * max] >= maxvote)
                {
                    maxvote = accu[(int) ro + (int)theta * max];
                    angle = theta;
                }
            }
        }
    }

    free(accu);
    return angle;
}

// Rotate a SDL_Surface using an angle
SDL_Surface *Rotate(SDL_Surface *image, double angle)
{
    angle = -angle * M_PI / 180;
    double cos_a = cos(angle);
    double sin_a= sin(angle);

    int height = abs(-image->w * sin_a) + abs(image->h * cos_a);
    int width = abs(image->w * cos_a) + abs(image->h * cos_a);

    SDL_Surface *output = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);

    Uint32 pixel;

    for (int j = 0; j < output->h; ++j)
    {
        for (int i = 0; i < output->w ; ++i)
        {
            int n_h = (j - output->h / 2) * cos_a - (i - output->w / 2) * sin_a;
            n_h += image->h / 2;

            int n_w = (i - output->w / 2) * cos_a + (j - output->h / 2) * sin_a;
            n_w += image->w / 2;

            if (n_h > 0 && n_h <image->h && n_w > 0 && n_w <image->w)
            {
                pixel = get_pixel(image, n_w, n_h);
            }
            else
            {
                pixel = SDL_MapRGB(output->format, 255, 255, 255);
            }
            put_pixel(output, i, j, pixel);
        }
    }

    return output;
}

//Auto Deskew function
SDL_Surface *AutoDeskew(SDL_Surface *image)
{
    double angle = find_angle2(image);
    image = Rotate(image, angle);

    return image;
}

// Manual deskew function
SDL_Surface *Deskew(SDL_Surface *image, double angle)
{
    image = Rotate(image, angle);
    IMG_SavePNG(image, "tmp/deskew.png");

    return image;
}