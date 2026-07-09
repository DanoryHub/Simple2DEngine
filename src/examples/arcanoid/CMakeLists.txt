cmake_minimum_required(VERSION 4.0)
project(Arcanoid VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

# Setup project build options
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL3IMAGE_STATIC ON)
set(SDL3IMAGE_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

# Build source libs
add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../../engine
        ${CMAKE_CURRENT_BINARY_DIR}/Engine
)
add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_BINARY_DIR}/ArcanoidSrc
)

# Build executable
add_executable(Arcanoid ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/main.cpp)

target_link_libraries(
        Arcanoid PRIVATE
        Engine
        ArcanoidSrc
)

# Custom target to copy media directory to the output directory of the executable
add_custom_target(
        copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:Arcanoid>/assets"
        COMMENT "Copying media dir"
)
add_dependencies(Arcanoid copy_assets)