cmake_minimum_required(VERSION 3.28)
project(MiniGolfe C)

set(CMAKE_C_STANDARD 99)

include_directories(cli-lib-main/include)

add_executable(MiniGolfe main.c
        cli-lib-main/src/keyboard.c
        cli-lib-main/src/screen.c
        cli-lib-main/src/timer.c
)
