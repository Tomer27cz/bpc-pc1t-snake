//
// Created by Tomer27cz on 14.10.2024.
//
//

#ifndef BPC_PC1T_SNAKE_SNAKELOGIC_H
#define BPC_PC1T_SNAKE_SNAKELOGIC_H

#include "stdlib.h"
#include "snakeStruct.h"
#include "../lib/fruitArray.h"

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

                // Increase the speed of the snake (decrease clockDelay)
                if ((gameData->clockDelay-gameData->speedStep) > gameData->minClockDelay) {
                    gameData->clockDelay -= gameData->speedStep;
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

#endif //BPC_PC1T_SNAKE_SNAKELOGIC_H
