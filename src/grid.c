#include "grid.h"

char grid[9][9];

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

int MakeGrid(char *path)
{
    char *img = "assets/grid.jpg";
    SDL_Surface *sdk = load_img(img);
    SDL_Surface *digit;
    SDL_Rect digitrect, gridrect;
    
    file2grid(path);

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            //printf("%c |", grid[i][j]);
            char c[] = { ' ', (grid[i][j]), ' ', 0};
            digit = GetDigitSurface(c);
            gridrect.x = j*67 + 15;
            gridrect.y = i*67 + 15;
            digitrect.h = 36;
            digitrect.w = 36;
            SDL_BlitSurface(digit, &digitrect, sdk, &gridrect);
        }
        //printf("\n");
    }
    IMG_SavePNG(sdk, "output/output.png");
    SDL_FreeSurface(digit);
    SDL_FreeSurface(sdk);

    return EXIT_SUCCESS;
}