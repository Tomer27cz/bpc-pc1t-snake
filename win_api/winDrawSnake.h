//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWSNAKE_H
#define BPC_PC1T_SNAKE_WINDRAWSNAKE_H

#include <windows.h>
#include "../snake/snakeStruct.h"
#include "math.h"

void DrawScore(HDC hdc, struct gameData *gameData, RECT clientRect, int topOffset);

void DrawGrid(HDC hdc, RECT clientRect, double squareWidth, double squareHeight, int GRID_COLS, int GRID_ROWS, int topOffset);

void FillSquareAt(HDC hdc, int x, int y, double squareWidth, double squareHeight, int color, int topOffset);
void DrawSnakeAndFruit(HDC hdc, struct gameData *gameData, double squareWidth, double squareHeight, int topOffset);


void DrawScore(HDC hdc, struct gameData *gameData, RECT clientRect, int topOffset) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d", gameData->score);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(0, 0, 0));

    HFONT hFont = GetStockObject(DEFAULT_GUI_FONT);
    LOGFONT lf;
    GetObject(hFont, sizeof(LOGFONT), &lf);

    lf.lfHeight = topOffset;

    HFONT hNewFont = CreateFontIndirect(&lf);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

    // Do text drawing
    DrawText(hdc, scoreText, strlen(scoreText), &clientRect, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOCLIP);

    // Always select the old font back into the DC
    SelectObject(hdc, hOldFont);
    DeleteObject(hNewFont);
}
void DrawGrid(HDC hdc, RECT clientRect, double squareWidth, double squareHeight, int GRID_COLS, int GRID_ROWS, int topOffset) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));  // Black pen for grid lines
    SelectObject(hdc, hPen);

    // Draw vertical lines
    for (int x = 0; x <= GRID_COLS; x++)
    {
        MoveToEx(hdc, x * squareWidth, topOffset, NULL);
        LineTo(hdc, x * squareWidth, clientRect.bottom);
    }

    // Draw horizontal lines
    for (int y = 0; y <= GRID_ROWS; y++)
    {
        MoveToEx(hdc, 0, y * squareHeight + topOffset, NULL);
        LineTo(hdc, clientRect.right, y * squareHeight + topOffset);
    }

    DeleteObject(hPen);
}
void FillSquareAt(HDC hdc, int x, int y, double squareWidth, double squareHeight, int color, int topOffset) {
    // Color 0=Black, 1=Red, 2=Green, 3=Blue

    COLORREF squareColor;
    switch (color) {
        case 0:
            squareColor = RGB(0, 0, 0);
            break;
        case 1:
            squareColor = RGB(255, 0, 0);
            break;
        case 2:
            squareColor = RGB(0, 255, 0);
            break;
        case 3:
            squareColor = RGB(0, 0, 255);
            break;
        default:
            squareColor = RGB(0, 0, 0);
            break;
    }

    HBRUSH hBrush = CreateSolidBrush(squareColor);  // Red brush for filling squares
    RECT rect;

    // Calculate the top-left and bottom-right of the square to fill
    rect.left = x * squareWidth;
    rect.top = y * squareHeight + topOffset;
    rect.right = ceil(rect.left + squareWidth);
    rect.bottom = ceil(rect.top + squareHeight);

    FillRect(hdc, &rect, hBrush);  // Fill the square

    DeleteObject(hBrush);
}
void DrawSnakeAndFruit(HDC hdc, struct gameData *gameData, double squareWidth, double squareHeight, int topOffset) {
    // Draw the snake's head
    FillSquareAt(hdc, gameData->x, gameData->y, squareWidth, squareHeight, 2, topOffset);

    // Draw the snake's body
    for (int i = 0; i < gameData->tailLen; i++) {
        FillSquareAt(hdc, gameData->tail[i].x, gameData->tail[i].y, squareWidth, squareHeight, 0, topOffset);
    }

    // Draw the fruit
    for (int i = 0; i < gameData->fruits.size; i++) {
        FillSquareAt(hdc, gameData->fruits.array[i].x, gameData->fruits.array[i].y, squareWidth, squareHeight, 1, topOffset);
    }
}

void DrawSnake(HDC hdc, struct gameData *gameData, RECT clientRect, double squareWidth, double squareHeight, int GRID_COLS, int GRID_ROWS, int topOffset) {
    DrawScore(hdc, gameData, clientRect, topOffset);
    DrawGrid(hdc, clientRect, squareWidth, squareHeight, GRID_COLS, GRID_ROWS, topOffset);
    DrawSnakeAndFruit(hdc, gameData, squareWidth, squareHeight, topOffset);
}

#endif //BPC_PC1T_SNAKE_WINDRAWSNAKE_H