//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_CONSOLEDRAWEND_H
#define BPC_PC1T_SNAKE_CONSOLEDRAWEND_H

#include "../snake/snakeStruct.h"
#include <conio.h>

int consoleDrawEnd(struct gameData *gameData) {
    printf("\nGame Over!\n\n");
    printf("Score: %d  |  Length: %d", gameData->score, gameData->tailLen);
    printf("\nPress Enter to play again or Esc to exit\n");

    while (1) {
        int ch = getch();
        if (ch == 13) {
            return 1;
        } else if (ch == 27) {
            return 0;
        }
    }

}

#endif //BPC_PC1T_SNAKE_CONSOLEDRAWEND_H
