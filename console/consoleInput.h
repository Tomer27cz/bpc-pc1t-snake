//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_CONSOLEINPUT_H
#define BPC_PC1T_SNAKE_CONSOLEINPUT_H

#include <windows.h>
#include "../snake/snakeStruct.h"
#include "../snake/snakeLogic.h"
#include "../lib/statFile.h"

void consoleInput(struct gameData *gameData) {
    // use windows async function to get key press
    if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x41) || GetAsyncKeyState(0x61)) {
        changeDirection(gameData, 3);
    } else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x73)) {
        changeDirection(gameData, 4);
    } else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x77)) {
        changeDirection(gameData, 1);
    } else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44) || GetAsyncKeyState(0x64)) {
        changeDirection(gameData, 2);
    } else if (GetAsyncKeyState(27)) {

    }
}

#endif //BPC_PC1T_SNAKE_CONSOLEINPUT_H
