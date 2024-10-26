//
// Created by Tomer27cz on 24.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWSCREEN_H
#define BPC_PC1T_SNAKE_WINDRAWSCREEN_H

#include "windows.h"
#include "snake.h"

void DrawMainText(HDC hdc, RECT clientRect);
void DrawMainScore(HDC hdc, RECT clientRect, int *bestScores, int top_n);

void DrawMainScreen(HDC hdc, RECT clientRect, int scoreCount, int *scores);

void DrawEndScreen(HDC hdc, struct gameData *gameData, RECT clientRect);

#endif //BPC_PC1T_SNAKE_WINDRAWSCREEN_H
