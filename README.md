🚀 MazeMaster - Pathfinding Visualizer

**MazeMaster** is an interactive simulation tool designed to visualize how pathfinding algorithms work in real-time. Built from scratch using **C++** and **Raylib**.

![Project Screenshot](assets/screenshot.png)

## ✨ Key Features

* 🧠 **3 Pathfinding Algorithms:**
    * **DFS (Depth First Search):** Visualizes deep exploration strategy.
    * **BFS (Breadth First Search):** Guarantees finding the shortest path (expanding wave).
    * **A* (A-Star):** Highly optimized heuristic search using **Min-Heap Priority Queue**.
* 🏗️ **Maze Generation:**
    * Generates random **Perfect Mazes** (no loops) using Recursive Backtracking.
    * Supports dynamic resizing (from 5x5 to 1000x1000 grids).
* 🎮 **Interactive UI:**
    * **Real-time Interaction:** Set Start/End points using mouse clicks.
    * **Control Panel:** Toggle visualization steps, switch algorithms, and adjust settings on the fly.
    * **Responsive Rendering:** Auto-centering and scaling map to fit the window.
    * **Overlay System:** Solution path is drawn as a transparent overlay on top of the simulation.

## 🛠️ Tech Stack

* **Language:** C++17
* **Graphics:** [Raylib master](https://www.raylib.com/)
* **UI Components:** [raygui](https://github.com/raysan5/raygui) & Custom Texture Engine
* **Build System:** CMake

## 📦 How to Download & Play (For Users)

You don't need to compile the code to play!
1.  Go to the **[Releases](https://github.com/MKhoiDev/MazeMaster/releases/)** page.
2.  Download the latest `MazeMaster_v1.0.zip`.
3.  Extract the zip file.
4.  Run `MazeMaster.exe`.

## ⚙️ How to Build (For Developers)

If you want to modify the code, follow these steps:

### Prerequisites
* C++ Compiler (MSVC, GCC, or Clang)
* CMake (3.14+)

### Build Instructions
```bash
# 1. Clone the repository
git clone https://github.com/MKhoiDev/MazeMaster.git
cd MazeMaster

# 2. Create build directory
mkdir build
cd build

# 3. Configure (CMake will automatically download Raylib)
cmake .. -DCMAKE_BUILD_TYPE=Release

# 4. Build
cmake --build . --config Release


###🧩 Project Structure
-src/Core/: Engine logic, Game Loop, and Window management.

-src/Entities/: Grid data structure and Cell logic.

-src/Algorithms/: Implementation of DFS, BFS, A* and Maze Generators.

-assets/: UI textures and resources.

Made with ❤️ by [Trần Huỳnh Minh Khôi]