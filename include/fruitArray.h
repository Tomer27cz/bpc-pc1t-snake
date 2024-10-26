//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_FRUITARRAY_H
#define BPC_PC1T_SNAKE_FRUITARRAY_H

#include "point.h"
#include "base.h"

typedef struct {
    point array[MAX_FRUITS];
    int front;
    int rear;
    int size;
} FruitArray;

void fInitArray(FruitArray* f);
void fArrayAppend(FruitArray* f, point fruit);
int fArrayRemove(FruitArray* f, point fruit);

#endif //BPC_PC1T_SNAKE_FRUITARRAY_H
