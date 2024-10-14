//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_CONSOLEDRAWSCORE_H
#define BPC_PC1T_SNAKE_CONSOLEDRAWSCORE_H

#include "../lib/statFile.h"

void consoleDrawScore(int scoreCount, int* scores) {
    if (scores == NULL) {
        return;
    }

    printf("Best Scores\n");
    for (int i = 0; i < scoreCount; i++) {
        printf("%d. %d\n", i + 1, scores[i]);
    }
}

#endif //BPC_PC1T_SNAKE_CONSOLEDRAWSCORE_H
