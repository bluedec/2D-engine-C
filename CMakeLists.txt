cmake_minimum_required(VERSION 3.16)
project(Test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for clangd

find_package(SDL3 REQUIRED CONFIG)

add_executable(Test 
  src/app.c
  src/main.c
  src/state.c
  src/stage.c
  src/constants.c
  src/player/player.c
  src/player/movement.c
  src/stages/greenForest.c
  src/stages/blueForest.c
  src/components/components.c

)
target_link_libraries(Test PRIVATE SDL3::SDL3 m)
# 2. Tell CMake to look inside the "include" folder for header (.h) files
target_include_directories(Test PRIVATE include)
