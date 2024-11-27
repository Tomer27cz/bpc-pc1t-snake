//
// Created by Tomer27cz on 24.10.2024.
//

#include <windows.h>
#include "stdio.h"
#include "stdlib.h"

#include "../include/snake.h"
#include "../include/statFile.h"

char* spacePad(char *str, int width) {
    int len = strlen(str);
    if (len >= width) {
        return str;
    }

    char *padded = malloc(width + 1);
    if (!padded) {
        perror("Memory allocation error");
        return NULL;
    }

    memset(padded, ' ', width);
    padded[width] = '\0';
    memcpy(padded, str, len);
    return padded;
}

int compare_scores(const void *a, const void *b) {
    Score *score_a = (Score *)a;
    Score *score_b = (Score *)b;
    return score_b->score - score_a->score;
}

Score* getTopScores(const char *filename, int *scores) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        *scores = 0;
        return NULL;
    }

    Score *score_list = NULL;
    int count = 0, capacity = 10;

    score_list = malloc(capacity * sizeof(Score));
    if (!score_list) {
        perror("Memory allocation error");
        fclose(file);
        *scores = 0;
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (count >= capacity) {
            capacity *= 2;
            score_list = realloc(score_list, capacity * sizeof(Score));
            if (!score_list) {
                perror("Memory allocation error");
                fclose(file);
                *scores = 0;
                return NULL;
            }
        }

        char name[MAX_NAME_CHARS];
        int score;
        if (sscanf(line, "%19[^,],%d", name, &score) == 2) {
            strncpy(score_list[count].name, spacePad(name, MAX_NAME_CHARS), MAX_NAME_CHARS);
            score_list[count].name[MAX_NAME_CHARS - 1] = '\0'; // Ensure null termination
            score_list[count].score = score;
            count++;
        }
    }

    fclose(file);

    qsort(score_list, count, sizeof(Score), compare_scores);

    int top_n = count < 10 ? count : 10;
    Score *top_scores = malloc(top_n * sizeof(Score));
    if (!top_scores) {
        perror("Memory allocation error");
        free(score_list);
        *scores = 0;
        return NULL;
    }
    memcpy(top_scores, score_list, top_n * sizeof(Score));
    free(score_list);

    *scores = top_n;
    return top_scores;
}

void writeScore(const char *filename, struct gameData *gameData, const char *name) {
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

    // if name is empty, use "Unknown"
    if (strlen(name) == 0) {
        name = "Unknown";
    }

    fprintf(file, "%s,%d\n", name, gameData->score);
    fclose(file);
}
