#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Action3::Action3(std::string action, json data, int spriteWidth, int spriteHeight, int imageWidth, int imageHeight, int FPS, std::ifstream &file) : Action1(action, data, spriteWidth, spriteHeight, imageWidth, imageHeight, FPS, file) {
                                                                                                                                               // protected:
                                                                                                                                           };

void Action3::option1()
{
    counter++;
    if (counter >= (fps / 3) * 2)
    {
        counter = 0;
        if (frame == 4)
        {
            frame = 6;
        }
        else if (frame == 8)
        {
            frame = 10;
        }
        else
        {
            frame++;
        }

        if (frame > 19)
        {
            frame = 19;
        }
    }
};

void Action3::option2()
{
    counter++;
    if (counter >= (fps / 3) * 2)
    {
        counter = 0;

        if (frame == 5)
        {
            frame = 10;
        }
        else
        {
            frame++;
        }

        if (frame > 19)
        {
            frame = 19;
        }
    }
};

void Action3::option3()
{
    counter++;
    if (counter >= (fps / 3) * 2)
    {
        counter = 0;
        if (frame == 4)
        {
            frame = 8;
        }
        else
        {
            frame++;
        }

        if (frame > frameCount - 1)
        {
            frame = frameCount - 1;
        }
    }
};

void Action3::option4()
{
    counter++;
    if (counter >= fps)
    {
        counter = 0;
        frame++;

        if (frame > frameCount - 1)
        {
            frame = frameCount - 1;
        }
    }
};