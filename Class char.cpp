#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Character::Character(const std::string &jsonPath, float locX, float locY, int num)
{
    std::ifstream file(jsonPath);
    if (file)
    {
        json data;
        file >> data;
        file.close();

        int spriteWidth = data["spriteWidth"];
        int spriteHeight = data["spriteHeight"];
        float hitboxWidthHead = data["hitboxWidthHead"];
        float hitboxHeightHead = data["hitboxHeightHead"];
        float hitboxWidthBody = data["hitboxWidthBody"];
        float hitboxHeightBody = data["hitboxHeightBody"];
        float hitboxWidthLegs = data["hitboxWidthLegs"];
        float hitboxHeightLegs = data["hitboxHeightLegs"];
        int imageWidth = data["imageWidth"];
        int imageHeight = data["imageHeight"];
        jumpDelay = data["jumpDelay"];
        jumpForce = data["jumpForce"];
        jumpFactor = data["jumpFactor"];
        hp = data["hp"];

        player = num;
        knockback = 0;
        pushover = 0;
        jumpStart = 0;
        jumpV = 0;
        priority = 0;
        HeightOffset = 0;
        WidthOffset = 0;
        keyPressed = 0;
        prevKeyPressed = 0;
        memoryKey = 0;
        hitboxChange = false;
        hitboxReset = false;
        onFloor = false;
        attacking = false;
        crouching = false;
        gettingHit = false;

        up = false;
        down = false;
        left = false;
        right = false;
        triangle = false;
        circle = false;
        cross = false;
        square = false;
        leftTrigger1 = false;
        leftTrigger2 = false;
        rightTrigger1 = false;
        rightTrigger2 = false;

        upHold = false;
        downHold = false;
        leftHold = false;
        rightHold = false;
        triangleHold = false;
        circleHold = false;
        crossHold = false;
        squareHold = false;
        leftTrigger1Hold = false;
        leftTrigger2Hold = false;
        rightTrigger1Hold = false;
        rightTrigger2Hold = false;
        hitAnim = false;

        entityBoxHead = {locX, locY, hitboxWidthHead, hitboxHeightHead};
        entityBoxBody = {locX, locY, hitboxWidthBody, hitboxHeightBody};
        entityBoxLegs = {locX, locY, hitboxWidthLegs, hitboxHeightLegs};
        hitBoxHead = entityBoxHead;
        hitBoxBody = entityBoxBody;
        hitBoxLegs = entityBoxLegs;
        hurtBox = {0, 0, 0, 0};

        sourceW = {0, 0, 800.0, 54};
        sourceR = {0, 0, 800.0, 54};
        if (num == 0)
        {
            destW = {(float)100, (float)100, 800, 54};
            destR = {(float)100, (float)100, 800, 54};
        }
        else if(num == 1){
            destW = {(float)1000, (float)100, 800, 54};
            destR = {(float)1000, (float)100, 800, 54};
        }

        std::string address = data["movementAddress"];

        std::ifstream binaryFile(address, std::ios::binary);

        if (!binaryFile)
        {
            std::cerr << "Failed to open binary file: " << address << std::endl;
            return;
        }

        // Rewind to start each time before passing
        binaryFile.clear();
        binaryFile.seekg(0);
        idle = new Action1("idle", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.clear();
        binaryFile.seekg(0);
        walk = new Action2("walk", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.clear();
        binaryFile.seekg(0);
        jump = new Action3("jump", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.clear();
        binaryFile.seekg(0);
        crouch = new Action2("crouch", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.clear();
        binaryFile.seekg(0);
        block = new Action2("block", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.clear();
        binaryFile.seekg(0);
        hit = new Action2("hit", data, spriteWidth, spriteHeight, imageWidth, imageHeight, 6, binaryFile);

        binaryFile.close();

        std::string newAddress = data["attackAddress"];

        std::ifstream binaryAttackFile(newAddress, std::ios::binary);

        if (!binaryAttackFile)
        {
            std::cerr << "Failed to open binary file: " << newAddress << std::endl;
            return;
        }

        binaryAttackFile.clear();
        binaryAttackFile.seekg(0);
        idleAttack1 = new Action4("idleAttack1", data, spriteWidth, spriteHeight, imageHeight, imageHeight, 6, binaryAttackFile);

        binaryAttackFile.clear();
        binaryAttackFile.seekg(0);
        idleAttack2 = new Action4("idleAttack2", data, spriteWidth, spriteHeight, imageHeight, imageHeight, 6, binaryAttackFile);

        binaryAttackFile.clear();
        binaryAttackFile.seekg(0);
        idleAttack3 = new Action4("idleAttack3", data, spriteWidth, spriteHeight, imageHeight, imageHeight, 6, binaryAttackFile);

        binaryAttackFile.clear();
        binaryAttackFile.seekg(0);
        idleAttack4 = new Action4("idleAttack4", data, spriteWidth, spriteHeight, imageHeight, imageHeight, 6, binaryAttackFile);

        binaryAttackFile.close();
    }
}

int absoluteDiff(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1 - num2;
    }
    else
    {
        return num2 - num1;
    }
}

void Character::changeHeadBox(float xOffset, float yOffset, float widthFactor, float heightFactor, int curFrame, int initStart, int initEnd, int finStart, int finEnd)
{
    if (initStart <= curFrame && curFrame <= initEnd)
    {

        factor = (float)absoluteDiff(initStart, curFrame) / absoluteDiff(initStart, initEnd);
    }
    else if (finStart <= curFrame && curFrame <= finEnd)
    {
        factor = (float)absoluteDiff(finEnd, curFrame) / absoluteDiff(finStart, finEnd);
    }
    else
    {
        factor = 1;
    }

    hitBoxHead.y = entityBoxHead.y + (yOffset * factor);
    hitBoxHead.width = entityBoxHead.width + (entityBoxHead.width * (widthFactor - 1) * factor);
    hitBoxHead.height = entityBoxHead.height + (entityBoxHead.height * (heightFactor - 1) * factor);
    if (leftSide)
    {
        hitBoxHead.x = entityBoxHead.x + (xOffset * factor);
    }
    else
    {
        hitBoxHead.x = entityBoxHead.x + entityBoxHead.width - hitBoxHead.width + (xOffset * factor);
    }
}

void Character::changeBodyBox(float xOffset, float yOffset, float widthFactor, float heightFactor, int curFrame, int initStart, int initEnd, int finStart, int finEnd)
{

    if (initStart <= curFrame && curFrame <= initEnd)
    {

        factor = (float)absoluteDiff(initStart, curFrame) / absoluteDiff(initStart, initEnd);
    }
    else if (finStart <= curFrame && curFrame <= finEnd)
    {
        factor = (float)absoluteDiff(finEnd, curFrame) / absoluteDiff(finStart, finEnd);
    }
    else
    {
        factor = 1;
    }

    hitBoxBody.y = entityBoxHead.y + hitBoxHead.height + (yOffset * factor);
    hitBoxBody.width = entityBoxBody.width + (entityBoxBody.width * (widthFactor - 1) * factor);
    hitBoxBody.height = entityBoxBody.height + (entityBoxBody.height * (heightFactor - 1) * factor);
    if (leftSide)
    {

        hitBoxBody.x = entityBoxHead.x + (xOffset * factor);
    }
    else
    {
        hitBoxBody.x = entityBoxBody.x + entityBoxBody.width - hitBoxBody.width + (xOffset * factor);
    }
}

void Character::changeLegsBox(float xOffset, float yOffset, float widthFactor, float heightFactor, int curFrame, int initStart, int initEnd, int finStart, int finEnd)
{

    if (initStart <= curFrame && curFrame <= initEnd)
    {

        factor = (float)absoluteDiff(initStart, curFrame) / absoluteDiff(initStart, initEnd);
    }
    else if (finStart <= curFrame && curFrame <= finEnd)
    {
        factor = (float)absoluteDiff(finEnd, curFrame) / absoluteDiff(finStart, finEnd);
    }
    else
    {
        factor = 1;
    }

    hitBoxLegs.y = entityBoxHead.y + hitBoxHead.height + hitBoxBody.height + (yOffset * factor);

    hitBoxLegs.width = entityBoxLegs.width + (entityBoxLegs.width * (widthFactor - 1) * factor);
    hitBoxLegs.height = entityBoxLegs.height + (entityBoxLegs.height * (heightFactor - 1) * factor);
    if (leftSide)
    {
        hitBoxLegs.x = entityBoxHead.x + (xOffset * factor);
    }
    else
    {
        hitBoxLegs.x = entityBoxLegs.x + entityBoxLegs.width - hitBoxLegs.width + (xOffset * factor);
    }
}

void Character::resetBox()
{
    hitBoxHead = entityBoxHead;
    hitBoxBody = entityBoxBody;
    hitBoxLegs = entityBoxLegs;
}

void Character::boxUpdate()
{
    entityBoxBody.y = entityBoxHead.y + hitBoxHead.height;
    entityBoxLegs.y = entityBoxHead.y + hitBoxHead.height + hitBoxBody.height;

    if (leftSide)
    {
        entityBoxBody.x = entityBoxHead.x;
        entityBoxLegs.x = entityBoxHead.x;
        entityBoxLegs.y = entityBoxHead.y + hitBoxHead.height + hitBoxBody.height;
    }
    else
    {
        entityBoxBody.x = entityBoxHead.x - (entityBoxBody.width - entityBoxHead.width);
        entityBoxBody.y = entityBoxHead.y + hitBoxHead.height;
        entityBoxLegs.x = entityBoxHead.x - (entityBoxLegs.width - entityBoxHead.width);
    }
    if (crouch->frame > 0)
    {
        float crouchFactor = 0.6f;
        float yOffset = (entityBoxHead.height + entityBoxBody.height + entityBoxLegs.height) * (1.0f - crouchFactor); // move hitbox downward
        changeHeadBox(0.0f, yOffset, 1.5f, crouchFactor, crouch->frame, 0, 4, 25, 29);
        changeBodyBox(0.0f, yOffset, 0.9f, crouchFactor, crouch->frame, 0, 4, 25, 29);
        changeLegsBox(0.0f, yOffset, 1.3f, crouchFactor, crouch->frame, 0, 4, 25, 29);
    }
    else if (!onFloor)
    {
        changeHeadBox(0.0f, 0.0f, 1.1f, 0.5f, jump->frame, 0, 7, 8, 14);
        changeBodyBox(0.0f, 0.0f, 1.5f, 0.8f, jump->frame, 0, 7, 8, 14);
        changeLegsBox(0.0f, 0.0f, 1.0f, 0.5f, jump->frame, 0, 7, 8, 14);
    }
    else if (idleAttack1->frame > 0)
    {
        changeHeadBox(0.0f, 0.0f, 1.8f, 0.5f, idleAttack1->frame, 0, 4, 5, 9);
        changeBodyBox(0.0f, 0.0f, 2.0f, 0.8f, idleAttack1->frame, 0, 4, 5, 9);
        changeLegsBox(0.0f, 0.0f, 1.3f, 0.5f, idleAttack1->frame, 0, 4, 5, 9);
    }
    else
    {

        resetBox();
    }
}

/*
void Character::boxUpdate()
{
    if (!onFloor)
    {
        // if ( !hitboxReset)

        changeBox(0, 0, 1.0, 0.75);
        hitboxChange = false;
        hitboxReset = true;
    }
    else
    {
        // if (hitboxReset )

        hitboxReset = false;
        resetBox(); // just reset immediately
    }

    if (crouching)
    {
        // if ( !hitboxReset)

        changeBox(0.0, hitBox.height * 0.25, 1.0, 0.75);
        hitboxChange = false;
        hitboxReset = true;
    }
    else
    {
        // if (hitboxReset)

        hitboxReset = false;
        resetBox(); // just reset immediately
    }
}
    */

Character::~Character()
{
    delete idle;
}
