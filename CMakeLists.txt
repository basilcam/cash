cmake_minimum_required(VERSION 3.15)
project(camshell C)

add_subdirectory(deps/LibCam)

add_executable(camshell src/evaluate.c
        src/main.c
        src/parse.c
        src/command.c
        src/builtin.c
        src/jobs.c
        src/signals.c)
target_include_directories(camshell PRIVATE include/)
target_link_libraries(camshell PRIVATE cam)