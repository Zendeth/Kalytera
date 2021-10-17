#include "main.h"

int main(int argc, char *argv[])
{
    //Tests
    Binarize("samples/image_05.jpeg");
    Reduct_noise("tmp/binarized.png");

    DeskewImage("tmp/noisereducted.png");

    return EXIT_SUCCESS;
}