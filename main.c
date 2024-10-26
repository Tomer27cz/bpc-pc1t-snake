#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#include "include/fruitArray.h"
#include "include/inputBuffer.h"
#include "include/point.h"
#include "include/snake.h"
#include "include/statFile.h"
#include "include/winDrawScreen.h"
#include "include/winDrawSnake.h"
#include "include/winDrawText.h"
#include "include/base.h"

static int Running = 1;
static int State = 0;
struct gameData gameData;

int scoreCount;
int *scores;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "GridWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        MessageBoxA(NULL, "Failed to register window class", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Snake",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Size and position
        600, 660,                       // Width and height
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL) {
        MessageBoxA(NULL, "Failed to create window", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    setup(&gameData);
    ShowWindow(hwnd, nCmdShow);

    while (Running) {
        MSG Message;
        while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE)) {
            if(Message.message == WM_QUIT) {
                Running = 0;
            }
            TranslateMessage(&Message);
            DispatchMessageA(&Message);
        }

        Sleep(State == 1 ? gameData.clockDelay : 500);

        logic(&gameData);
        InvalidateRect(hwnd, NULL, TRUE);

        if (gameData.gameOver) {
            State = 2;
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static double squareWidth, squareHeight;
    static int topOffset;

    switch (uMsg) {
        case WM_CREATE: {
            scores = getTopScores(SAVE_FILE, &scoreCount);
            break;
        }

        case WM_SIZE: {
            // Get new window dimensions
            double width = LOWORD(lParam);
            double height = HIWORD(lParam);

            // Calculate area for text
            topOffset = ceil(height / 10);

            // Calculate new square sizes based on window size
            squareWidth = width / gameData.width;
            squareHeight = (height - topOffset) / gameData.height;

            // Force a repaint
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            switch (State) {
                case 1:
                    DrawSnake(hdc, &gameData, clientRect, squareWidth, squareHeight, gameData.width, gameData.height, topOffset);
                    break;
                case 2:
                    DrawEndScreen(hdc, &gameData, clientRect);
                    break;
                default:
                    DrawMainScreen(hdc, clientRect, scoreCount, scores);
                    break;
            }

            EndPaint(hwnd, &ps);
        }
        break;

        case WM_KEYDOWN: {
            switch(wParam) {
                case 0x41: // A
                case 0x61: // a
                case VK_LEFT: // Left arrow
                    changeDirection(&gameData, 1);
                    break;
                case 0x44: // D
                case 0x64: // d
                case VK_RIGHT:
                    changeDirection(&gameData, 2);
                    break;
                case 0x57: // W
                case 0x77: // w
                case VK_UP: // Up arrow
                    changeDirection(&gameData, 3);
                    break;
                case 0x53: // S
                case 0x73: // s
                case VK_DOWN: // Down arrow
                    changeDirection(&gameData, 4);
                    break;
                case VK_ESCAPE:
                    writeScore(SAVE_FILE, &gameData);
                    Running = 0;
                    break;
                case 0x0D: // Enter
                    writeScore(SAVE_FILE, &gameData);
                    setup(&gameData);

                    State = 1;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;
                default:
                    break;
            }
        } break;

        case WM_DESTROY: // Window is being destroyed (by clicking the X button)
            writeScore(SAVE_FILE, &gameData);
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

//int main() {
//    scores = getTopScores(SAVE_FILE, &scoreCount);
//    consoleDrawScore(scoreCount, scores);
//
//    printf("Use WASD or arrow keys to move.\n");
//    printf("Press Enter to start the game.\n");
//    printf("Press ESC to exit the game.\n");
//
//    while (1) {
//        int ch = getch();
//        if (ch == 13) { // Enter
//            break;
//        } else if (ch == 27) { // ESC
//            exit(0);
//        }
//    }
//
//    setup(&gameData);
//
//    while (Running) {
//        consoleInput(&gameData);
//        logic(&gameData);
//        consoleDraw(&gameData);
//        Sleep(200 - gameData.speed);
//
//        if (gameData.gameOver) {
//            writeScore(SAVE_FILE, &gameData);
//            State = 2;
//            if (!consoleDrawEnd(&gameData)) {
//                Running = 0;
//            }
//        }
//    }
//
//    // Keep windows from closing
//    getch();
//
//    return 0;
//
//}

