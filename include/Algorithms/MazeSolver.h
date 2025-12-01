#pragma once

#include <vector>
struct cell;

static bool check_cell(cell cell);
static bool depth_first_search_algorithm(int x,int y,std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size,int parent_x,int parent_y);
void depth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size);

void breadth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size);
struct Point{
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};
