#include "raylib.h"
#include "stdlib.h"

#include "include/snake.h"
#include "include/base.h"
#include "include/fruitArray.h"
#include "include/inputBuffer.h"
#include "include/point.h"
#include "include/statFile.h"

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

typedef enum GameScreen { TITLE=0, GAMEPLAY, ENDING } GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
struct gameData gameData;

int scoreCount;
Score *scores;

int topBarHeight = 100;
int screenWidth = 800;
int screenHeight = 800;

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main(void) {
    // Initialization =================================================================
    scores = getTopScores(SAVE_FILE, &scoreCount);
    GameScreen currentScreen = TITLE;

    // Text BOX
    char name[MAX_NAME_CHARS + 1] = "\0"; // Add null terminator at the end of the string.
    int letterCount = 0;

    Rectangle textBox = { 160, 200, 500, 50 };
    bool mouseOnText = false;

    // Grid size
    screenHeight += topBarHeight;
    int gridWidth = screenWidth / WIDTH;
    int gridHeight = (screenHeight-topBarHeight) / HEIGHT;

    // WINDOW INIT
    InitWindow(screenWidth, screenHeight, "Snake Game - BPC-PC1T");
    SetTargetFPS(60);
    int framesCounter = 0;

    // Main game loop =================================================================
    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case TITLE:

                mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox) ? true : false;
                if (mouseOnText) {
                    SetMouseCursor(MOUSE_CURSOR_IBEAM); // Set the window's cursor to the I-Beam

                    // Get char pressed (unicode character) on the queue
                    int key = GetCharPressed();
                    while (key > 0) {

                        // Only keys in range [32..125]
                        if ((key >= 32) && (key <= 125) && (letterCount < MAX_NAME_CHARS)) {
                            name[letterCount] = (char)key;
                            name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                            letterCount++;
                        }

                        key = GetCharPressed();  // Check next character in the queue
                    }

                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        letterCount--;
                        if (letterCount < 0) letterCount = 0;
                        name[letterCount] = '\0';
                    }
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                }

                framesCounter = mouseOnText ? framesCounter + 1 : 0;

                if (IsKeyPressed(KEY_ENTER)) {
                    setup(&gameData, name);
                    currentScreen = GAMEPLAY;
                }
                break;
            case GAMEPLAY:
                if (IsKeyDown(KEY_LEFT)) {
                    changeDirection(&gameData, 1);
                } else if (IsKeyDown(KEY_RIGHT)) {
                    changeDirection(&gameData, 2);
                } else if (IsKeyDown(KEY_UP)) {
                    changeDirection(&gameData, 3);
                } else if (IsKeyDown(KEY_DOWN)) {
                    changeDirection(&gameData, 4);
                }

                if (framesCounter >= (int)gameData.framesPerMove) {
                    logic(&gameData);
                    framesCounter = 0;
                }

                if (gameData.gameOver) {
                    writeScore(SAVE_FILE, &gameData, name);
                    currentScreen = ENDING;
                }

                framesCounter++;
                break;
            case ENDING:
                if (IsKeyPressed(KEY_ENTER)) {
                    setup(&gameData, name);
                    currentScreen = GAMEPLAY;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = TITLE;
                } else if (IsKeyPressed(KEY_BACKSPACE)) {
                    currentScreen = TITLE;
                    scores = getTopScores(SAVE_FILE, &scoreCount);
                }
                framesCounter++;
                break;
            default: break;
        }

        // Draw =======================================================================

        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (currentScreen) {
                case TITLE: {
                    DrawText("SNAKE", 20, 20, 40, DARKGRAY);

                    DrawText("Enter Your Name", 235, 120, 40, DARKGRAY);
                    DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 160, 20, GRAY);

                    DrawRectangleRec(textBox, LIGHTGRAY);
                    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
                    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

                    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

                    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_NAME_CHARS), 315, 260, 20, DARKGRAY);

                    if (mouseOnText) {
                        if (letterCount < MAX_NAME_CHARS) {
                            // Draw blinking underscore char
                            if (((framesCounter/20)%2) == 0) {
                                DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                            }
                        }
                        else {
                            DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
                        }
                    }

                    DrawText("PRESS [ENTER] to START GAMEPLAY", 220, 330, 20, GRAY);

                    DrawText("TOP SCORES", 250, 400, 50, DARKGRAY);
                    for (int i = 0; i < scoreCount; i++) {
                        DrawText(TextFormat("%i. %s", i + 1, scores[i].name), 250, 500 + 20*i, 20, DARKGRAY);
                        DrawText(TextFormat("- %i", scores[i].score), 550, 500 + 20*i, 20, DARKGRAY);
                    }

                } break;
                case GAMEPLAY: {
                    DrawRectangle(gameData.x*gridWidth, gameData.y*gridHeight+topBarHeight, gridWidth, gridHeight, DARKGREEN);

                    for (int i = 0; i < gameData.tailLen; i++) {
                        DrawRectangle(gameData.tail[i].x*gridWidth, gameData.tail[i].y*gridHeight+topBarHeight, gridWidth, gridHeight, GREEN);
                    }

                    for (int i = 0; i < gameData.fruits.size; i++) {
                        DrawRectangle(gameData.fruits.array[i].x*gridWidth, gameData.fruits.array[i].y*gridHeight+topBarHeight, gridWidth, gridHeight, RED);
                    }

                    DrawLine(0, topBarHeight, screenWidth, topBarHeight, GRAY);

                    DrawText(TextFormat("%i", gameData.score), 20, 20, 75, DARKGRAY);
                    DrawText(TextFormat("LEVEL: %i", gameData.level), screenWidth/2, 10, 40, DARKGRAY);
                    DrawText(TextFormat("SPEED: %.2f", gameData.framesPerMove), screenWidth/2, 55, 40, DARKGRAY);

                    DrawFPS(screenWidth-75, 10);
                } break;
                case ENDING: {
                    DrawText(TextSubtext("GAME OVER!", 0, framesCounter/10), 100, 150, 100, RED);
                    DrawText(TextFormat("SCORE: %i", gameData.score), 100, 310, 60, DARKGRAY);

                    DrawText("PRESS [ENTER] to PLAY AGAIN", 250, 450, 20, GRAY);
                    DrawText("PRESS [BACKSPACE] to GO TO TITLE", 225, 500, 20, GRAY);
                    DrawText("PRESS [ESCAPE] to EXIT", 275, 550, 20, GRAY);
                } break;
                default: break;

            }

        EndDrawing();

        // ==============================================================================
    }

    // Save score if the game is not over
    if (currentScreen != ENDING) {
        writeScore(SAVE_FILE, &gameData, name);
    }

    // De-Initialization
    CloseWindow();

    return 0;
}