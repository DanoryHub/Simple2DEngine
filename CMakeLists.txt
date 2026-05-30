cmake_minimum_required(VERSION 4.0)
project(Simple2DEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# Setup project build options
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL3IMAGE_STATIC ON)
set(SDL3IMAGE_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

# Build third party libraries
add_subdirectory(./src/third_party/SDL EXCLUDE_FROM_ALL)
add_subdirectory(./src/third_party/SDL_image EXCLUDE_FROM_ALL)

# Build project libraries
add_subdirectory(./src/render)

# Build executable
add_executable(Simple2DEngine ./src/main.cpp)

target_link_libraries(Simple2DEngine PRIVATE S2DRender)

# Custom target to copy media directory to the output directory of the executable
add_custom_target(
        copy_media
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_CURRENT_SOURCE_DIR}/src/media" "$<TARGET_FILE_DIR:Simple2DEngine>/media"
        COMMENT "Copying media dir"
)
add_dependencies(Simple2DEngine copy_media)