#pragma once
#include <vector>


struct cell;

static double EMPTY_SPACE=0;

static bool check_cell(int x,int y,const std::vector<std::vector<cell>> &grid,int height,int width);
static void carve_maze(int x,int y,std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
void break_wall(std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
double get_current_empty_space();
void update_empty_space(double new_empty_space);
void generate_maze(std::vector<std::vector<cell>> &grid,int height,int width,int cell_size);
