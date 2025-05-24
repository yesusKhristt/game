#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Action2::Action2(std::string action, json data, int spriteWidth, int spriteHeight, int imageWidth, int imageHeight, int FPS, std::ifstream &file) : Action1(action, data, spriteWidth, spriteHeight, imageWidth, imageHeight, FPS, file) {
                                                                                                                                                        // protected:
                                                                                                                                                    };

void Action2::setFPS(int x)
{
    fps = x;
}
void Action2::resetCycleInc()
{
    if (frame == 20)
    {
        frame = 5;
    }
};

void Action2::resetCycleDec()
{
    if (frame == 5)
    {
        frame = 20;
    }
};
