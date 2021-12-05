/*
// Deskew functions
// Author: Hafid HOUSNI
*/
#include "deskew.h"

// Find values of rho and theta
struct values *winner(int maxrho, int maxtheta, int maxrholen,
                                            int accu[maxtheta][maxrholen])
{
    double max = 0, winrho = 0, wintheta = 0;

    for (int r = 0; r < maxrholen; r++)
    {
        for (int t = 0; t < maxtheta; t++)
        {
            if (accu[t][r] < max) continue;
            max = accu[t][r];
            winrho = r;
            wintheta = t;
        }
    }
    
    double rho = ((double) winrho / maxrholen - 0.5) * maxrho;
    double theta = 1.5621178940501734278001322309137322008610 
                        - ((double) wintheta / maxtheta) * M_PI;

    struct values *values = malloc(sizeof(struct values));

    values->rho = rho;
    values->theta = theta;

    return values;
}

// voting function using an accumulator
void vote(int x, int y, int maxrho, int maxtheta, int maxrholen,
                    int accu[maxtheta][maxrholen], SDL_Surface *img)
{
    Uint8 r, g, b;
    SDL_GetRGB(get_pixel(img, x, y), img->format, &r, &g, &b); 

    if (!(r == 0 && g == 0 && b == 0)) // not black
        return;

    for (int theta_index = 0; theta_index < maxtheta; theta_index++)
    {
        double theta = ((double) theta_index / maxtheta) * M_PI;
        double rho = x * cos(theta) + y * sin(theta);
        int rho_index = (int) (0.5 + (rho / maxrho + 0.5) * maxrholen);
        accu[theta_index][rho_index]++;
    }
}

// Determine tha angle for the rotation
double find_angle(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    int maxrho = sqrt(width * width + height * height);
    int maxrholen = maxrho + 1;
    int maxtheta = 360;
    int accu[maxtheta][maxrholen];

    for (int i = 0; i < maxtheta; i++) {
        for (int j = 0; j < maxrholen; j++) {
            accu[i][j] = 0;
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            vote(x, y, maxrho, maxtheta, maxrholen, accu, image);
        }
    }

    struct values *values = winner(maxrho, maxtheta, maxrholen, accu);
    double angle = values->theta * 180 / M_PI;

    //printf("theta: %f \n", values->theta);
    //printf("rho: %f \n", values->rho);
    //printf("angle: %f \n", angle);

    if (values->theta < 0 && values->rho > 0)
        angle += 177.8;
    if (values->theta > 0 && values->rho < 0)
        angle -= 180;

    angle = (values->theta < 0) ? -angle + values->theta : -angle - values->theta;
    
    printf("angle after adjust: %f \n", angle);

    return angle;
}

// Rotate a SDL_Surface using a given angle
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

//Auto Rotate function
SDL_Surface *AutoRotate(SDL_Surface *image)
{
    double angle = find_angle(image);
    image = Rotate(image, angle);
    
    IMG_SavePNG(image, "tmp/deskew.png");

    return image;
}

// Manual rotate function
SDL_Surface *ManualRotate(SDL_Surface *image, double angle)
{
    image = Rotate(image, angle);
    IMG_SavePNG(image, "tmp/deskew.png");

    return image;
}