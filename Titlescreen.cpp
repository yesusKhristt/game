#include "ball.h"
#include <iostream>
#include <raylib.h>

extern Texture2D intro_bg1;
extern Texture2D intro_bg2;
extern Texture2D intro_bg3;

extern Texture2D intro_txt1;
extern Texture2D intro_txt2;
extern Texture2D intro_txt3;
extern Texture2D intro_txt4;
extern Texture2D intro_txt5;
extern Texture2D intro_txt6;

extern Texture2D intro_txt2s;
extern Texture2D intro_txt3s;
extern Texture2D intro_txt4s;
extern Texture2D intro_txt5s;
extern Texture2D intro_txt6s;

void titlescreen(int* screen, int* type)
{

    float textwidth = 50 ;
    float text1 = 50 ;
    float text2 = 550 ;
    float text3 = 650 ;
    float text4 = 750 ;
    float text5 = 850 ;

    Vector2 bgLoc = {0.0f,0.0f};
    Vector2 text1Loc = {textwidth, text1};
    Vector2 text2Loc = {textwidth, text2};
    Vector2 text3Loc = {textwidth, text3};
    Vector2 text4Loc = {textwidth, text4};
    Vector2 text5Loc = {textwidth, text5};

    float txt2Width = (float)intro_txt2.width ;
    float txt2Height = (float)intro_txt2.height ;

    float txt3Width = (float)intro_txt3.width ;
    float txt3Height = (float)intro_txt3.height ;

    float txt4Width = (float)intro_txt4.width ;
    float txt4Height = (float)intro_txt4.height ;

    float txt5Width = (float)intro_txt5.width ;
    float txt5Height = (float)intro_txt5.height ;

    Rectangle RecTex2 = {textwidth,text2,txt2Width,txt2Height};
    Rectangle RecTex3 = {textwidth,text3,txt3Width,txt3Height};
    Rectangle RecTex4 = {textwidth,text4,txt4Width,txt4Height};
    Rectangle RecTex5 = {textwidth,text5,txt5Width,txt5Height};

    Vector2 MousePos = GetMousePosition();
    


    BeginDrawing();
        
        DrawTextureEx(intro_bg1, bgLoc, 0, 1, WHITE);
        DrawTextureEx(intro_bg2, bgLoc, 0, 1, WHITE);
        
        
        //singleplayer
        DrawTextureEx(intro_txt1, text1Loc, 0, 1, WHITE);
        if(CheckCollisionPointRec(MousePos, RecTex2))
        {
            DrawTextureEx(intro_txt2s, text2Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 5;
                *type = 0;
            }
        }
        else
        {
            DrawTextureEx(intro_txt2, text2Loc, 0, 1, WHITE);
        }

        //versus
        if(CheckCollisionPointRec(MousePos, RecTex3))
        {
            DrawTextureEx(intro_txt3s, text3Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 5;
                *type = 1;
            }
        }
        else
        {
            DrawTextureEx(intro_txt3, text3Loc, 0, 1, WHITE);;
        }

        //options
        if(CheckCollisionPointRec(MousePos, RecTex4))
        {
            DrawTextureEx(intro_txt4s, text4Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 4;
            }
        }
        else
        {
            DrawTextureEx(intro_txt4, text4Loc, 0, 1, WHITE);
        }

        //exit
        if(CheckCollisionPointRec(MousePos, RecTex5) )
        {
            DrawTextureEx(intro_txt5s, text5Loc, 0, 1, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 0;
            }
        }
        else
        {
            DrawTextureEx(intro_txt5, text5Loc, 0, 1, WHITE);
        }
        
        
        //DrawTexture(intro_txt4, textwidth, text4, WHITE);
        //DrawTexture(intro_txt5, textwidth, text5, WHITE);
        
    EndDrawing();
}