cmake_minimum_required(VERSION 4.0)
project(Engine VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.10
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL"
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.4.4
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL_image"
)
FetchContent_MakeAvailable(SDL3_image)

add_library(
        Engine STATIC
        src/Engine/main_app.cpp
)
target_include_directories(
        Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
        Engine PUBLIC
        SDL3_image::SDL3_image-static
        SDL3::SDL3-static
)