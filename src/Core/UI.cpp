#include "Core/UI.h"
#include "Entities/MazeGrid.h"
#include "raylib.h"
#include <iostream>

bool show_solution=false;
void set_show_solution(bool solution){
    show_solution=solution;
}

static Texture2D show_gen_step_on;
static Rectangle rect_show_gen_step{40, 50, 350, 150};
static Texture2D show_gen_step_off;

static Texture2D generate;
static Rectangle rect_generate{40,250,350,150};



bool is_turn_on_draw_when_generate(){
    return TURN_ON_DRAW_WHEN_GENERATE;
}
double draw_gen_time(){
    return DRAW_GEN_TIME;
}

static Texture2D show_solve_step_on;
static Rectangle rect_show_solve_step{40,450,350,150};
static Texture2D show_solve_step_off;

static Texture2D algo_dfs;
static Texture2D algo_bfs;
static Texture2D algo_a_star;
static Rectangle rect_algo{40,650,350,150};
int algo_type_int=0;
void change_algo_type_int_ui(int algo_type_int_ui){
    algo_type_int=algo_type_int_ui;
}

static Texture2D solve;
static Rectangle rect_solve{40,859,350,150};



bool is_turn_on_draw_when_solve(){
    return TURN_ON_DRAW_WHEN_SOLVE;
}
double draw_solve_time(){
    return DRAW_SOLVE_TIME;
}



user_action handle_ui_input(){
    Vector2 mouse_point=GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_show_gen_step)){
            TURN_ON_DRAW_WHEN_GENERATE=!TURN_ON_DRAW_WHEN_GENERATE;
            return user_action::NONE;
        }
        
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_generate)){
            return user_action::GENERATE;
        }
        
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_show_solve_step)){
            TURN_ON_DRAW_WHEN_SOLVE=!TURN_ON_DRAW_WHEN_SOLVE;
            return user_action::NONE;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_algo)){
            return user_action::CHANGE_ALGO;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse_point,rect_solve)){
            return user_action::SOLVE;
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

    generate=LoadTexture("assets/generate.png");
    SetTextureFilter(generate, TEXTURE_FILTER_TRILINEAR);

    show_solve_step_on=LoadTexture("assets/show_solve_step_on.png");
    SetTextureFilter(show_solve_step_on, TEXTURE_FILTER_TRILINEAR);
    show_solve_step_off=LoadTexture("assets/show_solve_step_off.png");
    SetTextureFilter(show_solve_step_off, TEXTURE_FILTER_TRILINEAR);

    algo_a_star=LoadTexture("assets/algo_a_star.png");
    SetTextureFilter(algo_a_star, TEXTURE_FILTER_TRILINEAR);
    algo_bfs=LoadTexture("assets/algo_bfs.png");
    SetTextureFilter(algo_bfs, TEXTURE_FILTER_TRILINEAR);
    algo_dfs=LoadTexture("assets/algo_dfs.png");
    SetTextureFilter(algo_dfs, TEXTURE_FILTER_TRILINEAR);

    solve=LoadTexture("assets/solve.png");
    SetTextureFilter(solve, TEXTURE_FILTER_TRILINEAR);



}
void unload_resource(){
    UnloadTexture(show_gen_step_off);
    UnloadTexture(show_gen_step_on);
    UnloadTexture(generate);
    UnloadTexture(show_gen_step_off);
    UnloadTexture(show_gen_step_on);
    UnloadTexture(algo_a_star);
    UnloadTexture(algo_bfs);
    UnloadTexture(algo_dfs);
    UnloadTexture(solve);
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

    Rectangle source_generate{0.0f,0.0f,(float)generate.width,(float)generate.height};
    DrawTexturePro(generate,source_generate,rect_generate,origin,0.0f,WHITE);

    Rectangle source_show_solve_step_on{0.0f,0.0f,(float)show_solve_step_on.width,(float)show_solve_step_on.height};
    Rectangle source_show_solve_step_off{0.0f,0.0f,(float)show_solve_step_off.width,(float)show_solve_step_off.height};

    if(is_turn_on_draw_when_solve()){
        DrawTexturePro(show_solve_step_on,source_show_solve_step_on,rect_show_solve_step,origin,0.0f,WHITE);
    }
    else{
        DrawTexturePro(show_solve_step_off,source_show_solve_step_off,rect_show_solve_step,origin,0.0f,WHITE);
    }

    Rectangle source_aglo_dfs{0.0f,0.0f,(float)algo_dfs.width,(float)algo_dfs.height};
    Rectangle source_aglo_bfs{0.0f,0.0f,(float)algo_bfs.width,(float)algo_bfs.height};
    Rectangle source_aglo_a_star{0.0f,0.0f,(float)algo_a_star.width,(float)algo_a_star.height};

    if(algo_type_int==0){
        DrawTexturePro(algo_bfs,source_aglo_bfs,rect_algo,origin,0.0f,WHITE);
    }
    else if(algo_type_int==1){
        DrawTexturePro(algo_dfs,source_aglo_dfs,rect_algo,origin,0.0f,WHITE);
    }
    else{
        DrawTexturePro(algo_a_star,source_aglo_a_star,rect_algo,origin,0.0f,WHITE);
    }

    Rectangle source_solve{0.0f,0.0f,(float)solve.width,(float)solve.height};
    DrawTexturePro(solve,source_solve,rect_solve,origin,0.0f,WHITE);

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


