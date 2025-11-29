#include "Core/Engine.h"
#include "Core/UI.h"
#include "Algorithms/MazeGenerator.h"
#include "Algorithms/MazeSolver.h"
#include "raylib.h"
#include <ctime>
#include <cstdlib>
using namespace std;

engine::engine(int height ,int width):height(height),width(width),cell_size(0),is_running(true),start_x(-1),start_y(-1),end_x(-1),end_y(-1){}

void engine::generate_maze(){
    ::generate_maze(grid,height,width,cell_size);
}
void engine::solve_maze(){
    ::depth_first_search(grid,height,width,cell_size);
}
void engine::init(){
    ::setup_window(height,width,cell_size);
    load_resource();
    SetTargetFPS(0);
}
void engine::update(){
    if(IsKeyPressed(KEY_R)){
        generate_maze();
        get_show_solution(false);
    }
    if(IsKeyPressed(KEY_S)){
        get_show_solution(false);
        solve_maze();
        get_show_solution(true
        );
    }
    handle_ui_input();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)||IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        if (GetMouseX() > SYSTEM_WIDTH){
            get_show_solution(false);
            get_position(start_x,end_x,start_y,end_y,cell_size);
            update_start_end(grid,start_x,start_y,end_x,end_y);
        }
    }
}

void engine::run(){
    srand((unsigned)time(nullptr));
    init();
    generate_maze();
    while(!WindowShouldClose()){
        ::get_current_state(grid,cell_size);
        update();
    }
    unload_resource();
    CloseWindow();
}
