#pragma once
#include <vector>
struct cell{
    bool is_block;
    bool visited;
    bool is_start;
    bool is_end;
    int parent_x;
    int parent_y;
    int f;
    int g;
    
    cell(bool bl=true,bool vi=false,int non=0):is_block(bl),visited(vi),is_start(false),is_end(false),parent_x(non),parent_y(non),f(1e9),g(1e9){}
};
void create_maze(std::vector<std::vector<cell>> &grid,const int &height,const int &width);
void update_start_end(std::vector<std::vector<cell>> &grid,const int &start_x,const int &start_y,const int &end_x,const int  &end_y);
void reset_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width);
void reset_maze_solve(std::vector<std::vector<cell>> &grid,const int &height,int const &width);

