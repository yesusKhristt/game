#include "ball.h"
#include <iostream>
#include <raylib.h>

extern Texture2D bg1;

extern Texture2D ch1;
extern Texture2D ch2;
extern Texture2D ch3;
extern Texture2D ch4;
extern Texture2D ch1_s;
extern Texture2D ch2_s;
extern Texture2D ch3_s;
extern Texture2D ch4_s;

extern Texture2D orange_s;
extern Texture2D blue_s;
extern Texture2D red_s;
extern Texture2D blue_orange_s;
extern Texture2D blue_red_s;

extern Texture2D intro_txt6;
extern Texture2D intro_txt6s;

void player2_Select(int* char2, int* screen, int char1)
{
    int gap = 17;

    float chr1Width = 145 ;
    float chr1Height = 700 ;
    float chr2Width = 645 ;
    float chr2Height = 700 ;
    float chr3Width = 1145 ;
    float chr3Height = 700 ;
    float chr4Width = 1645 ;
    float chr4Height = 700 ;
    float text6Width = 1650 ;
    float text6Height = 950 ;

    Vector2 bgLoc = {0.0f,0.0f};
    Vector2 char1Loc = {chr1Width, chr1Height};
    Vector2 char2Loc = {chr2Width, chr2Height};
    Vector2 char3Loc = {chr3Width, chr3Height};
    Vector2 char4Loc = {chr4Width, chr4Height};
    Vector2 text6Loc = {text6Width, text6Height};

    Vector2 char1Loc_s = {chr1Width-gap, chr1Height-gap};
    Vector2 char2Loc_s = {chr2Width-gap, chr2Height-gap};
    Vector2 char3Loc_s = {chr3Width-gap, chr3Height-gap};
    Vector2 char4Loc_s = {chr4Width-gap, chr4Height-gap};

    float char1Width = (float)ch1.width ;
    float char1Height = (float)ch1.height ;
    float char2Width = (float)ch2.width ;
    float char2Height = (float)ch2.height ;
    float char3Width = (float)ch3.width ;
    float char3Height = (float)ch3.height ;
    float char4Width = (float)ch4.width ;
    float char4Height = (float)ch4.height ;
    float txt6Width = (float)intro_txt6.width ;
    float txt6Height = (float)intro_txt6.height ;


    Rectangle RecChar1 = {chr1Width, chr1Height, char1Width, char1Height};
    Rectangle RecChar2 = {chr2Width, chr2Height, char2Width, char2Height};
    Rectangle RecChar3 = {chr3Width, chr3Height, char3Width, char3Height};
    Rectangle RecChar4 = {chr4Width, chr4Height, char4Width, char4Height};
    Rectangle RecTex6 = {text6Width,text6Height,txt6Width,txt6Height};

    Vector2 MousePos = GetMousePosition();

    BeginDrawing();

        DrawTextureEx(bg1, bgLoc, 0, 1, WHITE);
        
        
        if(CheckCollisionPointRec(MousePos, RecChar1))
        {
            DrawTextureEx(ch1_s, char1Loc, 0, 1, WHITE);
            if(char1 == 0)
            {
                DrawTextureEx(blue_orange_s, char1Loc_s, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(orange_s, char1Loc_s, 0, 1, WHITE);
            }
            
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *char2 = 0;
                *screen = 7;
            }
        }
        else
        {
            DrawTextureEx(ch1, char1Loc, 0, 1, WHITE);
            if(char1 == 0)
            {
                DrawTextureEx(blue_s, char1Loc_s, 0, 1, WHITE);
            }
        }

        if(CheckCollisionPointRec(MousePos, RecChar2))
        {
            DrawTextureEx(ch2_s, char2Loc, 0, 1, WHITE);
            if(char1 == 1)
            {
                DrawTextureEx(blue_orange_s, char2Loc_s, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(orange_s, char2Loc_s, 0, 1, WHITE);
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *char2 = 1;
                *screen = 7;
            }
        }
        else
        {
            DrawTextureEx(ch2, char2Loc, 0, 1, WHITE);
            if(char1 == 1)
            {
                DrawTextureEx(blue_s, char2Loc_s, 0, 1, WHITE);
            }
        }

        if(CheckCollisionPointRec(MousePos, RecChar3))
        {
            DrawTextureEx(ch3_s, char3Loc, 0, 1, WHITE);
            if(char1 == 2)
            {
                DrawTextureEx(blue_orange_s, char3Loc_s, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(orange_s, char3Loc_s, 0, 1, WHITE);
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *char2 = 2;
                *screen = 7;
            }
        }
        else
        {
            DrawTextureEx(ch3, char3Loc, 0, 1, WHITE);
            if(char1 == 2)
            {
                DrawTextureEx(blue_s, char3Loc_s, 0, 1, WHITE);
            }
        }

        if(CheckCollisionPointRec(MousePos, RecChar4))
        {
            DrawTextureEx(ch4_s, char4Loc, 0, 1, WHITE);
            if(char1 == 3)
            {
                DrawTextureEx(blue_orange_s, char4Loc_s, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(orange_s, char4Loc_s, 0, 1, WHITE);
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *char2 = 3;
                *screen = 7;
            }
        }
        else
        {
            DrawTextureEx(ch4, char4Loc, 0, 1, WHITE);
            if(char1 == 3)
            {
                DrawTextureEx(blue_s, char4Loc_s, 0, 1, WHITE);
            }
        }
        
        if(CheckCollisionPointRec(MousePos, RecTex6))
        {
            DrawTextureEx(intro_txt6s, text6Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 5;
            }
        }
        else
        {
            DrawTextureEx(intro_txt6, text6Loc, 0, 1, WHITE);
        }

    EndDrawing();

}