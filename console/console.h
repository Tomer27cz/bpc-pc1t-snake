//
// Created by Tomer27cz on 24.10.2024.
//

#ifndef BPC_PC1T_SNAKE_CONSOLE_H
#define BPC_PC1T_SNAKE_CONSOLE_H

#include <windows.h>

#include "../snake/snakeStruct.h"
#include "../snake/snakeLogic.h"
#include "../include/statFile.h"

void consoleDrawScore(int scoreCount, int* scores);

void consoleDraw(struct gameData *gameData);

int consoleDrawEnd(struct gameData *gameData);

void consoleInput(struct gameData *gameData);

#endif //BPC_PC1T_SNAKE_CONSOLE_H
