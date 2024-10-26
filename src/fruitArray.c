//
// Created by Tomer27cz on 24.10.2024.
//

#include "../include/fruitArray.h"

// Initialize the fruit array
void fInitArray(FruitArray* f) {
    f->front = 0;
    f->rear = -1;
    f->size = 0;
}

// Append a new fruit to the array
void fArrayAppend(FruitArray* f, point fruit) {
    if (f->size >= MAX_FRUITS) {
        return;
    }
    f->rear = (f->rear + 1) % MAX_FRUITS;  // Circular buffer behavior
    f->array[f->rear] = fruit;
    f->size++;
}

// Remove a fruit from the array
int fArrayRemove(FruitArray* f, point fruit) {
    if (f->size == 0) {
        return -1;  // Return invalid index when empty
    }
    int index = -1;
    for (int i = 0; i < f->size; i++) {
        if (f->array[i].x == fruit.x && f->array[i].y == fruit.y) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return -1;  // Return invalid index when not found
    }
    for (int i = index; i < f->size - 1; i++) {
        f->array[i] = f->array[i + 1];
    }
    f->rear = (f->rear - 1) % MAX_FRUITS;  // Circular buffer behavior
    f->size--;
    return index;
}