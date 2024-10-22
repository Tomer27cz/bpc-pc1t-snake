//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_STATFILE_H
#define BPC_PC1T_SNAKE_STATFILE_H

#include <windows.h>
#include "../snake/snakeStruct.h"
#include "stdio.h"
#include "stdlib.h"

// Function to compare two integers for qsort
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a); // Sort in descending order
}

// Function to read scores from file, sort them, and return top 10
int* getTopScores(const char *filename, int *top_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s\n", filename);
        return NULL;
    }

    int *scores = NULL;
    int score, count = 0;
    size_t capacity = 10;

    scores = (int *)malloc(capacity * sizeof(int));
    if (!scores) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read integers from the file
    while (fscanf(file, "%d", &score) != EOF) {
        if (count >= capacity) {
            capacity *= 2;
            scores = (int *)realloc(scores, capacity * sizeof(int));
            if (!scores) {
                printf("Memory reallocation failed\n");
                fclose(file);
                return NULL;
            }
        }
        scores[count++] = score;
    }
    fclose(file);

    // Sort the scores in descending order
    qsort(scores, count, sizeof(int), compare);

    // Return the top 10 or fewer if less than 10 scores
    *top_count = (count < 10) ? count : 10;

    return scores;
}

void writeScore(const char *filename, struct gameData *gameData) {
    if (gameData->score == 0) {
        return;
    }

    FILE *file;
    file = fopen(filename, "a");
    if (!file) {
        printf("\nError opening file! - Creating new one.\n");

        // If no file present create one
        file = fopen(filename, "w");

        if (!file) {
            printf("\nError opening new file!\n");
            exit(1);
        }
    }

    fprintf(file, "%d\n", gameData->score);
    fclose(file);
}

#endif //BPC_PC1T_SNAKE_STATFILE_H
