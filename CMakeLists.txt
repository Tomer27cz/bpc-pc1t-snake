cmake_minimum_required(VERSION 3.27)
project(bpc_pc1t_snake C)

set(CMAKE_C_STANDARD 11)

add_executable(bpc_pc1t_snake main.c
        include/fruitArray.h
        include/inputBuffer.h
        include/point.h
        include/snake.h
        include/statFile.h
        include/winDrawScreen.h
        include/winDrawSnake.h
        include/winDrawText.h
        src/fruitArray.c
        src/inputBuffer.c
        src/snake.c
        src/statFile.c
        src/winDrawScreen.c
        src/winDrawText.c
        src/winDrawSnake.c
        include/base.h
)
