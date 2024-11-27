//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_STATFILE_H
#define BPC_PC1T_SNAKE_STATFILE_H

#include "snake.h"

typedef struct {
    char name[MAX_NAME_CHARS];
    int score;
} Score;

void writeScore(const char *filename, struct gameData *gameData, const char *name);
Score* getTopScores(const char *filename, int *scores);

#endif //BPC_PC1T_SNAKE_STATFILE_H
