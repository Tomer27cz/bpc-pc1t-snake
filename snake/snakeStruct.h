//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_SNAKESTRUCT_H
#define BPC_PC1T_SNAKE_SNAKESTRUCT_H

#include "stdlib.h"
#include "../lib/point.h"
#include "../lib/fruitArray.h"
#include "../lib/inputBuffer.h"

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

void generateFruit(struct gameData *gameData) {
    while (1) {
        point fruit = {0, 0};

        fruit.x = rand() % gameData->width;
        fruit.y = rand() % gameData->height;

        if (fruit.x == gameData->x && fruit.y == gameData->y) {
            continue;
        }

        int collision = 0;
        for (int i = 0; i < gameData->tailLen; i++) {
            if (fruit.x == gameData->tail[i].x && fruit.y == gameData->tail[i].y) {
                collision = 1;
                break;
            }
        }

        if (collision) {
            continue;
        }

        fArrayAppend(&gameData->fruits, fruit);
        break;
    }
}

void setup(struct gameData *gameData) {
    gameData->tail[0].x = (WIDTH / 2) - 1;
    gameData->tail[0].y = HEIGHT / 2;

    for (int i = 1; i < 100; i++) {
        gameData->tail[i].x = -1;
        gameData->tail[i].y = -1;
    }

    gameData->gameOver = 0;
    gameData->direction = 0;
    gameData->tailLen = 1;
    gameData->score = 0;

    gameData->level = 1;
    gameData->maxLevel = (WIDTH * HEIGHT) / 10;

    int sizeConstant = (WIDTH + HEIGHT) / 2;

    // clockDelay: 400 is very slow, 75 is very fast
    gameData->clockDelay = MAX_TIME_TO_CROSS / sizeConstant < 400 ? MAX_TIME_TO_CROSS / sizeConstant : 400; // maxClockDelay
    gameData->minClockDelay = MIN_TIME_TO_CROSS / sizeConstant > 75 ? MIN_TIME_TO_CROSS / sizeConstant : 75; // minClockDelay
    gameData->speedStep = (gameData->clockDelay - gameData->minClockDelay) / gameData->maxLevel; // speedStep - subtract from clockDelay at level change

    dInitQueue(&gameData->queue);

    gameData->x = WIDTH / 2;
    gameData->y = HEIGHT / 2;

    gameData->width = WIDTH;
    gameData->height = HEIGHT;

    fInitArray(&gameData->fruits);
    fArrayAppend(&gameData->fruits, (point) {(WIDTH / 2)+2, HEIGHT / 2});
}

#endif //BPC_PC1T_SNAKE_SNAKESTRUCT_H
