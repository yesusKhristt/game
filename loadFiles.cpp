#include "ball.h"
#include <iostream>
#include <raylib.h>

#define BG_FRAME_COUNT1 234
#define CH_FRAME_COUNT1 5

extern Texture2D bg_anime[BG_FRAME_COUNT1];  // Make sure this is defined in main.cpp
extern Texture2D ch1_anime[CH_FRAME_COUNT1];
extern Texture2D ch2_anime[CH_FRAME_COUNT1]; 


void loadChar1(int chWidth, int chHeight, int ch)
{
    for (int i = 0; i < CH_FRAME_COUNT1; i++)
    {
        char filename[50];  
        sprintf(filename, "resources/characters/character%d/%04d.png",ch+1, i + 1);  // Simplified filename formatting
        //sprintf(filename, "resources/backgrounds/background1/%04d.png", i + 1);  // Simplified filename formatting
        
        std::cout << "Loading: " << filename << std::endl; // Debugging output

        if (!FileExists(filename))  // Check if file exists
        {
            std::cout << "Error: File not found - " << filename << std::endl;
            continue;  
        }

        Image img = LoadImage(filename);
        if (img.data == NULL)  // Check if image loaded properly
        {
            std::cout << "Error: Could not load " << filename << std::endl;
            continue;  
        }

        ImageResize(&img, chWidth, chHeight);
        ch1_anime[i] = LoadTextureFromImage(img);
        UnloadImage(img);

        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        // Debugging text
        DrawText(TextFormat("Loading Current Frame: %d / 234", i), 50, 50, 20, DARKGRAY);
    
        EndDrawing();
    }
}

void loadChar2(int chWidth, int chHeight, int ch)
{
    for (int i = 0; i < CH_FRAME_COUNT1; i++)
    {
        char filename[50];  
        sprintf(filename, "resources/characters/character%d/%04d.png",ch+1, i + 1);  // Simplified filename formatting
        //sprintf(filename, "resources/backgrounds/background1/%04d.png", i + 1);  // Simplified filename formatting
        
        std::cout << "Loading: " << filename << std::endl; // Debugging output

        if (!FileExists(filename))  // Check if file exists
        {
            std::cout << "Error: File not found - " << filename << std::endl;
            continue;  
        }

        Image img = LoadImage(filename);
        if (img.data == NULL)  // Check if image loaded properly
        {
            std::cout << "Error: Could not load " << filename << std::endl;
            continue;  
        }

        ImageResize(&img, chWidth, chHeight);
        ch2_anime[i] = LoadTextureFromImage(img);
        UnloadImage(img);

        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        // Debugging text
        DrawText(TextFormat("Loading Current Frame: %d / 234", i), 50, 50, 20, DARKGRAY);
    
        EndDrawing();
    }
}

void loadFiles(int monitorWidth, int monitorHeight, int char1, int char2, int bg, int * screen)
{
    loadChar1(400,  500, char1);
    loadChar2(400,  500, char2);
    *screen = 12;
}




