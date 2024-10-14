//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_CONSOLEDRAWSNAKE_H
#define BPC_PC1T_SNAKE_CONSOLEDRAWSNAKE_H

#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

#include "../snake/snakeStruct.h"

void consoleDraw(struct gameData *gameData) {
    system("cls");

    // Creating top wall
    for (int i = 0; i < gameData->width + 2; i++)
        printf("-");
    printf("\n");

    for (int i = 0; i < gameData->height; i++) {
        for (int j = 0; j <= gameData->width; j++) {

            // Creating side walls with '#'
            if (j == 0 || j == gameData->height)
                printf("#");

            // Creating snake's head with 'O'
            if (i == gameData->y && j == gameData->x)
                printf("O");

            // Creating the sanke's food with '*'
            else if (i == gameData->fruits.array[0].y && j == gameData->fruits.array[0].x)
                printf("*");

            // Creating snake's body with 'o'
            else {
                int prTail = 0;
                for (int k = 0; k < gameData->tailLen; k++) {
                    if (gameData->tail[k].x == j
                        && gameData->tail[k].y == i) {
                        printf("o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    printf(" ");
            }
        }
      printf("\n");

    }

    // Creating bottom walls with '-'
    for (int i = 0; i < gameData->width + 2; i++)
        printf("-");
     printf("\n");

    // Print the score and instructions
    printf("score = %d", gameData->score);
    printf("\n");
    printf("Press W, A, S, D for movement.\n");
    printf("Press X to quit the game.");
}

#endif //BPC_PC1T_SNAKE_CONSOLEDRAWSNAKE_H
