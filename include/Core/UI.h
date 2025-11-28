#pragma once

#include "raylib.h"
#include <vector>

#define SYSTEM_WIDTH 200
#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1200
struct cell;

static void draw_maze(const std::vector<std::vector<cell>> &grid,int cell_size);
void setup_window(const int& height,const int& width,int& cell_size );
void get_current_state(const std::vector<std::vector<cell>> &grid,int cell_size );