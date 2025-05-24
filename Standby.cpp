#include "ball.h"
#include <iostream>
#include <raylib.h>

extern Texture2D intro_bg3;
extern Texture2D intro_txt6;
extern Texture2D intro_txt6s;

void standBy(int* screen)
{
    float textwidth = 1650 ;
    float text6 = 950 ;

    Vector2 bgLoc = {0.0f,0.0f};
    Vector2 text6Loc = {textwidth,text6};

    float txt6Width = (float)intro_txt6.width ;
    float txt6Height = (float)intro_txt6.height ;


    Rectangle RecTex6 = {textwidth,text6,txt6Width,txt6Height};

    Vector2 MousePos = GetMousePosition();

    BeginDrawing();

        
        DrawTextureEx(intro_bg3, bgLoc, 0, 1, WHITE);
        
        if(CheckCollisionPointRec(MousePos, RecTex6))
        {
            DrawTextureEx(intro_txt6s, text6Loc, 0, 1, WHITE);
            //DrawText(TextFormat("Char pressed"), 10, 190, 20, DARKGRAY);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *screen = 1;
            }
        }
        else
        {
            DrawTextureEx(intro_txt6, text6Loc, 0, 1, WHITE);
            //DrawText(TextFormat("Char pressed"), 10, 190, 20, DARKGRAY);
        }
        
    EndDrawing();

}