//
// Created by Tomer27cz on 24.10.2024.
//

#ifndef BPC_PC1T_SNAKE_SNAKE_H
#define BPC_PC1T_SNAKE_SNAKE_H

#include "point.h"
#include "fruitArray.h"
#include "inputBuffer.h"
#include "base.h"

struct gameData {
    point tail[WIDTH*HEIGHT];
    int tailLen;

    FruitArray fruits;

    int direction;
    DirectionQueue queue;

    int gameOver;
    int score;

    int level;
    int maxLevel;

    int clockDelay;
    int minClockDelay;
    int speedStep;

    int x;
    int y;
    int width;
    int height;
};

void generateFruit(struct gameData *gameData);
void setup(struct gameData *gameData);
void logic(struct gameData *gameData);
void changeDirection(struct gameData *gameData, int direction);

#endif //BPC_PC1T_SNAKE_SNAKE_H
