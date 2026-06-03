cmake_minimum_required(VERSION 4.0)
project(Engine VERSION 0.0.1)

add_library(
        Engine STATIC
        main_app.cpp
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