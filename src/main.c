#include "main.h"

// Ask the user to display an image in path
void display(char *path)
{
    printf("Do you want to display the image? [Y/N]: ");
    char c;
    scanf(" %c",&c);
    if (c == 'Y' || c == 'y')
    {
        loader(path);
    }
    if (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
    {
        printf("Error : Please retry\n");
        display(path);
    }
}

// Ask user to binarize an image
void image2binarized(SDL_Surface *image)
{
    printf("Do you want to binarize the image? [Y/N]: ");
    char c;
    scanf(" %c",&c);
    if (c == 'Y' || c == 'y')
    {
        printf("Is your image noisy? [Y/N]: ");
        char n;
        scanf(" %c",&n);
        if (n == 'Y' || n == 'y')
        {
            image = Binarize(image,1);
        }
        else
        {
            image = Binarize(image,0);
        }
    }
    if (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
    {
        printf("Error : Please retry\n");
        image2binarized(image);
    }
}

// Ask user to apply noise reduction on binarized SDL_Surface *
void noisereduc(SDL_Surface *image)
{
    printf("Do you want to reduce noise of the image? [Y/N]: ");
    char c;
    scanf(" %c",&c);
    if (c == 'Y' || c == 'y')
    {
        image = Reduct_noise(image);
    }
    if (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
    {
        printf("Error : Please retry\n");
        noisereduc(image);
    }
}

// Ask user to rotate a SDL_Surface *
void Rot(SDL_Surface *image)
{
    printf("Do you want to rotate the image? [Y/N]: ");
    char c;
    scanf(" %c",&c);
    if (c == 'Y' || c == 'y')
    {
        printf("Enter the skew angle: ");
        double a;
        scanf(" %lf",&a);
        image = Deskew(image, a);
    }
    if (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
    {
        printf("Error : Please retry\n");
        Rot(image);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        errx(1,"kalytera: Usage : ./kalytera <path of image>");
    }

    char *path = argv[1];
    
    display(path);

    SDL_Surface *image = load_img(path);

    // Binarize
    image2binarized(image);
    display("tmp/binarized.png");

    // Getting binarized image
    path = "tmp/binarized.png";
    image = load_img(path);

    // Noise reduction
    noisereduc(image);
    display("tmp/noisereduced.png");

    // Getting noise reduced image
    path = "tmp/noisereduced.png";
    image = load_img(path);

    // Deskew
    Rot(image);
    display("tmp/deskew.png");

    return EXIT_SUCCESS;
}