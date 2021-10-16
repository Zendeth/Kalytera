#include "main.h"

int main(int argc, char *argv[])
{
    //Tests
    Binarize("samples/image_02.jpeg");
    Reduct_noise("samples/image_02.jpeg");

    return EXIT_SUCCESS;
}