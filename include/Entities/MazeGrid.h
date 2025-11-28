#pragma once
#include <vector>
struct cell{
    bool is_block;
    bool visited;
    int parent_x;
    int parent_y;
    cell(bool bl=true,bool vi=false,int non=0):is_block(bl),visited(vi),parent_x(non),parent_y(non){}
};
void create_maze(std::vector<std::vector<cell>> &grid,const int &height,const int &width);
void reset_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width);
void reset_maze_solve(std::vector<std::vector<cell>> &grid,const int &height,int const &width);
