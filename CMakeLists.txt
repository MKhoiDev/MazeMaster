cmake_minimum_required(VERSION 3.14) # FetchContent cần bản 3.14 trở lên

# 1. Thông tin dự án
project(MazeMaster VERSION 1.0.0 LANGUAGES CXX)

# 2. Chuẩn C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. TỰ ĐỘNG TẢI RAYLIB (FetchContent)
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

# 4. Thiết lập đường dẫn Header
include_directories(include)

# 5. Gom file code
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 6. Tạo file chạy
add_executable(MazeMaster ${SOURCES})
if(MSVC)
  # Tăng Stack lên 10MB (/STACK:bytes)
  target_link_options(MazeMaster PRIVATE "/STACK:100000000")
endif()

# 7. GẮN KẾT (Linking)
# Lệnh gắn Raylib vào MazeMaster
target_link_libraries(MazeMaster PRIVATE raylib)



# 8. Copy tài nguyên (Hình ảnh/Font) ra thư mục chạy
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})