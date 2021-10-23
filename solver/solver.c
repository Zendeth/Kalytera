#include "solver.h"

//Load the sudoku grid from a text file
void load_grid(char file[], int grid[][9])
{
    FILE *fp;
    fp = fopen(file,"r");
    int row = 0;
    int column = 0;
    char c;
    int jump = 0;
    while((c = fgetc(fp)) != EOF)
    {
        if(c != ' ')
        {
            if(c == '\n')
            {
                if(jump < 3)
                {
                jump++;
                row++;
                column = 0;
                }
                else
                {
                    jump = 0;
                    column = 0;
                }

            }
            else if(c == '.')
            {
                grid[row][column] = 0;
                column++;
            }
            else
            {
                grid[row][column] = c - '0';
                column++;
            }
        }
    }
    fclose(fp);
}

void save_grid(char file[], int grid[][9])
{
    FILE *fp;
    fp = fopen(file,"w");
    int row = 1;
    int column = 0;

    for (int i = 0; i < 9; i++)
    {
        column = 0;
        for (int j = 0; j < 9; j++)
        {
            if (column == 3)
            {
                fprintf(fp," ");
                column = 0;
            }
            if (grid[i][j] == 0)
            {
                fprintf(fp,".");
            }
            else
            {
                fprintf(fp,"%d",grid[i][j]);
            }
            column++;
        }
        fprintf(fp,"\n");
        if (row == 3)
        {
            fprintf(fp,"\n");
            row = 0;
        }
        row++;
    }
}

void square_to_line(int tamp[], int line, int col, int grid[][9])
{
    int i, j, k;
    while ((line % 3) != 0) line--;
    while ((col % 3) != 0) col--;
    k = 0;
    for (i = line; i < line + 3; i++)
    {
        for (j = col; j < col + 3; j++)
        {
            tamp[k++] = grid[i][j];
        }
    }
}

int tile_check(int num, int line, int col, int grid[][9])
{
    int i;
    int temp[9];
    for (i = 0; i < 9; i++)
    {
        if (grid[line][i] == num) return 0;
    } 

    for (i = 0; i < 9; i++)
    {
        if (grid[i][col] == num) return 0;
    }

    square_to_line(temp, line, col, grid);
    for (i = 0; i < 9; i++)
    {
        if (temp[i] == num) return 0;
    }

    return 1;
}

int is_finish(int grid[][9])
{
    for (int line = 0; line < 9; line++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (grid[line][col] == 0 )
            {
                return 0;
            }
        }
    }
    return 1;
}

void solve(int grid[][9])
{
    int num_temp;
    for (int line = 0; line < 9; line++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (grid[line][col]) continue;
            for (int num = 1; num <= 9; num++)
            {
                if (!tile_check(num, line, col, grid)) continue;

                num_temp = grid[line][col];
                grid[line][col] = num;

                solve(grid);

                if (is_finish(grid)) return;

                grid[line][col] = num_temp;
            }
            return;
        }
    }
    return;
}