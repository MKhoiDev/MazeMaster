#include "raylib.h"

int main() {
    // 1. Khởi tạo cửa sổ 800x600, title "MazeMaster"
    InitWindow(800, 600, "MazeMaster - Raylib");

    // 2. Đặt FPS mục tiêu (60 frame/s)
    SetTargetFPS(60);

    // 3. Vòng lặp chính: chạy tới khi người dùng đóng cửa sổ
    while (!WindowShouldClose()) {
        // 4. Bắt đầu vẽ frame mới
        BeginDrawing();

        // 5. Xoá nền, tô màu (ở đây là DARKBLUE)
        ClearBackground(DARKBLUE);

        // 6. Vẽ chút text cho vui
        DrawText("MazeMaster using raylib", 20, 20, 20, RAYWHITE);

        // 7. Kết thúc vẽ, push frame lên màn hình
        EndDrawing();
    }

    // 8. Đóng cửa sổ, giải phóng tài nguyên
    CloseWindow();

    return 0;
}
