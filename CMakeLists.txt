cmake_minimum_required(VERSION 3.29)
project(test_maze)

set(CMAKE_CXX_STANDARD 26)

add_executable(test_maze 
    main.cpp
    gameplay.cpp
    enemies.cpp
    levels.cpp
    patterns.cpp
    colors.cpp
    animations.cpp
    renderer.cpp
)
