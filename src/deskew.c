/*
// Deskew functions
// Author: Hafid HOUSNI
*/
#include "deskew.h"

// Determine a skew angle using Hough transform method
// Not perfectly working
double find_angle(SDL_Surface *image)
{
    double angle=0;
    double ro;
    int max = sqrt((image->w*image->w) + (image->h*image->h));
    int *accu = calloc(max*180, sizeof(int));

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
            }
        }
    }

    //Find the angle of the max vote
    int maxvote = 0;
    for (int d = 0; d < max; d++)
    {
        for (double theta = 0; theta < 180; theta+=0.2)
        {
            if (accu[d + (int)theta * max] >= maxvote)
            {
                maxvote = accu[d + (int)theta * max];
                angle = theta;
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
SDL_Surface *Deskew(SDL_Surface *image)
{
    double angle = find_angle(image);
    image = Rotate(image, angle);

    return image;
}

int DeskewImage(char *file)
{
    SDL_Surface *image = load_img(file);
    SDL_Surface *deskew = Deskew(image);
    IMG_SavePNG(deskew, "tmp/deskew.png");

    return EXIT_SUCCESS;
}