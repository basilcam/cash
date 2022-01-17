cmake_minimum_required(VERSION 3.15)
project(camshell C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(deps/LibCam)

add_executable(camshell src/evaluate.c
    src/main.c
    src/parse.c)
target_include_directories(camshell PRIVATE src/)
target_link_libraries(camshell PRIVATE cam)