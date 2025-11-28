#include "Entities/MazeGrid.h"
using namespace std;

void create_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    grid.resize(height);
    for (int i=0; i<height;i++){
        grid[i].resize(width);
    }
    reset_maze(grid,height,width);
}
void reset_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    for (int i=0;i<height;i++){
        for ( int j=0;j<width;j++){
            grid[i][j].is_block=true;
            grid[i][j].visited=false;
        }
    }
}
void reset_maze_solve(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    for (int i=0;i<height;i++){
        for ( int j=0;j<width;j++){
            grid[i][j].visited=false;
        }
    }
}
