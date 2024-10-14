//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWENDSCREEN_H
#define BPC_PC1T_SNAKE_WINDRAWENDSCREEN_H

#include <windows.h>
#include "../snake/snakeStruct.h"
#include "winDrawText.h"

void DrawEndScreen(HDC hdc, struct gameData *gameData, RECT clientRect) {

    int font1 = (clientRect.bottom * clientRect.right / 1000) / 5;
    int font2 = (clientRect.bottom * clientRect.right / 1000) / 10;
    int font3 = (clientRect.bottom * clientRect.right / 1000) / 15;

    int bottom1 = clientRect.bottom / 3;
    int bottom2 = clientRect.bottom / 5 + bottom1;
    int bottom3 = clientRect.bottom / 5 + bottom2;
    int bottom4 = clientRect.bottom / 5 + bottom3;

    RECT rect1 = {0, 0, clientRect.right, bottom1};
    DrawTextSimple(hdc,
                   rect1,
                   "Game Over!",
                   font1,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

    char scoreText[50];
    sprintf(scoreText, "Score: %d  |  Length: %d", gameData->score, gameData->tailLen);

    RECT rect2 = {0, bottom1, clientRect.right, bottom2};
    DrawTextSimple(hdc,
                   rect2,
                   scoreText,
                   font2,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

    RECT rect3 = {0, bottom2, clientRect.right, bottom3};
    DrawTextSimple(hdc,
                   rect3,
                   "Press 'Enter' to play again",
                   font3,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

    RECT rect4 = {0, bottom3, clientRect.right, bottom4};
    DrawTextSimple(hdc,
                   rect4,
                   "Press 'Esc' to exit the game",
                   font3,
                   RGB(0, 0, 0),
                   DT_CENTER | DT_SINGLELINE | DT_NOCLIP);
}

#endif //BPC_PC1T_SNAKE_WINDRAWENDSCREEN_H
