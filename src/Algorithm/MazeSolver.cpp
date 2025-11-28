#include "Algorithms/MazeSolver.h"
#include "Core/UI.h"
#include "Entities/MazeGrid.h"

using namespace std;

static bool check_cell(cell cell){
    if (cell.visited||cell.is_block){
        return false;
    }
    return true;
}
static void depth_first_search_algorithm(int x,int y,std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size,int parent_x,int parent_y){
    grid[y][x].visited=true;
    grid[y][x].parent_x=parent_x;
    grid[y][x].parent_y=parent_y;
    get_current_state(grid,cell_size);
    parent_x=x;
    parent_y=y;
    for ( int i=0;i<4;i++){
        if(i==0){
            x+=1;
        }
        if(i==1){
            x-=1;
        }
        if(i==2){
        y+=1;
        }
        if(i==3){
            y-=1;
        }
        if(check_cell(grid[y][x])){
            depth_first_search_algorithm(x,y,grid,height,width,cell_size,parent_x,parent_y);
        }
        x=parent_x;
        y=parent_y;
    }
}

void depth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size){
    reset_maze_solve(grid,height,width);
    depth_first_search_algorithm(1,1,grid,height,width,cell_size,1,1);
}