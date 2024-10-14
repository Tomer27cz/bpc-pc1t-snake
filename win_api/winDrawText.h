//
// Created by Tomer27cz on 14.10.2024.
//

#ifndef BPC_PC1T_SNAKE_WINDRAWTEXT_H
#define BPC_PC1T_SNAKE_WINDRAWTEXT_H

#include <windows.h>

void DrawTextSimple(HDC hdc, RECT clientRect, char *inputText, int fontSize, COLORREF color, UINT format) {
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, color);

    HFONT hFont = GetStockObject(DEFAULT_GUI_FONT);
    LOGFONT lf;
    GetObject(hFont, sizeof(LOGFONT), &lf);

    lf.lfHeight = fontSize;

    HFONT hNewFont = CreateFontIndirect(&lf);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

    // Do text drawing
    DrawText(hdc, inputText, strlen(inputText), &clientRect, format);

    // Always select the old font back into the DC
    SelectObject(hdc, hOldFont);
    DeleteObject(hNewFont);
}

#endif //BPC_PC1T_SNAKE_WINDRAWTEXT_H
