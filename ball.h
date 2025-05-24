#pragma once

#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

void titlescreen(int *, int *);
void standBy(int *);
// void standBy1(int* , float* );
void player1_Select(int *, int *);
void player2_Select(int *, int *, int char1);
void loadImages(int, int);
void background_Select(int *, int *, int, int);
void loadFiles(int, int, int, int, int, int *);
void singlePlayer(int *, int, int, int, int, int);
// void BoxResize(Rectangle *, float, float);

class Background
{
protected:
    Texture2D *bgArray; // Pointer to first frame (frame 0)
    // float scale;
    ;
    std::string address;
    // std::string jsonAddress;
    int counter;
    int fps;

public:
    int frameCount;
    int frame;
    int ch1X;
    int ch1Y;
    int ch2X;
    int ch2Y;
    int speed;
    int gap;
    int monitorWidth;
    int monitorHeight;

    Background(const std::string &jsonPath);

    int getFrame();
    int getFrameCount();
    Texture2D getTexture();
    int incFrame();
    int decFrame();
    int retSpeed();

    // Texture2D LoadTextureFromBinary(const std::string& filePath);
    // std::vector<std::string> GetDATFiles(const std::string& folder);

    ~Background();
};

class Action1
{
protected:
    Texture2D *Animation;
    Texture2D *AnimationR;

    int counter;

public:
    int frame;
    int fps;
    int frameCount;
    int delay;
    int flick;
    Action1(std::string, nlohmann::json, int, int, int, int, int, std::ifstream &);
    int incFrame();
    int decFrame();
    int Delay(int);
    Texture2D returnTexture();
    Texture2D returnTextureR();
    void resetFrame();
    int returnFrame();
    int returnFrameCount();

    ~Action1();
};

class Action2 : public Action1
{
public:
    int stage;
    Action2(std::string, nlohmann::json, int, int, int, int, int, std::ifstream &);
    void resetCycleInc();
    void resetCycleDec();
    void setFPS(int);
};

class Action3 : public Action1
{
public:
    Action3(std::string, nlohmann::json, int, int, int, int, int, std::ifstream &);
    void option1();
    void option2();
    void option3();
    void option4();
};

class Action4 : public Action1
{
public:
    float hurtBoxX;
    float hurtBoxY;
    float hurtBoxHeight;
    float hurtBoxWidth;
    int damage;
    int knockback;

    Action4(std::string, nlohmann::json, int, int, int, int, int, std::ifstream &);
    bool hit();
};

class Character
{
protected:
    std::string adress;
    float scale;

public:
    int player;
    Texture2D hpWhite;
    Texture2D hpRed;
    Rectangle sourceW;
    Rectangle destW;
    Rectangle sourceR;
    Rectangle destR;
    bool hitboxChange;
    bool hitboxReset;
    // float hitboxWidth;
    // float hitboxHeight;
    float HeightOffset;
    float WidthOffset;
    float jumpFactor;
    bool jumpStart;
    bool onFloor;
    int jumpDelay;
    int priority;
    float jumpV;
    float jumpForce;
    int keyPressed;
    int keyDown;
    int prevKeyPressed;
    int memoryKey;
    bool attacking;
    bool crouching;
    bool blockingU;
    bool blockingD;
    bool leftSide; // left is true, right is false
    bool gettingHit;
    bool hitAnim;
    float factor;
    float hp;
    float knockback;
    float pushover;
    int currDamage;

    bool up;
    bool down;
    bool left;
    bool right;
    bool triangle;
    bool circle;
    bool cross;
    bool square;
    bool leftTrigger1;
    bool leftTrigger2;
    bool rightTrigger1;
    bool rightTrigger2;

    bool upHold;
    bool downHold;
    bool leftHold;
    bool rightHold;
    bool triangleHold;
    bool circleHold;
    bool crossHold;
    bool squareHold;
    bool leftTrigger1Hold;
    bool leftTrigger2Hold;
    bool rightTrigger1Hold;
    bool rightTrigger2Hold;

    Rectangle entityBoxHead;
    Rectangle entityBoxBody;
    Rectangle entityBoxLegs;
    Rectangle hitBoxHead;
    Rectangle hitBoxBody;
    Rectangle hitBoxLegs;
    Rectangle hurtBox;
    Rectangle blockBoxU;
    Rectangle blockBoxD;
    Character(const std::string &jsonPath, float, float, int);
    void changeHeadBox(float, float, float, float, int, int, int, int, int);
    void changeBodyBox(float, float, float, float, int, int, int, int, int);
    void changeLegsBox(float, float, float, float, int, int, int, int, int);
    void resetBox();
    void boxUpdate();

    Texture2D curr;
    Texture2D currR;
    Action1 *idle;
    Action2 *walk;
    Action3 *jump;
    Action2 *crouch;
    Action2 *block;
    Action2 *hit;
    Action4 *idleAttack1;
    Action4 *idleAttack2;
    Action4 *idleAttack3;
    Action4 *idleAttack4;

    int getFrame();

    ~Character();
};
