#pragma once
#include <vector>


struct cell;

static bool check_cell(int x,int y,const std::vector<std::vector<cell>> &grid,int height,int width);
static void carve_maze(int x,int y,std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
void break_wall(std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
void generate_maze(std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
