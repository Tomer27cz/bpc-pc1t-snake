//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_STATFILE_H
#define BPC_PC1T_SNAKE_STATFILE_H

#include "snake.h"

void writeScore(const char *filename, struct gameData *gameData);
int* getTopScores(const char *filename, int *top_count);

#endif //BPC_PC1T_SNAKE_STATFILE_H