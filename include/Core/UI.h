#pragma once


#include <vector>

#define SYSTEM_WIDTH 400
#define WINDOW_HEIGHT 1500
#define WINDOW_WIDTH 1500

static bool TURN_ON_DRAW_WHEN_GENERATE=true;

bool is_turn_on_draw_when_generate();
static double DRAW_GEN_TIME=0.01;
double draw_gen_time();

static bool TURN_ON_DRAW_WHEN_SOLVE=false;
bool is_turn_on_draw_when_solve();
static double DRAW_SOLVE_TIME=0.2; //s
double draw_solve_time();
struct cell;

void handle_ui_input();

static void draw_maze(const std::vector<std::vector<cell>> &grid,int cell_size);
void setup_window(const int& height,const int& width,int& cell_size );
void get_position( int &start_x,int &end_x,int &start_y,int &end_y,const int &cell_size);
void load_resource();
void unload_resource();
void draw_slidebar();
void get_show_solution(bool solution);
void draw_solution_path(const std::vector<std::vector<cell>> &grid,const int &cell_size);
void get_current_state(const std::vector<std::vector<cell>> &grid,int cell_size );