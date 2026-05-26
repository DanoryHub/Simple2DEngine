cmake_minimum_required(VERSION 4.0)
project(S2DRender VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_library(S2DRender STATIC
    texture.cpp
)

target_include_directories(S2DRender PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(S2DRender PUBLIC
        SDL3_image::SDL3_image-static
        SDL3::SDL3-static
)