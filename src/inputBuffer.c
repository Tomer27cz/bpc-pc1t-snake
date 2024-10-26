//
// Created by Tomer27cz on 24.10.2024.
//

#include "../include/inputBuffer.h"
#include "../include/base.h"

// Initialize the direction queue
void dInitQueue(DirectionQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if the queue is full
int dIsFull(DirectionQueue* q) {
    return q->size == MAX_BUFFER_SIZE;
}

// Check if the queue is empty
int dIsEmpty(DirectionQueue* q) {
    return q->size == 0;
}

// Enqueue a new direction
void dEnqueue(DirectionQueue* q, int direction) {
    if (dIsFull(q)) {
        return;
    }
    q->rear = (q->rear + 1) % MAX_BUFFER_SIZE;  // Circular buffer behavior
    q->buffer[q->rear] = direction;
    q->size++;
}

// Dequeue and return the next direction
int dDequeue(DirectionQueue* q) {
    if (dIsEmpty(q)) {
        return -1;  // Return invalid direction when empty
    }
    int direction = q->buffer[q->front];
    q->front = (q->front + 1) % MAX_BUFFER_SIZE;
    q->size--;
    return direction;
}