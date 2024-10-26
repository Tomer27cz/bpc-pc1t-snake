//
// Created by Tomer27cz on 24.10.2024.
//

#include "windows.h"
#include "stdlib.h"
#include "stdio.h"

#include "console.h"

void consoleDrawScore(int scoreCount, int* scores) {
    if (scores == NULL) {
        return;
    }

    printf("Best Scores\n");
    for (int i = 0; i < scoreCount; i++) {
        printf("%d. %d\n", i + 1, scores[i]);
    }
}

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
