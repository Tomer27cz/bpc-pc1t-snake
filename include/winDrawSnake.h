//
// Created by Tomer27cz on 24.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWSNAKE_H
#define BPC_PC1T_SNAKE_WINDRAWSNAKE_H

#include "windows.h"
#include "snake.h"

void DrawSnake(HDC hdc, struct gameData *gameData, RECT clientRect, double squareWidth, double squareHeight, int GRID_COLS, int GRID_ROWS, int topOffset);

#endif //BPC_PC1T_SNAKE_WINDRAWSNAKE_H
