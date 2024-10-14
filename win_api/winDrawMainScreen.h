//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWMAINSCREEN_H
#define BPC_PC1T_SNAKE_WINDRAWMAINSCREEN_H

#include <windows.h>
#include "winDrawText.h"
#include "../lib/statFile.h"

void DrawMainText(HDC hdc, RECT clientRect) {

    int font1 = (clientRect.bottom * clientRect.right / 1000) / 7;
    int font2 = (clientRect.bottom * clientRect.right / 1000) / 10;

    int bottom1 = clientRect.bottom / 3;
    int bottom2 = clientRect.bottom / 5 + bottom1;
    int bottom3 = clientRect.bottom / 5 + bottom2;

    RECT rect1;
    rect1.left = 0;
    rect1.top = 0;
    rect1.right = clientRect.right;
    rect1.bottom = bottom1;

    DrawTextSimple(hdc,
                   rect1,
                   "Welcome to Snake Game!",
                   font1,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

    RECT rect2;
    rect2.left = 0;
    rect2.top = bottom1;
    rect2.right = clientRect.right;
    rect2.bottom = bottom2;

    DrawTextSimple(hdc,
                   rect2,
                   "Press 'Enter' to start \nPress 'Esc' to end",
                   font2,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_VCENTER | DT_NOCLIP);

    RECT rect3;
    rect3.left = 0;
    rect3.top = bottom2;
    rect3.right = clientRect.right;
    rect3.bottom = bottom3;

    DrawTextSimple(hdc,
                   rect3,
                   "Use arrow keys or WASD to move\nEat the fruit to grow longer!",
                   font2,
                   RGB(0, 0, 0),
                   DT_CENTER);
}

void DrawMainScore(HDC hdc, RECT clientRect, int *bestScores, int top_n) {

    int font1 = (clientRect.bottom * clientRect.right / 1000) / 7;

    RECT rect1;
    rect1.left = 0;
    rect1.top = clientRect.bottom - (clientRect.bottom / 3);
    rect1.right = clientRect.right;
    rect1.bottom = clientRect.bottom;

    DrawTextSimple(hdc, rect1, "Best Scores", font1, RGB(0, 0, 0), DT_CENTER);

    int font2 = (clientRect.bottom * clientRect.right / 1000) / 15;
    int mid = top_n / 2;

    if (top_n <= 5) {
        for (int i = 0; i < top_n; i++) {
        RECT rect2;
        rect2.left = 0;
        rect2.top = clientRect.bottom - (clientRect.bottom / 4) + (i+1) * font2;
        rect2.right = clientRect.right;
        rect2.bottom = clientRect.bottom - (clientRect.bottom / 4) + (i+2) * font2;

        char scoreText[50];
        sprintf(scoreText, "%d. %d", i+1, bestScores[i]);

        DrawTextSimple(hdc, rect2, scoreText, font2, RGB(0, 0, 0), DT_CENTER);
        }

        return;
    }

    for (int i = 0; i < mid; i++) {
        RECT rect2;
        rect2.left = 0;
        rect2.top = clientRect.bottom - (clientRect.bottom / 4) + (i+1) * font2;
        rect2.right = clientRect.right / 2;
        rect2.bottom = clientRect.bottom - (clientRect.bottom / 4) + (i+2) * font2;

        char scoreText[50];
        sprintf(scoreText, "%d. %d", i+1, bestScores[i]);

        DrawTextSimple(hdc, rect2, scoreText, font2, RGB(0, 0, 0), DT_CENTER);
    }
    for (int i = mid; i < top_n; i++) {
        RECT rect3;
        rect3.left = clientRect.right / 2;
        rect3.top = clientRect.bottom - (clientRect.bottom / 4) + (i + 1 - mid) * font2;
        rect3.right = clientRect.right;
        rect3.bottom = clientRect.bottom - (clientRect.bottom / 4) + (i + 2) * font2;

        char scoreText[50];
        sprintf(scoreText, "%d. %d", i + 1, bestScores[i]);

        DrawTextSimple(hdc, rect3, scoreText, font2, RGB(0, 0, 0), DT_CENTER);
    }
}

void DrawMainScreen(HDC hdc, RECT clientRect, int scoreCount, int *scores) {
    DrawMainText(hdc, clientRect);
    DrawMainScore(hdc, clientRect, scores, scoreCount);
}

#endif //BPC_PC1T_SNAKE_WINDRAWMAINSCREEN_H
