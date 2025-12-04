#pragma once

#include <vector>
struct cell;

struct point{
    int x;
    int y;

    point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

enum class algo{
    A_STAR,
    BFS,
    DFS,
};

void depth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size);

void breadth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size);

void a_star(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size);

void change_algo_type_int_ui(int algo_type_int_ui);