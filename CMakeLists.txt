cmake_minimum_required(VERSION 4.0)
project(Simple2DEngine VERSION 0.0.1)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(./src/third_party/SDL)

add_executable(Simple2DEngine ./src/main.cpp)

target_link_libraries(Simple2DEngine PRIVATE SDL3::SDL3-static)
