cmake_minimum_required(VERSION 3.27)
project(bpc_pc1t_snake C)

set(CMAKE_C_STANDARD 11)

add_executable(bpc_pc1t_snake main.c
        snake/snakeStruct.h
        console/consoleDrawSnake.h
        win_api/winDrawSnake.h
        win_api/winDrawMainScreen.h
        win_api/winDrawEndScreen.h
        win_api/winDrawText.h
        lib/statFile.h
        lib/inputBuffer.h
        console/consoleDrawScore.h
        console/consoleInput.h
        console/consoleDrawEnd.h
        lib/fruitArray.h
        lib/point.h)
