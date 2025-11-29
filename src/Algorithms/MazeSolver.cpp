#include "Algorithms/MazeSolver.h"
#include "Core/UI.h"
#include "Entities/MazeGrid.h"
#include <iostream>
#include "raylib.h"

using namespace std;

static bool check_cell(cell cell){
    if (cell.visited||cell.is_block){
        return false;
    }
    return true;
}
static bool depth_first_search_algorithm(int x,int y,std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size,int parent_x,int parent_y){
    
    grid[y][x].visited=true;
    grid[y][x].parent_x=parent_x;
    grid[y][x].parent_y=parent_y;
    cout << "Dang duyet: " << grid[y][x].parent_x << ", " << grid[y][x].parent_y << endl;
    if(grid[y][x].is_end==true){
        return true;
    }
    if(is_turn_on_draw_when_solve()){
        get_current_state(grid,cell_size);
        WaitTime(draw_solve_time());
    }
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
            if(depth_first_search_algorithm(x,y,grid,height,width,cell_size,parent_x,parent_y)){
                return true;
            }
        }
        x=parent_x;
        y=parent_y;
    }
    return false;
}

void depth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size){
    reset_maze_solve(grid,height,width);
    int start_x=1;
    int start_y=1;
    for(int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            if(grid[i][j].is_start==true){
                start_x=j;
                start_y=i;
            }
        }
    }
    if(depth_first_search_algorithm(start_x,start_y,grid,height,width,cell_size,start_x,start_y)){
    }
    else{
        
    }
}