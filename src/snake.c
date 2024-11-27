//
// Created by Tomer27cz on 24.10.2024.
//

#include "stdlib.h"
#include "math.h"

#include "stdio.h"

#include "../include/snake.h"
#include "../include/fruitArray.h"
#include "../include/inputBuffer.h"

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

void setup(struct gameData *gameData, const char *name) {
//    gameData->tail[0].x = (WIDTH / 2) - 1;
//    gameData->tail[0].y = HEIGHT / 2;

    for (int i = 0; i < 100; i++) {
        gameData->tail[i].x = -1;
        gameData->tail[i].y = -1;
    }

    gameData->gameOver = 0;
    gameData->direction = 0;
    gameData->tailLen = 0;
    gameData->score = 0;

    for (int i = 0; i < MAX_NAME_CHARS; i++) {
        gameData->name[i] = name[i];
    }

    gameData->level = 1;
    gameData->maxLevel = (WIDTH * HEIGHT) / 10;

    float sizeConstant = (float)(WIDTH + HEIGHT) / 2;

    float maxSpeed = (MIN_TIME_TO_CROSS / sizeConstant) / 1000 * 60;
    float minSpeed = (MAX_TIME_TO_CROSS / sizeConstant) / 1000 * 60;

    gameData->maxSpeed = maxSpeed < 3 ? 3 : maxSpeed;
    gameData->minSpeed = minSpeed > 30 ? 30 : minSpeed;

    gameData->speedStep = (gameData->minSpeed - gameData->maxSpeed) / (float)gameData->maxLevel;
    gameData->framesPerMove = minSpeed;

    dInitQueue(&gameData->queue);

    gameData->x = WIDTH / 2;
    gameData->y = HEIGHT / 2;

    gameData->width = WIDTH;
    gameData->height = HEIGHT;

    fInitArray(&gameData->fruits);
    fArrayAppend(&gameData->fruits, (point) {(WIDTH / 2)+2, HEIGHT / 2});
}

void logic(struct gameData *gameData) {
    if (gameData->direction == 0 || gameData->gameOver == 1)
        return;

    // Process the direction queue
    if (!dIsEmpty(&gameData->queue)) {
        gameData->direction = dDequeue(&gameData->queue);
    }

    // Previous position of the tail , Set the position of the tail to the current position of the head
    point prevPoint = gameData->tail[0];
    gameData->tail[0] = (point) {gameData->x, gameData->y};

    point prevPoint2;
    for (int i = 1; i < gameData->tailLen; i++) {
        // Save the current coordinates of the tail at position i
        prevPoint2 = gameData->tail[i];

        // Set the coordinates at position i to the previous coordinates at position i-1 (if tail is stacked = dont)
        //if (gameData->tail[i].x != gameData->tail[i-1].x && gameData->tail[i].y != gameData->tail[i-1].y) {
        //    gameData->tail[i] = prevPoint;
        //}
        gameData->tail[i] = prevPoint;

        // Set the coordinates for the next iteration
        prevPoint = prevPoint2;
    }

    // Move the head in the direction
    switch (gameData->direction) {
    case 1: // LEFT
        gameData->x--;
        break;
    case 2: // RIGHT
        gameData->x++;
        break;
    case 3: // UP
        gameData->y--;
        break;
    case 4: // DOWN
        gameData->y++;
        break;
    default:
        break;
    }

    // Checks for collision with the wall
    if (gameData->x < 0 || gameData->x >= gameData->width || gameData->y < 0 || gameData->y >= gameData->height) {
        gameData->gameOver = 1;
    }

    // Checks for collision with the tail
    for (int i = 0; i < gameData->tailLen; i++) {
        if (gameData->tail[i].x == gameData->x && gameData->tail[i].y == gameData->y)
            gameData->gameOver = 1;
    }

    // Checks for collision with the fruit
    for (int i = 0; i < gameData->fruits.size; i++) {
        if (gameData->x == gameData->fruits.array[i].x && gameData->y == gameData->fruits.array[i].y) {
            // Increase the score and the length of the tail
            gameData->score += 10;
            gameData->tailLen += 1;

            // Check if the tail length is divisible by 10
            if (gameData->tailLen % 10 == 0) {
                gameData->level++;

                if (gameData->framesPerMove > gameData->maxSpeed) {
                    gameData->framesPerMove -= gameData->speedStep;
                }
            }

            // Remove the fruit from the array
            fArrayRemove(&gameData->fruits, gameData->fruits.array[i]);

            // Generate a new fruit
            generateFruit(gameData);
        }
    }
}

void changeDirection(struct gameData *gameData, int direction) {
    if (gameData->direction == 0) {
        gameData->direction = direction;
    } else {
        int lastDirection;

        if (dIsEmpty(&gameData->queue)) {
            lastDirection = gameData->direction;
        } else {
            lastDirection = gameData->queue.buffer[gameData->queue.rear];
        }

        switch (direction){
            case 1: // UP
                if (lastDirection == 2 || lastDirection == 1) {return;}
                break;
            case 2: // DOWN
                if (lastDirection == 1 || lastDirection == 2) {return;}
                break;
            case 3: // LEFT
                if (lastDirection == 4 || lastDirection == 3) {return;}
                break;
            case 4: // RIGHT
                if (lastDirection == 3 || lastDirection == 4) {return;}
                break;
            default:
                break;
        }

        dEnqueue(&gameData->queue, direction);
    }
}