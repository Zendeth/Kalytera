#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>

void load_grid(char file[], int grid[][9]);
void save_grid(char file[], int grid[][9]);
void square_to_line(int tamp[], int line, int col, int grid[][9]);
int tile_check(int num, int line, int col, int grid[][9]);
int is_finish(int grid[][9]);
void solve(int grid[][9]);

#endif