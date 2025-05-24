#include "ball.h"
#include <iostream>
#include <raylib.h>

extern Texture2D bg1;
extern Texture2D bg2;
extern Texture2D bg3;
extern Texture2D bg4;
extern Texture2D bg_s;

extern Texture2D intro_txt6;
extern Texture2D intro_txt6s;

void background_Select(int* bg, int* screen, int char1, int char2)
{
    int gapX = 20;
    int gapY = 10;
    float shrink = 0.15;
    float edge = 1.14;

    float bg1Width = 145;
    float bg1Height = 700 ;
    float bg2Width = 645 ;
    float bg2Height = 700 ;
    float bg3Width = 1145 ;
    float bg3Height = 700;
    float bg4Width = 1645;
    float bg4Height = 700;
    float text6Width = 1650;
    float text6Height = 950;

    Vector2 bgLoc = {0.0f,0.0f};
    Vector2 BG1Loc = {bg1Width, bg1Height};
    Vector2 BG2Loc = {bg2Width, bg2Height};
    Vector2 BG3Loc = {bg3Width, bg3Height};
    Vector2 BG4Loc = {bg4Width, bg4Height};
    Vector2 text6Loc = {text6Width, text6Height};

    Vector2 BG1Loc_s = {bg1Width-gapX, bg1Height-gapY};
    Vector2 BG2Loc_s = {bg2Width-gapX, bg2Height-gapY};
    Vector2 BG3Loc_s = {bg3Width-gapX, bg3Height-gapY};
    Vector2 BG4Loc_s = {bg4Width-gapX, bg4Height-gapY};

    float BG1Width = (float)bg1.width *(shrink);
    float BG1Height = (float)bg1.height *(shrink);
    float BG2Width = (float)bg2.width *(shrink);
    float BG2Height = (float)bg2.height *(shrink);
    float BG3Width = (float)bg3.width *(shrink);
    float BG3Height = (float)bg3.height *(shrink);
    float BG4Width = (float)bg4.width *(shrink);
    float BG4Height = (float)bg4.height *(shrink);
    float txt6Width = (float)intro_txt6.width *(shrink);
    float txt6Height = (float)intro_txt6.height *(shrink);


    Rectangle RecBG1 = {bg1Width, bg1Height, BG1Width, BG1Height};
    Rectangle RecBG2 = {bg2Width, bg2Height, BG2Width, BG2Height};
    Rectangle RecBG3 = {bg3Width, bg3Height, BG3Width, BG3Height};
    Rectangle RecBG4 = {bg4Width, bg4Height, BG4Width, BG4Height};
    Rectangle RecTex6 = {text6Width,text6Height,txt6Width,txt6Height};

    Vector2 MousePos = GetMousePosition();

    BeginDrawing();

        if(*bg == 0)
        {
            DrawTextureEx(bg1, bgLoc, 0, 1, WHITE);
            
        }
        else if(*bg == 1)
        {
            DrawTextureEx(bg2, bgLoc, 0, 1, WHITE);
        }
        else if(*bg == 2)
        {
            DrawTextureEx(bg3, bgLoc, 0, 1, WHITE);
        }
        else if(*bg == 3)
        {
            DrawTextureEx(bg4, bgLoc, 0, 1, WHITE);
        }
        
        
        if(CheckCollisionPointRec(MousePos, RecBG1))
        {
            *bg = 0;
            DrawTextureEx(bg_s, BG1Loc_s, 0, (shrink)*(edge), WHITE);
            DrawTextureEx(bg1, BG1Loc, 0, (shrink), WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {

                *screen = 12;
            }
        }
        else
        {
            DrawTextureEx(bg1, BG1Loc, 0, (shrink), WHITE);
            DrawText(TextFormat("X(145) = %f\nY(700) = %f\nwidth(297) = %f\nheight(162) = %f\nshrink(0.15) = %f",bg1Width, bg1Height, BG1Width, BG1Height,shrink), 10, 10, 70, DARKGRAY);
        }

        if(CheckCollisionPointRec(MousePos, RecBG2))
        {
            *bg = 1;
            DrawTextureEx(bg_s, BG2Loc_s, 0, (shrink)*(edge), WHITE);
            DrawTextureEx(bg2, BG2Loc, 0, (shrink), WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                
                *screen = 12;
            }
        }
        else
        {
            DrawTextureEx(bg2, BG2Loc, 0, (shrink), WHITE);
        }

        if(CheckCollisionPointRec(MousePos, RecBG3))
        {
            *bg = 2;
            DrawTextureEx(bg_s, BG3Loc_s, 0, (shrink)*(edge), WHITE);
            DrawTextureEx(bg3, BG3Loc, 0, (shrink), WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                
                *screen = 12;
            }
        }
        else
        {
            DrawTextureEx(bg3, BG3Loc, 0, (shrink), WHITE);
        }

        if(CheckCollisionPointRec(MousePos, RecBG4))
        {
            *bg = 3;
            DrawTextureEx(bg_s, BG4Loc_s, 0, (shrink)*(edge), WHITE);
            DrawTextureEx(bg4, BG4Loc, 0, (shrink), WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                
                *screen = 12;
            }
        }
        else
        {
            DrawTextureEx(bg4, BG4Loc, 0, (shrink), WHITE);
        }
        
        if(CheckCollisionPointRec(MousePos, RecTex6))
        {
            DrawTextureEx(intro_txt6s, text6Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 6;
            }
        }
        else
        {
            DrawTextureEx(intro_txt6, text6Loc, 0, 1, WHITE);
        }

    EndDrawing();

}