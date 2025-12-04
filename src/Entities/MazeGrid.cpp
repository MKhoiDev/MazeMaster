#include "Entities/MazeGrid.h"
using namespace std;

void create_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    grid.resize(height);
    for (int i=0; i<height;i++){
        grid[i].resize(width);
    }
    reset_maze(grid,height,width);
}
void update_start_end(std::vector<std::vector<cell>> &grid,const int &start_x,const int &start_y,const int &end_x,const int  &end_y){
    if(start_x>=0&&start_y>=0){
    if(!grid[start_y][start_x].is_block){
        for(auto &i:grid){
            for(auto &j:i){
                j.is_start=false;
            }
        }
        grid[start_y][start_x].is_start=true;
        
    }}
    if(end_x>=0&&end_y>=0){
    if(!grid[end_y][end_x].is_block){
        for(auto &i:grid){
            for(auto &j:i){
                j.is_end=false;
            }
        }
        grid[end_y][end_x].is_end=true;
    }}
}
void reset_maze(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    for (int i=0;i<height;i++){
        for ( int j=0;j<width;j++){
            grid[i][j].is_block=true;
            grid[i][j].visited=false;
            grid[i][j].is_start=false;
            grid[i][j].is_end=false;
            grid[i][j].parent_x=0;
            grid[i][j].parent_y=0;
            grid[i][j].f=1e9;
            grid[i][j].g=1e9;

        }
    }
}
void reset_maze_solve(std::vector<std::vector<cell>> &grid,const int &height,int const &width){
    for (int i=0;i<height;i++){
        for ( int j=0;j<width;j++){
            grid[i][j].visited=false;
            grid[i][j].parent_x=0;
            grid[i][j].parent_y=0;
            grid[i][j].f=1e9;
            grid[i][j].g=1e9;
        }
    }
}
