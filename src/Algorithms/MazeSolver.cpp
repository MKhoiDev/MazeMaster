#include "Algorithms/MazeSolver.h"
#include "Core/UI.h"
#include "Entities/MazeGrid.h"
#include <iostream>
#include <deque>
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
    // cout << "Dang duyet: " << grid[y][x].parent_x << ", " << grid[y][x].parent_y << endl;
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
void breadth_first_search(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size){
    deque<point> queue;
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
    point start;
    start.x=start_x;
    start.y=start_y;

    queue.push_back(start);
    while(queue.size()>0){
        point point=queue[0];
        if(grid[point.y][point.x].is_end){
            break;
        }
        for(int i=0;i<4;i++){
                int x=point.x;
                int y=point.y;
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
                    grid[y][x].parent_x=point.x;
                    grid[y][x].parent_y=point.y;
                    queue.push_back({x,y});
                    grid[y][x].visited=true;
                }
            }
            queue.pop_front();
            if(is_turn_on_draw_when_solve()){
            get_current_state(grid,cell_size);
            WaitTime(draw_solve_time());
            }
            }

}
static void insert_priority_queue(std::vector<std::vector<cell>> &grid,deque<point> &queue,const point new_point){
    queue.push_back(new_point);
    int i = queue.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2; 
        if (grid[queue[i].y][queue[i].x].f < grid[queue[parent].y][queue[parent].x].f) {
            std::swap(queue[i], queue[parent]);
            i = parent; 
        } else {
            break;
        }
    }
}
static void delete_priority_queue(std::vector<std::vector<cell>> &grid,deque<point> &queue){
    if (queue.empty()) return;
    queue[0]=queue.back();
    queue.pop_back();
    int i=0;
    int size=queue.size();
    while(true){
        int smallest=i;
        int right=i*2+2;
        int left=i*2+1;
        if(left<size){
            if (grid[queue[smallest].y][queue[smallest].x].f>=grid[queue[left].y][queue[left].x].f){
                smallest=left;
            }
        }
        if(right<size){
            if (grid[queue[smallest].y][queue[smallest].x].f>=grid[queue[right].y][queue[right].x].f){
                smallest=right;
            }
        }

        if(smallest!=i){
            swap(queue[i],queue[smallest]);
            i=smallest;
        }
        else{
            break;
        }
    }

}

void a_star(std::vector<std::vector<cell>> &grid,const int &height,const int &width,const int& cell_size){
    deque<point> queue;
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
    int end_x=width;
    int end_y=height;
    for(int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            if(grid[i][j].is_end==true){
                end_x=j;
                end_y=i;
            }
        }
    }
    point start;
    start.x=start_x;
    start.y=start_y;
    insert_priority_queue(grid,queue,start);
    grid[start.y][start.x].parent_y=start.y;
    grid[start.y][start.x].parent_x=start.x;
    grid[start.y][start.x].g=0;
    int h_start = abs(end_y - start.y) + abs(end_x - start.x);
    grid[start.y][start.x].f = 0 + h_start;

    while(queue.size()>0){
        point point=queue[0];
        delete_priority_queue(grid,queue);
        // cout << "Pop: " << point.x << "," << point.y 
        //     << " | F=" << grid[point.y][point.x].f 
        //     << " | G=" << grid[point.y][point.x].g << endl;
        if(grid[point.y][point.x].is_end){
            break;
        }
        grid[point.y][point.x].visited=true;
        for(int i=0;i<4;i++){
                int x=point.x;
                int y=point.y;
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
                if (x >= 0 && x < width && y >= 0 && y < height){
                    if(grid[y][x].is_block){
                        continue;
                    }
                    if (grid[y][x].visited){
                        continue;
                    }
                    int new_g=grid[point.y][point.x].g+1;
                    if(grid[y][x].g>new_g){
                    grid[y][x].parent_y=point.y;
                    grid[y][x].parent_x=point.x;
                    grid[y][x].g=new_g;
                    grid[y][x].f=grid[y][x].g+(abs(end_y-y)+abs(end_x-x));
                    insert_priority_queue(grid,queue,{x,y});
                    }
                }
            }
        
        if(is_turn_on_draw_when_solve()){
            get_current_state(grid,cell_size);
            WaitTime(draw_solve_time());
        }

    }
    // cout << "End while";
}