#pragma once
#include "Entities/MazeGrid.h"
#include <vector>

using namespace std;

class engine{
    private:
    int height ;
    int width ;
    int cell_size;
    vector<vector<cell>> grid;
    bool is_running;


    public:
    engine(int height , int width);
    void run();

    private:
    void  init();
    void  update();
    void  generate_maze();
    void  solve_maze();


};