cmake_minimum_required(VERSION 4.0)
project(Engine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

find_package(Python3 COMPONENTS Interpreter)
if(Python3_FOUND)
    execute_process(
            COMMAND ${Python3_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

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

include(CTest)
enable_testing()

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_subdirectory(tests)

add_library(
        Engine STATIC
        src/Engine/S2DMainApp.cpp
        src/Engine/S2DGameObject.cpp
        src/Engine/S2DGameScene.cpp
        src/Engine/S2DPlaceable.cpp
        src/Engine/S2DTexture.cpp
        src/Engine/S2DCamera.cpp
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