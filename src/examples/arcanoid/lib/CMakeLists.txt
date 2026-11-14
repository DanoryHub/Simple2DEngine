cmake_minimum_required(VERSION 4.0)
project(ArkanoidSrc VERSION 0.0.1)

add_library(
        ArkanoidSrc STATIC
        src/ArkanoidGameObjects.cpp
        src/ArkanoidGameScene.cpp
        src/ArkanoidUiText.cpp
        src/ArkanoidSettings.cpp
)

# Add all generated cpp files to the library
file(
        GLOB GENERATED_FILES
        src/*_gen.cpp
)
target_sources(ArkanoidSrc PUBLIC ${GENERATED_FILES})
target_include_directories(
        ArkanoidSrc PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
        ArkanoidSrc PUBLIC
        Engine
)
