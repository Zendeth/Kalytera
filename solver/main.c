#include "main.h"

int main(int argc, char *argv[])
{
    int grid[9][9];
    load_grid(argv[1], grid);

    solve(grid);

    save_grid(strcat(argv[1],".result"), grid);

    return EXIT_SUCCESS;
}