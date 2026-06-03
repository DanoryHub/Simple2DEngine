cmake_minimum_required(VERSION 4.0)
project(Arcanoid VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# Setup project build options
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL3IMAGE_STATIC ON)
set(SDL3IMAGE_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

# Build third party libraries
add_subdirectory(./src/third_party/SDL)
add_subdirectory(./src/third_party/SDL_image)

# Build source libs
add_subdirectory(./src/engine)

# Build executable
add_executable(Arcanoid src/examples/arcanoid/main.cpp)

target_link_libraries(
        Arcanoid PRIVATE
        Engine
)

# Custom target to copy media directory to the output directory of the executable
add_custom_target(
        copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_CURRENT_SOURCE_DIR}/src/assets" "$<TARGET_FILE_DIR:Arcanoid>/assets"
        COMMENT "Copying media dir"
)
add_dependencies(Arcanoid copy_assets)