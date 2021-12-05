/*
// Grid make functions
// Author: Hafid HOUSNI
*/
#include "grid.h"

// Matrix 9*9 representing the grid
char grid[9][9];

// Read the file and make the grid matrix
void file2grid(char *path)
{
    FILE *fp = fopen(path,"r");
    int row = 0, col = 0, jump = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c != ' ')
        {
            if (c == '\n')
            {
                if(jump < 3)
                {
                    jump++;
                    row++;
                    col = 0;
                }
                else
                {
                    jump = 0;
                    col = 0;
                }
            }
            else if (c == '.')
            {
                grid[row][col] = ' ';
                col++;
            }
            else
            {
                grid[row][col] = c;
                col++;
            }
        }
    }
    fclose(fp);
}

// Make a Surface from digit char
SDL_Surface *GetDigitSurface(char *c)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("assets/arial.ttf", 32);
    SDL_Color bg = { 255, 255, 255, 255 };
    SDL_Color fg = { 0, 0, 0, 0};
    SDL_Surface *number = TTF_RenderText_Shaded(font, c, fg, bg);
    TTF_CloseFont(font);
    TTF_Quit();
    return number;
}

// Function to make the grid image
int MakeGrid(char *path)
{
    char *img = "assets/grid.jpg";
    SDL_Surface *sdk = load_img(img);
    SDL_Surface *digit;
    SDL_Rect gridrect;
    
    file2grid(path);

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            char c[] = { ' ', (grid[i][j]), ' ', 0};
            digit = GetDigitSurface(c);
            gridrect.x = j*67 + 15;
            gridrect.y = i*67 + 15;
            SDL_BlitSurface(digit, NULL, sdk, &gridrect);
        }
    }
    IMG_SavePNG(sdk, "output/output.png");
    SDL_FreeSurface(digit);
    SDL_FreeSurface(sdk);

    return EXIT_SUCCESS;
}