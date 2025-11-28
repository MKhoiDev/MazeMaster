#include "Core/UI.h"
#include "Entities/MazeGrid.h"

static void draw_maze(const std::vector<std::vector<cell>> &grid,int cell_size){
    for ( int y=0; y< grid.size() ; y++){
        for (int x=0;x<grid[y].size();x++){
            int pos_x=x*cell_size;
            int pos_y=y*cell_size;
            if(grid[y][x].is_block){
                DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,DARKGRAY);
            }
            else if (grid[y][x].visited){
                DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,YELLOW);
            }
            else{
                DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,RAYWHITE);
            }
            // DrawRectangleLines(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,BLACK);
        }
    }
}

void setup_window(const int& height,const int& width,int& cell_size ){
    if(height>width){
        cell_size=WINDOW_HEIGHT/height;
    }
    else{
        cell_size=WINDOW_WIDTH/width;
    }
    InitWindow(cell_size*width+SYSTEM_WIDTH,cell_size*height, "MazeMaster - Raylib");
}
void get_current_state(const std::vector<std::vector<cell>> &grid,int cell_size ){
    BeginDrawing();
    ClearBackground(BLUE);
    draw_maze(grid,cell_size);
    EndDrawing();
}


