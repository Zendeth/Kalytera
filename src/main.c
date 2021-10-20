#include "main.h"

// Ask the user to display an image in path
void display(char *path)
{
    printf("Do you want to display the image? [Y/N]:");
    char c = getchar();
    printf("\n");
    if (c == 'Y' || c == 'y')
    {
        loader(path);
    }
    else if (c != 'N' || c != 'n')
    {
        while (c != 'N' || c != 'n' || c != 'Y' || c != 'y')
        {
            printf("Do you want to display the image? [Y/N]:");
            c = getchar();
            printf("\n");
        }
        if (c == 'Y' || c == 'y')
        {
            loader(path);
        }
    }
}

// Ask user to binarize an image
void image2binarized(SDL_Surface *image)
{
    printf("Do you want to binarize the image? [Y/N]:");
    char c = getchar();
    printf("\n");
    if (c == 'Y' || c == 'y')
    {
        image = Binarize(image);
    }
    else if (c != 'N' || c != 'n')
    {
        while (c != 'N' || c != 'n' || c != 'Y' || c != 'y')
        {
            printf("Do you want to binarize the image? [Y/N]:");
            c = getchar();
            printf("\n");
        }
        if (c == 'Y' || c == 'y')
        {
            image = Binarize(image);
        }
    }
}

// Ask user to apply noise reduction on binarized SDL_Surface *
void noisereduc(SDL_Surface *image)
{
    printf("Do you want to reduce noise of the image? [Y/N]:");
    char c = getchar();
    printf("\n");
    if (c == 'Y' || c == 'y')
    {
        image = Reduct_noise(image);
    }
    else if (c != 'N' || c != 'n')
    {
        while (c != 'N' || c != 'n' || c != 'Y' || c != 'y')
        {
            printf("Do you want to reduce noise of the image? [Y/N]:");
            c = getchar();
            printf("\n");
        }
        if (c == 'Y' || c == 'y')
        {
            image = Reduct_noise(image);
        }
    }
}

// Ask user to rotate a SDL_Surface *
void Rot(SDL_Surface *image)
{
    printf("Do you want to rotate the image? [Y/N]:");
    char c = getchar();
    printf("\n");
    if (c == 'Y' || c == 'y')
    {
        //TODO: get angle function
        double angle;
        image = Deskew(image, angle);
    }
    else if (c != 'N' || c != 'n')
    {
        while (c != 'N' || c != 'n' || c != 'Y' || c != 'y')
        {
            printf("Do you want to reduce noise of the image? [Y/N]:");
            c = getchar();
            printf("\n");
        }
        if (c == 'Y' || c == 'y')
        {
            //TODO : get angle function
            double angle;
            image = Deskew(image, angle);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        errx(1,"Use : ./kalytera <path of image>");
    }

    char *path = argv[1];
    
    display(path);

    SDL_Surface *image = load_img(path);

    // Binarize
    image2binarized(image);
    display("tmp/binarized.png");

    // Noise reduction
    noisereduc(image);
    display("tmp/noisereduction.png");

    //DeskewImage("tmp/noisereducted.png");
    Rot(image);
    display("tmp/deskew.png");

    return EXIT_SUCCESS;
}