#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Action4::Action4(std::string action, json data, int spriteWidth, int spriteHeight, int imageWidth, int imageHeight, int FPS, std::ifstream &file) : Action1(action, data, spriteWidth, spriteHeight, imageWidth, imageHeight, FPS, file)
{
    char filename[100];
    sprintf(filename, "%sX", action.c_str());
    hurtBoxX = data[filename];

    sprintf(filename, "%sY", action.c_str());
    hurtBoxY = data[filename];

    sprintf(filename, "%sHeight", action.c_str());
    hurtBoxHeight = data[filename];

    sprintf(filename, "%sWidth", action.c_str());
    hurtBoxWidth = data[filename];

    sprintf(filename, "%sDamage", action.c_str());
    damage = data[filename];

    sprintf(filename, "%sKnockback", action.c_str());
    knockback = data[filename];

};

bool Action4::hit()
{
    counter++;

    if (counter >= (fps / 2)) // time to update frame
    {
        counter = 0;

        if (frame == frameCount / 2)
        {
            if (Delay(2))
            {
                frame++;
                return true; // strike moment with delay
            }
        }
        else if (frame >= frameCount - 1)
        {
            frame = -1;
            return false; // finished
        }
        else
        {
            frame++;
            return false;
        }
    }

    return false;
}
