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
algo algo_type=algo::BFS;
void engine::change_algo(){
    if(algo_type==algo::BFS){
        algo_type=algo::DFS;
    }
    else if (algo_type==algo::DFS){
        algo_type=algo::A_STAR;
    }
    else if (algo_type==algo::A_STAR){
        algo_type=algo::BFS;
    }
    int algo_type_int_ui=-1;
    if(algo_type==algo::BFS){
        algo_type_int_ui=0;
    }
    else if(algo_type==algo::DFS){
        algo_type_int_ui=1;
    }
    else if(algo_type==algo::A_STAR){
        algo_type_int_ui=2;
    }

    ::change_algo_type_int_ui(algo_type_int_ui);
}
void engine::solve_maze(){
    set_show_solution(false);
    if(IsKeyPressed(KEY_D)){
    ::depth_first_search(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
    if(IsKeyPressed(KEY_B)){
    ::breadth_first_search(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
    if(IsKeyPressed(KEY_A)){
    ::a_star(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
    if(algo_type==algo::DFS){
    ::depth_first_search(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
    if(algo_type==algo::BFS){
    ::breadth_first_search(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
    if(algo_type==algo::A_STAR){
    ::a_star(grid,height,width,cell_size);
    set_show_solution(true);
    return;
    }
}
void engine::init(){
    ::setup_window(height,width,cell_size);
    load_resource();
    SetTargetFPS(0);
}
void engine::update(){
    if(IsKeyPressed(KEY_R)){
        generate_maze();
        set_show_solution(false);
    }
    if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_B)||IsKeyPressed(KEY_A)){
        solve_maze();
    }
    user_action action=handle_ui_input();
    switch(action){
        case user_action::GENERATE:
            generate_maze();
            break;
        case user_action::CHANGE_ALGO:
            change_algo();
            break;
        case user_action::SOLVE:
            solve_maze();
            break;
    }


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)||IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        if (GetMouseX() > SYSTEM_WIDTH){
            set_show_solution(false);
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
