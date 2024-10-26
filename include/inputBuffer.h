//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_INPUTBUFFER_H
#define BPC_PC1T_SNAKE_INPUTBUFFER_H

#include "base.h"

// Queue structure
typedef struct {
    int buffer[MAX_BUFFER_SIZE];  // Array to hold the direction changes
    int front;   // Index of the front of the queue
    int rear;    // Index of the rear of the queue
    int size;    // Number of items in the queue
} DirectionQueue;

void dInitQueue(DirectionQueue* q);
int dIsFull(DirectionQueue* q);
int dIsEmpty(DirectionQueue* q);
void dEnqueue(DirectionQueue* q, int direction);
int dDequeue(DirectionQueue* q);


#endif //BPC_PC1T_SNAKE_INPUTBUFFER_H
