cmake_minimum_required(VERSION 4.0)
project(ArcanoidSrc VERSION 0.0.1)

add_library(
        ArcanoidSrc STATIC
        src/ArcanoidObject.cpp
        src/ArcanoidScene.cpp
        src/ArcanoidSettings.cpp
)
target_include_directories(
        ArcanoidSrc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
        ArcanoidSrc PUBLIC
        Engine
)