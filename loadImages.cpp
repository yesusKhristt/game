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

extern Texture2D bg1;
extern Texture2D bg2;
extern Texture2D bg3;
extern Texture2D bg4;
extern Texture2D bg_s;

extern Texture2D ch1;
extern Texture2D ch2;
extern Texture2D ch3;
extern Texture2D ch4;
extern Texture2D ch1_s;
extern Texture2D ch2_s;
extern Texture2D ch3_s;
extern Texture2D ch4_s;

extern Texture2D blue_s;
extern Texture2D red_s;
extern Texture2D orange_s;
extern Texture2D blue_red_s;
extern Texture2D blue_orange_s;


void loadImages(int monitorWidth, int monitorHeight)
{
    Image img;

    img = LoadImage("resources/intro/bg_1.png");
    ImageResize(&img, monitorWidth, monitorHeight);
    intro_bg1 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/bg_2.png");
    ImageResize(&img, monitorWidth, monitorHeight);
    intro_bg2 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/bg_3.png");
    ImageResize(&img, monitorWidth, monitorHeight);
    intro_bg3 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_1.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt1 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_2.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt2 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_2s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt2s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_3.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt3 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_3s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt3s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_4.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt4 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_4s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt4s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_5.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt5 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_5s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt5s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_6.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt6 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/intro/text_6s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    intro_txt6s = LoadTextureFromImage(img);
    UnloadImage(img);

    //BACKGROUNDS

    img = LoadImage("resources/backgrounds/icons/background1.JPG");
    //ImageResize(&img, monitorWidth, monitorHeight);
    bg1 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/backgrounds/icons/background2.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    bg2 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/backgrounds/icons/background3.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    bg3 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/backgrounds/icons/background4.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    bg4 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/backgrounds/icons/background_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    bg_s = LoadTextureFromImage(img);
    UnloadImage(img);


    //CHARACTER PICS

    img = LoadImage("resources/characterPics/char1.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch1 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char2.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch2 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char3.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch3 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char4.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch4 = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char1_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch1_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char2_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch2_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char3_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch3_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/char4_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    ch4_s = LoadTextureFromImage(img);
    UnloadImage(img);


    //SELECT SQUARES

    img = LoadImage("resources/characterPics/blue_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    blue_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/red_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    red_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/orange_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    orange_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/blue_red_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    blue_red_s = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/characterPics/blue_orange_s.png");
    //ImageResize(&img, monitorWidth, monitorHeight);
    blue_orange_s = LoadTextureFromImage(img);
    UnloadImage(img);
}
