#include "Core/Engine.h"
#include "Core/UI.h"
#include "Algorithms/MazeGenerator.h"
#include "Algorithms/MazeSolver.h"
#include "raylib.h"
#include <ctime>
#include <cstdlib>
using namespace std;

engine::engine(int height ,int width):height(height),width(width),cell_size(0),is_running(true){}

void engine::generate_maze(){
    ::generate_maze(grid,height,width,cell_size);
}
void engine::solve_maze(){
    ::depth_first_search(grid,height,width,cell_size);
}
void engine::init(){
    ::setup_window(height,width,cell_size);
    SetTargetFPS(0);
}
void engine::update(){
    if(IsKeyPressed(KEY_R)){
        generate_maze();
    }
    if(IsKeyPressed(KEY_S)){
        solve_maze();
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
    CloseWindow();
}
