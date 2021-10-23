#include "hough.h"

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

void hough(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    int half_width = width / 2;
    int half_heigth = height / 2;
    int count = 220;
    int num_rhos = 180;
    int num_thetas = 180;
    int rho,theta;

    int d = sqrt(width * width + height * height);
    int dtheta = 180 / num_thetas;
    int drhos = (2 * d) / num_rhos;

    int i;
    int thetas[181];
    int rhos[2*d+1];

    for (i = 0; i <= 180/dtheta; i++) thetas[i] = i*dtheta;
    for (i = 0; i <= 2*d/drhos; i++) rhos[i] = i*drhos;

    int cos_thetas[181], sin_thetas[181];

    for (i = 0; i <= 180; i += dtheta)
    {
        cos_thetas[i] = cos(degToRad(i));
        sin_thetas[i] = sin(degToRad(i));
    }

    int accu[2*d][2*d];

    Uint32 pixel;
    Uint8 r, g, b;
    size_t x,y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            pixel = get_pixel(image, x, y);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
                  
            if (r+g+b == 765)
            {
                int point[2] = {y - half_heigth, x - half_width};
                for (int t = 0; t < num_thetas;t++)
                {
                    rho = (point[1] * cos_thetas[t]) + (point[0] * sin_thetas[t]);
                    accu[rho][t]++;
                }
            }
        }
    }

    for (y = 0; y < 2*d; y++)
    {
        for (x = 0; x < 2*d; x++)
        {
            if (accu[y][x] > count)
            {
                rho = rhos[y];
                theta = thetas[x];
                int a = cos(degToRad(theta));
                int b = sin(degToRad(theta));
                int x0 = (a * rho) + half_width;
                int y0 = (b * rho) + half_heigth;
                int x1 = x0 + 1000 * (-b);
                int y1 = y0 + 1000 * (a);
                int x2 = x0 - 1000 * (-b);
                int y2 = y0 - 1000 * (a);
            }
        }
    }
}