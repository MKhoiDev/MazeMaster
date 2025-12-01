#include "Core/UI.h"
#include "Entities/MazeGrid.h"
#include "raylib.h"
#include <iostream>

bool show_solution=false;
void set_show_solution(bool solution){
    show_solution=solution;
}

static Texture2D show_gen_step_on;
static Rectangle rect_show_gen_step{40, 100, 300, 150};
static Texture2D show_gen_step_off;

bool is_turn_on_draw_when_generate(){
    return TURN_ON_DRAW_WHEN_GENERATE;
}
double draw_gen_time(){
    return DRAW_GEN_TIME;
}



bool is_turn_on_draw_when_solve(){
    return TURN_ON_DRAW_WHEN_SOLVE;
}
double draw_solve_time(){
    return DRAW_SOLVE_TIME;
}



void handle_ui_input(){
    Vector2 mouse_point=GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_show_gen_step)){
            TURN_ON_DRAW_WHEN_GENERATE=!TURN_ON_DRAW_WHEN_GENERATE;
        }
        
    }
}
static void draw_maze(const std::vector<std::vector<cell>> &grid,int cell_size){
    for ( int y=0; y< grid.size() ; y++){
        for (int x=0;x<grid[y].size();x++){
            int pos_x=x*cell_size;
            int pos_y=y*cell_size;
            if(grid[y][x].is_start){
                DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,GREEN);
                DrawRectangleLines(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,BLACK);
                continue;
            }
            if(grid[y][x].is_end){
                DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,RED);
                DrawRectangleLines(SYSTEM_WIDTH+pos_x,pos_y,cell_size,cell_size,BLACK);
                continue;
            }
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
void draw_solution_path(const std::vector<std::vector<cell>> &grid,const int &cell_size){
    bool found = false;
    int x=0;
    int y=0;
    for (int i=0;i<grid.size();i++){
        for (int j =0; j<grid[i].size();j++){
            if(grid[i][j].is_end){
                x=j;
                y=i;
                found=true;
            }
        }
    }
    if(!found){
        return;
    }
    double size=cell_size;
    while(!grid[y][x].is_start){
        int pos_x=x*cell_size;
        int pos_y=y*cell_size;
        if(!grid[y][x].is_end&&!grid[y][x].is_start){
            DrawRectangle(SYSTEM_WIDTH+pos_x,pos_y,size,size,PINK);
        }
        int next_x=grid[y][x].parent_x;
        int next_y=grid[y][x].parent_y;
        x=next_x;
        y=next_y;
        
    }
}
void get_position( int &start_x,int &end_x,int &start_y,int &end_y,const int &cell_size){
    Vector2 position=GetMousePosition();
    if(position.x<SYSTEM_WIDTH){
        return;
    }
    position.x-=SYSTEM_WIDTH;
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    start_x=position.x/cell_size;
    start_y=position.y/cell_size;
    }
    else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
    end_x=position.x/cell_size;
    end_y=position.y/cell_size;
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
void load_resource(){
    show_gen_step_on=LoadTexture("assets/show_gen_step_on.png");
    SetTextureFilter(show_gen_step_on, TEXTURE_FILTER_TRILINEAR);
    show_gen_step_off=LoadTexture("assets/show_gen_step_off.png");
    SetTextureFilter(show_gen_step_off, TEXTURE_FILTER_TRILINEAR);
}
void unload_resource(){
    UnloadTexture(show_gen_step_off);
    UnloadTexture(show_gen_step_on);
}
void draw_slidebar(){
    
    Rectangle source_show_gen_step_on{0.0f,0.0f,(float)show_gen_step_on.width,(float)show_gen_step_on.height};
    Rectangle source_show_gen_step_off{0.0f,0.0f,(float)show_gen_step_off.width,(float)show_gen_step_off.height};
    Vector2 origin{0.0f,0.0f};
    if(is_turn_on_draw_when_generate()){
        DrawTexturePro(show_gen_step_on,source_show_gen_step_on,rect_show_gen_step,origin,0.0f,WHITE);
    }
    else{
        DrawTexturePro(show_gen_step_off,source_show_gen_step_off,rect_show_gen_step,origin,0.0f,WHITE);
    }
}

void get_current_state(const std::vector<std::vector<cell>> &grid,int cell_size ){
    BeginDrawing();
    ClearBackground(BLACK);
    draw_maze(grid,cell_size);
    draw_slidebar();
    if(show_solution){
        draw_solution_path(grid,cell_size);
    }
    EndDrawing();
}


