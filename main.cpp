/*#include "raylib.h"

int main(void) {
    // Initialize the window
    InitWindow(800, 600, "Clickable Texture Example");
    SetTargetFPS(4);

    // Load a texture
    Image img = LoadImage("resources/texture.png");
    ImageResize(&img, 100, 100);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

    // Define the position of the texture on the screen
    Vector2 texturePosition = {200, 150};

    while (!WindowShouldClose()) {
        // Get the mouse position
        Vector2 mousePosition = GetMousePosition();

        // Define the bounds of the texture
        Rectangle textureBounds = {
            texturePosition.x, texturePosition.y,
            (float)texture.width, (float)texture.height
        };

        // Check if the texture is clicked
        bool isTextureClicked = 
            CheckCollisionPointRec(mousePosition, textureBounds) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the texture
        DrawTexture(texture, texturePosition.x, texturePosition.y, WHITE);

        // Highlight the texture if the mouse is over it
        if (CheckCollisionPointRec(mousePosition, textureBounds)) {
            DrawRectangleLinesEx(textureBounds, 2, RED);
        }

        // Display a message if the texture is clicked
        if (isTextureClicked) {
            DrawText("Texture clicked!", 10, 10, 20, GREEN);
        }

        EndDrawing();
    }

    // Unload the texture and close the window
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
*/

#include <raylib.h>
#include "ball.h"
#include <iostream>

Texture2D intro_bg1;
Texture2D intro_bg2;
Texture2D intro_bg3;

Texture2D intro_txt1;
Texture2D intro_txt2;
Texture2D intro_txt3;
Texture2D intro_txt4;
Texture2D intro_txt5;
Texture2D intro_txt6;

Texture2D intro_txt2s;
Texture2D intro_txt3s;
Texture2D intro_txt4s;
Texture2D intro_txt5s;
Texture2D intro_txt6s;

Texture2D bg1;
Texture2D bg2;
Texture2D bg3;
Texture2D bg4;
Texture2D bg_s;

Texture2D ch1;
Texture2D ch2;
Texture2D ch3;
Texture2D ch4;
Texture2D ch1_s;
Texture2D ch2_s;
Texture2D ch3_s;
Texture2D ch4_s;

Texture2D blue_s;
Texture2D red_s;
Texture2D orange_s;
Texture2D blue_red_s;
Texture2D blue_orange_s;

Texture2D bg_anime[311];
Texture2D ch1_anime[6];
Texture2D ch2_anime[6];

int main(void) {
    
    //Monitor Resolution(function doesn't work)
    int monitorWidth = 1920;
    int monitorHeight = 1080;

    SetTargetFPS(60);

    int screen = 1; //Indicate screen
    

    int type = 0; //single or multiplayer
    /*
        0 - singleplayer
        1 - versus
    */

    int char1 = 0; //player 0 character
    /*
        0 - character1
        1 - character2
        2 - character3
    */
    int char2 = 0; //player 1 or AI character
    /*
        0 - character1
        1 - character2
        2 - character3
    */
    int bg = 0; //background
    /*
        0 - background1
        1 - background2
        2 - background3
    */

    InitWindow(monitorWidth, monitorHeight, "GAME1");
    SetWindowPosition(0,0);

    loadImages(monitorWidth, monitorHeight);

    // Set FPS
    //MaximizeWindow();
    ToggleFullscreen();

    while (!WindowShouldClose()) {
        /*
        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }
        */

        //exit
        if(screen == 0)
        {
            break;
        }
        
        //Title Screen
        if(screen == 1)
        {
            titlescreen(&screen, &type);
        }

        //SinglePlayer
        if(screen == 2)
        {
            standBy(&screen);
            type = 0; //to indicate singleplayer
        }

        //Versus
        if(screen == 3)
        {
            standBy(&screen);
            type = 1; //to indicate versusw
        }

        //Options
        if(screen == 4)
        {
            standBy(&screen);
        }

        //Character 1 Select
        if(screen == 5)
        {
            player1_Select(&char1, &screen);
        }

        //Character 2 Select
        if(screen == 6)
        {
            player2_Select(&char2, &screen, char1);
        }

        //Background Select
        if(screen == 7)
        {
            background_Select(&bg, &screen, char1, char2);
        }

        if(screen == 8)
        {
            loadFiles(monitorWidth, monitorHeight, char1, char2, bg, &screen);
        }

        if(screen == 12)
        {
            //standBy(&screen);
            singlePlayer(&screen, bg, char1, char2, monitorWidth, monitorHeight);
        }
        
        /*
        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawTexture(intro_bg1, 0, 0, WHITE);
        DrawText("Press M to maximize, N to minimize and F to toggle fullscreen", 10, 10, 20, DARKGRAY);
        EndDrawing();
        */
        
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}


