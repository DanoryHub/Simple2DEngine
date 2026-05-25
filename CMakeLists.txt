cmake_minimum_required(VERSION 4.0)
project(Simple2DEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(./src/third_party/SDL)

add_executable(Simple2DEngine ./src/main.cpp)
target_link_libraries(Simple2DEngine PRIVATE SDL3::SDL3-static)

add_custom_target(
        copy_data
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_CURRENT_SOURCE_DIR}/src/media" "$<TARGET_FILE_DIR:Simple2DEngine>/media"
        COMMENT "Copying media dir"
)
add_dependencies(Simple2DEngine copy_data)
