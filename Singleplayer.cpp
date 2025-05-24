#include "ball.h"
#include <iostream>
#include <raylib.h>

#define CH_FRAME_COUNT1 6

// extern Texture2D bg_anime[FRAME_COUNT1]; // Ensure it's loaded before calling this function
// extern Texture2D ch1_anime[CH_FRAME_COUNT1];
// extern Texture2D ch2_anime[CH_FRAME_COUNT1];
/*
void BoxResize(Rectangle *rect, float scale, float oldScale, int monitorWidth, int gap)
{
    if (oldScale != scale)
    {
        float factor = 0.4f;
        rect->x = rect->x + (rect->x * (scale / oldScale) - rect->x) * factor;
        rect->width = rect->width * scale / oldScale;
        rect->height = rect->height * scale / oldScale;

        if (rect->x > monitorWidth - (gap + rect->width))
        {
            rect->x = monitorWidth - (gap + rect->width);
        }
        if (rect->x < gap)
        {
            rect->x = gap;
        }
    }
}
*/
/*
void adjustScale(float *scale)
{
    if (*scale > 1.3)
        *scale = 1.3;
    else if (*scale < 1)
        *scale = 1;
}
        */

void falling(Character *character, float floor, float gravity)
{
    character->jumpV += gravity * GetFrameTime();
    character->entityBoxHead.y += character->jumpV * GetFrameTime();
    if (character->entityBoxHead.y + character->entityBoxHead.height + character->entityBoxBody.height + character->entityBoxLegs.height >= floor)
    {
        character->onFloor = true;
        character->entityBoxHead.y = floor - character->entityBoxHead.height - character->entityBoxBody.height - character->entityBoxLegs.height;
        character->jumpV = 0;
    }
    else
    {
        character->onFloor = false;
    }
}

void drag(Character *character, float friction)
{
    if (character->pushover > 0)
    {
        if (character->leftSide)
        {
            character->entityBoxHead.x -= character->pushover * GetFrameTime();
        }
        else
        {
            character->entityBoxHead.x += character->pushover * GetFrameTime();
        }
        character->pushover -= friction * GetFrameTime();
    }
}

void updateKey(Character *character, int KEY)
{
    if (IsKeyPressed(KEY))
    {
        character->prevKeyPressed = character->keyPressed;
        character->keyPressed = KEY;
    }
    if (IsKeyDown(KEY))
    {
        character->keyDown = KEY;
    }
}

void updateMovementGamepad(Character *character)
{
    float axisX = GetGamepadAxisMovement(character->player, GAMEPAD_AXIS_LEFT_X);
    float axisY = GetGamepadAxisMovement(character->player, GAMEPAD_AXIS_LEFT_Y);
    float threshold = 0.5f;

    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || axisY > threshold)
        character->down = true;
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || axisY > threshold)
        character->downHold = true;

    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_LEFT_FACE_UP) || axisY < -threshold)
        character->up = true;
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_LEFT_FACE_UP) || axisY < -threshold)
        character->upHold = true;

    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || axisX > threshold)
        character->right = true;
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || axisX > threshold)
        character->rightHold = true;

    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || axisX < -threshold)
        character->left = true;
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || axisX < -threshold)
        character->leftHold = true;

    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        character->rightTrigger1 = true;
    }
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        character->rightTrigger1Hold = true;
    }
    if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        character->leftTrigger1 = true;
    }
    if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        character->leftTrigger1Hold = true;
    }
}

void updateAttackGamepad(Character *character)
{
    if (character->priority == 0)
    {
        if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {
            character->cross = true;
        }
        if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {
            character->crossHold = true;
        }

        if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_RIGHT_FACE_UP))
        {
            character->triangle = true;
        }
        if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_RIGHT_FACE_UP))
        {
            character->triangleHold = true;
        }

        if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        {
            character->circle = true;
        }
        if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        {
            character->circleHold = true;
        }

        if (IsGamepadButtonPressed(character->player, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        {
            character->square = true;
        }
        if (IsGamepadButtonDown(character->player, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        {
            character->squareHold = true;
        }
    }
}

void resetGamepad(Character *character)
{
    character->up = false;
    character->down = false;
    character->left = false;
    character->right = false;
    // character->triangle = false;
    // character->circle = false;
    // character->cross = false;
    // character->square = false;
    character->leftTrigger1 = false;
    character->leftTrigger2 = false;
    character->rightTrigger1 = false;
    character->rightTrigger2 = false;

    character->upHold = false;
    character->downHold = false;
    character->leftHold = false;
    character->rightHold = false;
    // character->triangleHold = false;
    // character->circleHold = false;
    // character->crossHold = false;
    // character->squareHold = false;
    character->leftTrigger1Hold = false;
    character->leftTrigger2Hold = false;
    character->rightTrigger1Hold = false;
    character->rightTrigger2Hold = false;
}

void checkSide(Character *character1, Character *character2)
{
    if (character1->entityBoxHead.x > character2->entityBoxHead.x)
    {
        character2->leftSide = true;
        character1->leftSide = false;
    }
    else
    {
        character2->leftSide = false;
        character1->leftSide = true;
    }
}

bool handleAttackInput(Character *character, bool *inputFlag, Action4 *attackAnim, Character *characterS)
{
    if (*inputFlag)
    {
        character->priority = 5;
        character->curr = attackAnim->returnTexture();
        character->currR = attackAnim->returnTextureR();

        if (attackAnim->hit()) // active strike frame
        {
            if (character->leftSide)
            {
                character->hurtBox.x = character->entityBoxHead.x + attackAnim->hurtBoxX;
                character->hurtBox.y = character->entityBoxHead.y + attackAnim->hurtBoxY;
                character->hurtBox.width = attackAnim->hurtBoxWidth;
                character->hurtBox.height = attackAnim->hurtBoxHeight;
            }
            else
            {

                character->hurtBox.width = attackAnim->hurtBoxWidth;
                character->hurtBox.height = attackAnim->hurtBoxHeight;
                character->hurtBox.x = character->entityBoxHead.x + attackAnim->hurtBoxX + (-1 * attackAnim->hurtBoxWidth);
                character->hurtBox.y = character->entityBoxHead.y + attackAnim->hurtBoxY;
            }

            if (CheckCollisionRecs(character->hurtBox, characterS->hitBoxHead))
            {
                characterS->priority = 10;
                characterS->gettingHit = true;

                characterS->currDamage = attackAnim->damage;
                character->knockback = attackAnim->knockback;
            }
            if (CheckCollisionRecs(character->hurtBox, characterS->hitBoxBody))
            {
                characterS->priority = 10;
                characterS->gettingHit = true;

                characterS->currDamage = attackAnim->damage;
                character->knockback = attackAnim->knockback;
            }
            if (CheckCollisionRecs(character->hurtBox, characterS->hitBoxLegs))
            {
                characterS->priority = 10;
                characterS->gettingHit = true;

                characterS->currDamage = attackAnim->damage;
                character->knockback = attackAnim->knockback;
            }
            character->attacking = true;
        }
        else
        {
            // Clear hurtbox once strike is over
            character->hurtBox = {0, 0, 0, 0};

            if (character->attacking)
            {
                character->attacking = false;
            }

            // If animation is complete, reset everything
            if (attackAnim->frame == -1) // we reset it in hit()
            {
                *inputFlag = false;
                character->priority = 0;
                attackAnim->frame = 0;
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void resetGamepadAttack(Character *character, bool *signal)
{
    character->triangle = false;
    character->circle = false;
    character->cross = false;
    character->square = false;
    *signal = true;
}

void attack(Character *character, Character *characterS)
{
    // if (!character->attacking)

    if (handleAttackInput(character, &character->triangle, character->idleAttack1, characterS))
    {
        resetGamepadAttack(character, &character->triangle);
    }
    else if (handleAttackInput(character, &character->circle, character->idleAttack2, characterS))
    {
        resetGamepadAttack(character, &character->circle);
    }
    else if (handleAttackInput(character, &character->square, character->idleAttack3, characterS))
    {
        resetGamepadAttack(character, &character->square);
    }
    else if (handleAttackInput(character, &character->cross, character->idleAttack4, characterS))
    {
        resetGamepadAttack(character, &character->cross);
    }
}

void hitAnimation(Character *characterP, int startFrame, int endFrame, bool blockSignal, Character *characterS)
{
    if (!characterP->hitAnim)
    {
        characterP->hit->frame = startFrame;
        characterP->hitAnim = true;
    }
    characterP->curr = characterP->hit->returnTexture();
    characterP->currR = characterP->hit->returnTextureR();
    characterP->hit->incFrame();

    if (characterP->currDamage > 0)
    {
        if (blockSignal)
        {
            characterP->knockback /= 2;
            characterP->currDamage /= 10;
        }
        characterP->pushover = characterS->knockback;
        characterS->knockback = 0;

        characterP->hp -= characterP->currDamage;
        characterP->currDamage = -1;
    }

    if (characterP->hit->frame == endFrame)
    {
        characterP->gettingHit = false;
        characterP->priority = 0;
        characterP->hitAnim = false;
        characterP->hit->resetFrame();
    }
}

void getHit(Character *characterP, Character *characterS)
{
    /*
    if (CheckCollisionRecs(characterP->hitBoxHead, characterS->hurtBox))
    {
        characterP->priority = 10;
        characterP->gettingHit = true;

    }
    */
    if (characterP->priority == 10)
    {
        if (!characterP->crouching)
        {
            if (!characterP->blockingU)
            {
                hitAnimation(characterP, 0, 4, characterP->blockingU, characterS);
            }
            else
            {
                hitAnimation(characterP, 10, 14, characterP->blockingU, characterS);
            }
        }
        else
        {
            if (!characterP->blockingD)
            {
                hitAnimation(characterP, 5, 9, characterP->blockingD, characterS);
            }
            else
            {
                hitAnimation(characterP, 15, 19, characterP->blockingU, characterS);
            }
        }
    }
}

void jumpPhysics(Character *character, float gravity)
{
    if (character->up || character->upHold || character->jumpStart)
    {
        if (character->onFloor)
        {
            character->jumpStart = true;
            character->memoryKey = character->prevKeyPressed;
            // character->jump->delay = 0;

            if (character->jump->Delay(character->jumpDelay))
            {
                {
                    // Make Character Jump
                    if (character->onFloor)
                    {
                        character->jumpV = character->jumpForce;
                        character->jumpStart = false;
                        character->hitboxChange = true;
                    }
                }
            }
        }
    }
}

void moveRightPhysics(Character *character, int primaryCharspd)
{
    if (!character->onFloor)
    {
        primaryCharspd = primaryCharspd * 3;
    }
    character->entityBoxHead.x += primaryCharspd * GetFrameTime();
}

void moveLeftPhysics(Character *character, int primaryCharspd)
{
    if (!character->onFloor)
    {
        primaryCharspd = primaryCharspd * 3;
    }
    character->entityBoxHead.x -= primaryCharspd * GetFrameTime();
}

void handleBoarder(Character *character, Rectangle *secondaryCharHitBox, int primaryCharspd, Background *background)
{
    if (character->leftSide)
    {
        if(character->entityBoxHead.x < background->gap)
        {
            character->entityBoxHead.x = background->gap;
            if ((int)secondaryCharHitBox->x < (int)(background->monitorWidth - (background->gap + secondaryCharHitBox->width)) && background->frame < 299)
            {
                if (!character->onFloor)
                {
                    primaryCharspd = primaryCharspd * 3;
                }
                secondaryCharHitBox->x += primaryCharspd * GetFrameTime();                                              // move char2 right
                if (secondaryCharHitBox->x > background->monitorWidth - (background->gap + secondaryCharHitBox->width)) // if char2 exceeds right boarder
                {
                    secondaryCharHitBox->x = background->monitorWidth - (background->gap + secondaryCharHitBox->width);
                }
                else
                {
                    background->incFrame();
                    if (!character->onFloor)
                    {
                        background->incFrame();
                        background->incFrame();
                    }
                }
            }
        }
        if(character->entityBoxHead.x + 500.0 > secondaryCharHitBox->x){
            character->entityBoxHead.x -= primaryCharspd * GetFrameTime();  
        }
    }
    else
    {
        if (character->entityBoxHead.x > background->monitorWidth - (background->gap + character->entityBoxHead.width))
        {
            character->entityBoxHead.x = background->monitorWidth - (background->gap + character->entityBoxHead.width); // keep Primary Char within right border
            if ((int)secondaryCharHitBox->x > (int)background->gap && background->frame > 0)                            // if seondary char is within left boarder
            {
                if (!character->onFloor)
                {
                    primaryCharspd = primaryCharspd * 3;
                }
                secondaryCharHitBox->x -= primaryCharspd * GetFrameTime(); // move char2 left
                if (secondaryCharHitBox->x < background->gap)              // if char2 exceeds right boarder
                {
                    secondaryCharHitBox->x = background->gap;
                }
                else
                {
                    background->decFrame();
                    if (!character->onFloor)
                    {
                        background->decFrame();
                        background->decFrame();
                    }
                }
            }
        }
        if(character->entityBoxHead.x < secondaryCharHitBox->x + 500.0 ){
            character->entityBoxHead.x += primaryCharspd * GetFrameTime();  
        }
    }
}

int jumpFunction(int x)
{
    return (1.5f / 4410000.0f) * x * x + (11.0f / 4200.0f) * x + 7.0f;
}

void jumpAnimation(Character *character, Rectangle *secondaryChar, int Primcharspd, Background *background)
{
    if (!character->onFloor || character->jumpV < 0 || character->jumpStart)
    {
        character->priority = 3;
        character->curr = character->jump->returnTexture();
        character->currR = character->jump->returnTextureR();

        /*
        if (character->jump->returnFrame() == (character->jump->returnFrameCount() - 1))
        {
            character->jumpStart = false;
        }
        character->jump->option4();
        */
        if (character->jump->frame < 3)
        {
            character->jump->option4();
        }
        else
        {
            character->jump->frame = jumpFunction(character->jumpV);
        }
        if (character->leftHold && !character->rightHold)
        {
            moveLeftPhysics(character, Primcharspd);
        }
        if (character->rightHold && !character->leftHold)
        {
            moveRightPhysics(character, Primcharspd);
        }
    }
    else
    {
        if (character->priority == 3)
        {
            character->priority = 0;
        }
        character->memoryKey = 0;
        character->jump->resetFrame();
    }
}

void crouchAnimation(Character *character, Rectangle *secondaryChar, int Primcharspd, Background *background)
{
    if (character->downHold)
    {
        character->priority = 2;
        if (character->crouch->frame < 5)
        {
            character->crouch->setFPS(3);
            character->curr = character->crouch->returnTexture();
            character->currR = character->crouch->returnTextureR();
            character->crouch->incFrame();
        }
        else
        {
            character->crouch->setFPS(6);
            character->crouching = true;
            character->curr = character->crouch->returnTexture();
            character->currR = character->crouch->returnTextureR();
            if (character->leftHold)
            {
                if (character->crouch->frame < 15 || character->crouch->frame > 24)
                {
                    character->crouch->frame = 24;
                }
                else
                {
                    character->crouch->decFrame();
                }
                moveLeftPhysics(character, Primcharspd);
            }
            else if (character->rightHold)
            {
                if (character->crouch->frame < 15 || character->crouch->frame >= 24)
                {
                    character->crouch->frame = 15;
                }
                else
                {
                    character->crouch->incFrame();
                }
                moveRightPhysics(character, Primcharspd);
            }
            else
            {
                if (character->crouch->frame < 5 || character->crouch->frame >= 14)
                {
                    character->crouch->frame = 5;
                }
                else
                {
                    character->crouch->incFrame();
                }
            }
        }
    }
    else if (character->crouching)
    {
        character->crouch->setFPS(3);
        character->curr = character->crouch->returnTexture();
        character->currR = character->crouch->returnTextureR();
        character->crouch->incFrame();
        if (character->crouch->frame < 25)
        {
            character->crouch->frame = 25;
        }
        if (character->crouch->frame >= character->crouch->frameCount - 1)
        {
            character->crouch->setFPS(6);
            character->priority = 0;
            character->crouching = false;
            character->crouch->resetFrame();
        }
    }
    else if (character->crouch->frame != 0)
    {
        character->crouch->setFPS(3);
        character->curr = character->crouch->returnTexture();
        character->currR = character->crouch->returnTextureR();
        character->crouch->decFrame();
        if (character->crouch->frame <= 0)
        {
            character->priority = 0;
            character->crouch->resetFrame();
        }
    }
}

void blockAnimation(Character *character)
{
    if (character->rightTrigger1Hold)
    {
        if (!character->crouching)
        {
            if (!character->downHold)
            {
                if (character->priority != 4)
                {
                    character->block->frame = 33;
                    character->priority = 4;
                    character->block->setFPS(3);
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->crouch->resetFrame();
                character->block->decFrame();
                if (character->block->frame == 29)
                {
                    character->blockingU = true;
                    character->blockingD = false;
                    character->block->setFPS(6);
                }
                if (character->block->frame <= 20)
                {
                    character->block->setFPS(6);
                    character->block->frame = 28;
                }
            }
            else
            {
                if (character->block->frame > 19)
                {
                    character->blockingU = false;
                    character->blockingD = false;
                    character->block->frame = 19;
                    character->crouch->frame = 0;
                    character->priority = 4;
                    character->block->setFPS(3);
                    character->crouch->setFPS(3);
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->block->decFrame();
                character->crouch->incFrame();

                if (character->block->frame == 15)
                {
                    character->crouching = true;
                }

                // character->crouching = true;
            }
        }
        else
        {
            if (character->downHold)
            {
                if (character->priority != 4)
                {
                    character->block->frame = 0;
                    character->priority = 4;
                    character->block->setFPS(3);
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->block->incFrame();
                if (character->block->frame == 5)
                {
                    character->blockingU = false;
                    character->blockingD = true;
                    character->block->setFPS(6);
                }
                if (character->block->frame >= 14)
                {
                    character->block->setFPS(6);
                    character->block->frame = 5;
                }
            }
            else
            {
                if (character->block->frame < 15)
                {
                    character->blockingU = false;
                    character->blockingD = false;
                    character->block->frame = 15;
                    character->block->setFPS(3);
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->crouch->resetFrame();
                character->block->incFrame();
                if (character->block->frame == 19)
                {
                    character->crouching = false;
                }
            }
        }
    }
    else if (character->block->frame != 0)
    {
        if (character->crouching)
        {
            if (character->downHold)
            {
                if (character->blockingD == true)
                {
                    character->blockingD = false;
                    character->block->frame = 4;
                    character->block->setFPS(3);
                    character->crouch->frame = 5;
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->block->decFrame();
            }
            else
            {
                if (character->blockingD == true)
                {
                    character->blockingD = false;
                    character->block->frame = 15;
                    character->block->setFPS(3);
                }
                character->curr = character->block->returnTexture();
                character->currR = character->block->returnTextureR();
                character->block->incFrame();
                character->block->incFrame();
                // character->block->incFrame();
                if (character->block->frame == 19 || character->block->frame == 20)
                {
                    character->block->frame = 29;
                }
                if (character->block->frame >= 33)
                {
                    character->block->frame = 0;
                }
            }
        }
        else
        {
            if (character->blockingU == true)
            {
                character->blockingU = false;
                character->block->frame = 29;
                character->block->setFPS(3);
            }
            character->curr = character->block->returnTexture();
            character->currR = character->block->returnTextureR();
            character->block->incFrame();
            if (character->block->frame == 33)
            {
                character->block->frame = 0;
            }
        }
    }
    else
    {
        if (character->priority == 4)
        {
            character->priority = 0;
            character->block->setFPS(6);
        }
    }
}

void moveLeftAnimation(Character *character, Rectangle *secondaryCharHitBox, int primaryCharspd, Background *background, int gap, int monitorWidth)
{
    character->priority = 1;
    character->curr = character->walk->returnTexture();
    character->currR = character->walk->returnTextureR();
    if (character->entityBoxHead.x < secondaryCharHitBox->x) // going backwards
    {
        character->walk->decFrame();
        character->walk->resetCycleDec();
    }
    else // going forward
    {
        character->walk->incFrame();
        character->walk->resetCycleInc();
    }

    // character1.decFrame();
}

void moveRightAnimation(Character *character, Rectangle *secondaryCharHitBox, int primaryCharspd, Background *background, int gap, int monitorWidth)
{
    character->priority = 1;
    character->currR = character->walk->returnTextureR();
    character->curr = character->walk->returnTexture();
    if (character->entityBoxHead.x < secondaryCharHitBox->x) // going forward
    {
        character->walk->incFrame();
        character->walk->resetCycleInc();
    }
    else // going backward
    {
        character->walk->decFrame();
        character->walk->resetCycleDec();
    }
}

void handleMovement(Character *character, Rectangle *opponentBox, int speed, Background *background, int screenWidth)
{
    if (character->priority > 1)
        return;

    if (character->leftHold && !character->rightHold)
    {
        moveLeftPhysics(character, speed);
        moveLeftAnimation(character, opponentBox, speed, background, background->gap, screenWidth);
    }
    else if (character->rightHold && !character->leftHold)
    {
        moveRightPhysics(character, speed);
        moveRightAnimation(character, opponentBox, speed, background, background->gap, screenWidth);
    }
    else
    {
        if (character->priority == 1)
        {
            character->priority = 0;
        }
    }
}

void hpWhite(Character *characterP, Character *characterS)
{
    if (characterP->attacking)
    {
        if (characterS->player == 0)
        {
            if (characterS->hp >= 0)
            {
                float hpRatio = (float)characterS->hp / 1000.0;
                characterS->sourceW = {(1.0f - hpRatio) * 800, 0, hpRatio * 800, 54};
                characterS->destW = {(float)100 + ((1.0f - hpRatio) * 800), (float)100, hpRatio * 800, 54};
            }
            else
            {
                characterS->hp = 0;
                characterS->sourceW = {800, 0, 0, 54};
                characterS->destW = {(float)100 + (1.0f * 800), (float)100, 0, 54};
            }
        }
        else if (characterS->player == 1)
        {
            if (characterS->hp >= 0)
            {
                float hpRatio = (float)characterS->hp / 1000.0;
                characterS->sourceW = {0, 0, hpRatio * 800, 54};
                characterS->destW = {(float)1000, (float)100, hpRatio * 800, 54};
            }
        }
    }
}

void hpRed(Character *character)
{
    float dif = character->sourceR.width - character->sourceW.width;
    if (dif > 0.5f)
    {
        if (character->player == 0)
        {
            character->sourceR.x = character->sourceR.x + 1;
            character->sourceR.width = character->sourceR.width - 1;
            character->destR.x = character->destR.x + 1;
            character->destR.width = character->destR.width - 1;
        }
        else if (character->player == 1)
        {
            character->sourceR.width = character->sourceR.width - 1;
            character->destR.width = character->destR.width - 1;
        }
    }
    /*
    if(character->destR.width > character->destR.width){
        character->destR.x = character->destR.x + 1;
        character->destR.width = character->destR.width - 1;
    }
    */
}

void singlePlayer(int *screen, int bg, int char1, int char2, int monitorWidth, int monitorHeight)
{
    // Background, Character1, charcater2 initialization
    char jsonA[50]; // Array to store location of background data
    sprintf(jsonA, "resources/backgrounds/background%d/bgData.json", bg + 1);
    Background background(jsonA);

    // sprintf(jsonA, "resources/characters/character%d/charData.json", char1+1);
    sprintf(jsonA, "resources/characters/character%d/charData.json", char1 + 1);
    Character character1(jsonA, background.ch1X, background.ch1X, 0);

    sprintf(jsonA, "resources/characters/character%d/charData.json", char2 + 1);
    Character character2(jsonA, background.ch2X, background.ch2X, 1);

    Image img;

    img = LoadImage("resources/GUI/hpFrame.png");
    ImageResize(&img, 800, 54);
    Texture2D hpFrameIMG = LoadTextureFromImage(img);
    ImageFlipHorizontal(&img);
    Texture2D hpFrameIMGR = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/GUI/hpWhite.png");
    ImageResize(&img, 800, 54);
    Texture2D hpWhiteIMG = LoadTextureFromImage(img);
    ImageFlipHorizontal(&img);
    Texture2D hpWhiteIMGR = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("resources/GUI/hpRed.png");
    ImageResize(&img, 800, 54);
    Texture2D hpRedIMG = LoadTextureFromImage(img);
    ImageFlipHorizontal(&img);
    Texture2D hpRedIMGR = LoadTextureFromImage(img);

    UnloadImage(img);

    float char1spd = background.retSpeed(); // Movement speed for character 1
    float char2spd = background.retSpeed(); // Movement speed for character 2
    float gravity = 5000.0;
    float friction = 5000.0;
    float floor = 1030;

    // Color shadowColor = BLACK; // Shadow color
    // shadowColor.a = 100;

    Color char1C_E = LIME;
    char1C_E.a = 100;

    Color char2C_E = DARKGREEN;
    char2C_E.a = 100;

    Color char1C_H = BLUE;
    char1C_H.a = 100;

    Color char2C_H = DARKBLUE;
    char2C_H.a = 100;

    Color char1C_Hu = RED;
    char1C_H.a = 100;

    Color char2C_Hu = MAROON;
    char2C_H.a = 100;

    float offsetXL = -84;
    float offsetXR = -239;
    float offsetY = -46;

    Rectangle pointer = {0, 0, 2, 2};

    // float offsetXSH = -80;
    // float offsetYSH = 18;

    // float scale = 1.3;
    // float oldScale = scale;

    Vector2 bgLoc;
    // Rectangle char1HitBox = {400, 250, 200.0f, 540.0f};
    // Rectangle char2HitBox = {1300, 250, 200.0f, 540.0f};

    // int FRAME_COUNT = background.getFrameCount();

    // int ch1Frame = 0;
    // int ch2Frame = 0;

    while (!WindowShouldClose())
    {

        falling(&character1, floor, gravity);
        falling(&character2, floor, gravity);

        drag(&character1, friction);
        drag(&character2, friction);

        updateMovementGamepad(&character1);
        updateMovementGamepad(&character2);
        updateAttackGamepad(&character1);
        updateAttackGamepad(&character2);

        checkSide(&character1, &character2);

        if (character1.priority <= 10)
        {
            getHit(&character1, &character2);
        }

        if (character2.priority <= 10)
        {
            getHit(&character2, &character1);
        }

        if (character1.priority == 0 || character1.priority == 5)
        {
            attack(&character1, &character2);
        }

        if (character2.priority == 0 || character2.priority == 5)
        {
            attack(&character2, &character1);
        }
        if (character1.priority <= 4)
        {
            blockAnimation(&character1);
        }
        if (character2.priority <= 4)
        {
            blockAnimation(&character2);
        }

        if (character1.priority <= 3)
        {
            jumpAnimation(&character1, &character2.entityBoxHead, char1spd, &background);
        }
        if (character2.priority <= 3)
        {
            jumpAnimation(&character2, &character1.entityBoxHead, char2spd, &background);
        }

        // if (character1.priority <= 2 || character1.downHold)
        if (character1.priority <= 2)
        {
            crouchAnimation(&character1, &character2.entityBoxHead, char1spd, &background);
        }

        if (character2.priority <= 2)
        {
            crouchAnimation(&character2, &character1.entityBoxHead, char2spd, &background);
        }

        jumpPhysics(&character1, gravity);
        handleMovement(&character1, &character2.entityBoxHead, char1spd, &background, monitorWidth);
        handleBoarder(&character1, &character2.entityBoxHead, char1spd, &background);

        jumpPhysics(&character2, gravity);
        handleMovement(&character2, &character1.entityBoxHead, char2spd, &background, monitorWidth);
        handleBoarder(&character2, &character1.entityBoxHead, char2spd, &background);

        // Handling falling

        // BOP

        if (character1.priority == 0)
        {
            character1.curr = character1.idle->returnTexture();
            character1.currR = character1.idle->returnTextureR();
            character1.idle->incFrame();
            character1.walk->resetFrame();
        }
        else
        {
            character1.idle->resetFrame();
        }
        if (character2.priority == 0)
        {
            character2.curr = character2.idle->returnTexture();
            character2.currR = character2.idle->returnTextureR();
            character2.idle->incFrame();
            character2.walk->resetFrame();
        }
        else
        {
            character2.idle->resetFrame();
        }

        character1.boxUpdate();
        character2.boxUpdate();

        /*
        if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_D))
        {
        }
        */
        // oldScale = scale;

        float distance = character1.entityBoxHead.x - character2.entityBoxHead.x;
        if (distance < 0)
        {
            distance = -distance;
        }

        resetGamepad(&character1);
        resetGamepad(&character2);

        // scale = 1.0f + (0.3f * (1 - (distance / (monitorWidth - (2 * background.gap + character1.entityBox.width)))));
        // adjustScale(&scale);

        // Drawing logic
        BeginDrawing();
        ClearBackground(RAYWHITE); // Clear previous frame

        // bgLoc = {-1 * (((scale * monitorWidth) - monitorWidth)) / 2, -1 * ((scale * floor) - floor)};
        bgLoc = {0, 0};

        // BOPBOP
        // DrawTextureEx(background.getTexture(), bgLoc, 0, scale, WHITE);
        DrawTextureEx(background.getTexture(), bgLoc, 0, 1, WHITE);

        // BoxResize(&character1.entityBox, scale, oldScale, monitorWidth, background.gap);
        // BoxResize(&character2.entityBox, scale, oldScale, monitorWidth, background.gap);
        // BoxResize(&character1.hitBox, scale, oldScale, monitorWidth, background.gap);
        // BoxResize(&character2.hitBox, scale, oldScale, monitorWidth, background.gap);

        // Draw the hitboxes (characters) with their updated positions
        // FOP

        //
        // DrawRectanglePro(character2.entityBox, (Vector2){0, 0}, 0, char2C_E);

        /*
        DrawRectanglePro(character2.hurtBox, (Vector2){0, 0}, 0, char1C_Hu);
        DrawRectanglePro(character2.hitBoxHead, (Vector2){0, 0}, 0, char2C_H);
        DrawRectanglePro(character2.hitBoxBody, (Vector2){0, 0}, 0, char2C_H);
        DrawRectanglePro(character2.hitBoxLegs, (Vector2){0, 0}, 0, char2C_H);

        // DrawRectanglePro(character1.entityBox, (Vector2){0, 0}, 0, char1C_E);
        DrawRectanglePro(character1.hurtBox, (Vector2){0, 0}, 0, char1C_Hu);
        DrawRectanglePro(character1.hitBoxHead, (Vector2){0, 0}, 0, char1C_H);
        DrawRectanglePro(character1.hitBoxBody, (Vector2){0, 0}, 0, char1C_H);
        DrawRectanglePro(character1.hitBoxLegs, (Vector2){0, 0}, 0, char1C_H);

        */
        DrawRectanglePro(pointer, (Vector2){0, 0}, 0, BLACK);

        Vector2 ch1Loc = {character1.entityBoxHead.x - 100, character1.entityBoxHead.y};
        Vector2 ch2Loc = {character2.entityBoxHead.x - 100, character2.entityBoxHead.y};

        if (IsKeyPressed(KEY_X) || IsKeyDown(KEY_X))
        {
            character1.jumpForce++;
            character2.jumpForce++;
        }
        if (IsKeyPressed(KEY_Y) || IsKeyDown(KEY_Y))
        {
            character1.jumpForce--;
            character2.jumpForce--;
        }
        /*
        if (IsKeyPressed(KEY_N))
        {
            character1.walk->fps++;
            character1.idle->fps++;
            character2.walk->fps++;
            character2.idle->fps++;
            background.fps++;
        }
        if (IsKeyPressed(KEY_P))
        {
            character1.walk->fps--;
            character1.idle->fps--;
            character2.walk->fps--;
            character2.idle->fps--;
            background.fps--;
        }
            */

        /*
    if (IsKeyPressed(KEY_P) || IsKeyDown(KEY_P))
    {
        pointer.x++;
    }
    if (IsKeyPressed(KEY_L) || IsKeyDown(KEY_L))
    {
        pointer.x--;
    }

    if (IsKeyPressed(KEY_O) || IsKeyDown(KEY_O))
    {
        pointer.y++;
    }
    if (IsKeyPressed(KEY_K) || IsKeyDown(KEY_K))
    {
        pointer.y--;
    }
        */

        if (IsKeyPressed(KEY_P) || IsKeyDown(KEY_P))
        {
            character1.idleAttack1->hurtBoxX++;
        }
        if (IsKeyPressed(KEY_L) || IsKeyDown(KEY_L))
        {
            character1.idleAttack1->hurtBoxX--;
        }

        if (IsKeyPressed(KEY_O) || IsKeyDown(KEY_O))
        {
            character1.idleAttack1->hurtBoxY++;
        }
        if (IsKeyPressed(KEY_K) || IsKeyDown(KEY_K))
        {
            character1.idleAttack1->hurtBoxY--;
        }

        if (IsKeyDown(KEY_SPACE))
        {
            character2.rightTrigger1Hold = true;
            character2.rightTrigger1 = true;
        }

        // DrawText(TextFormat("Hx: %f\nHy: %f\nfactor: %f\ncrouchF: %d\njumpF: %d\nblockF: %d\npriority: %d", pointer.x, pointer.y, character1.factor, character1.crouch->frame, character1.jump->frame, character1.block->frame, character1.priority), 200, 50, 50, RED);
        // DrawText(TextFormat("Hx: %f\nHy: %f\n1hp: %f\nwidth: %f\n2hp: %f\nwidth: %f\n", character1.idleAttack1->hurtBoxX, character1.idleAttack1->hurtBoxY, character1.hp, character1.hpWhite.width, character2.hp, character2.hpWhite.width), 200, 50, 50, RED);

        if (character1.cross)
        {
            DrawText(TextFormat("cross: true"), 800, 100, 50, RED);
        }
        else
        {
            DrawText(TextFormat("cross: false"), 800, 100, 50, RED);
        }

        if (character1.circle)
        {
            DrawText(TextFormat("circle: true"), 800, 150, 50, RED);
        }
        else
        {
            DrawText(TextFormat("circle: false"), 800, 150, 50, RED);
        }

        if (character1.square)
        {
            DrawText(TextFormat("square: true"), 800, 200, 50, RED);
        }
        else
        {
            DrawText(TextFormat("square: false"), 800, 200, 50, RED);
        }

        if (character1.triangle)
        {
            DrawText(TextFormat("triangle: true"), 800, 250, 50, RED);
        }
        else
        {
            DrawText(TextFormat("triangle: false"), 800, 250, 50, RED);
        }

        // BOP

        /*
        if (ch1Loc.x > ch2Loc.x)
        {

            // DrawTextureEx(character2.getTextureR(), {char2HitBox.x + offsetXL * scale + character2.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char2HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character2.curr, {character2.entityBox.x + offsetXL * scale + character2.WidthOffset * scale, character2.entityBox.y + offsetY + character2.HeightOffset * scale}, 0, scale * 0.8f, WHITE);

            // DrawTextureEx(character1.getTexture(), {char1HitBox.x + offsetXR * scale + character1.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char1HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character1.currR, {character1.entityBox.x + offsetXR * scale + character1.WidthOffset * scale, character1.entityBox.y + offsetY + character1.HeightOffset * scale}, 0, scale * 0.8f, WHITE);
        }
        else
        {
            // DrawTextureEx(character1.getTextureR(), {char1HitBox.x + offsetXL * scale + character1.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char1HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character1.curr, {character1.entityBox.x + offsetXL * scale + character1.WidthOffset * scale, character1.entityBox.y + offsetY + character1.HeightOffset * scale}, 0, scale * 0.8f, WHITE);

            // DrawTextureEx(character2.getTexture(), {char2HitBox.x + offsetXR * scale + character2.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char2HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character2.currR, {character2.entityBox.x + offsetXR * scale + character2.WidthOffset * scale, character2.entityBox.y + offsetY + character2.HeightOffset * scale}, 0, scale * 0.8f, WHITE);
        }
        */

        /*
        UnloadTexture(character1.hpRed);
        UnloadTexture(character2.hpRed);
        UnloadTexture(character1.hpWhite);
        UnloadTexture(character2.hpWhite);
        character1.hpWhite = LoadTextureFromImage(hpWhiteIMG);
        character2.hpWhite = LoadTextureFromImage(hpWhiteIMG);
        character1.hpRed = LoadTextureFromImage(hpRedIMG);
        character2.hpRed = LoadTextureFromImage(hpRedIMG);
        */

        Vector2 origin = {0, 0};

        hpWhite(&character1, &character2);
        hpWhite(&character2, &character1);

        hpRed(&character1);
        hpRed(&character2);

        DrawTexturePro(hpRedIMG, character1.sourceR, character1.destR, origin, 0.0f, WHITE);
        DrawTexturePro(hpRedIMGR, character2.sourceR, character2.destR, origin, 0.0f, WHITE);

        DrawTexturePro(hpWhiteIMG, character1.sourceW, character1.destW, origin, 0.0f, WHITE);
        DrawTexturePro(hpWhiteIMGR, character2.sourceW, character2.destW, origin, 0.0f, WHITE);

        DrawTexture(hpFrameIMG, 100, 100, WHITE);
        // DrawTextureEx(character1.hpRed, {(float)100 + (800 - character1.hpRed.width), (float)100}, 0, 1, WHITE);
        // DrawTextureEx(character1.hpWhite, {(float)100 + (800 - character1.hpWhite.width), (float)100}, 0, 1, WHITE);

        DrawTexture(hpFrameIMGR, 1000, 100, WHITE);
        // DrawTextureEx(character2.hpRed, {(float)100 + (800 - character2.hpRed.width), (float)300}, 0, 1, WHITE);
        // DrawTextureEx(character2.hpWhite, {(float)100 + (800 - character2.hpWhite.width), (float)300}, 0, 1, WHITE);

        if (ch1Loc.x > ch2Loc.x)
        {

            // DrawTextureEx(character2.getTextureR(), {char2HitBox.x + offsetXL * scale + character2.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char2HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character2.curr, {character2.entityBoxHead.x + offsetXL + character2.WidthOffset, character2.entityBoxHead.y + offsetY + character2.HeightOffset}, 0, 0.8f, WHITE);

            // DrawTextureEx(character1.getTexture(), {char1HitBox.x + offsetXR * scale + character1.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char1HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character1.currR, {character1.entityBoxHead.x + offsetXR + character1.WidthOffset, character1.entityBoxHead.y + offsetY + character1.HeightOffset}, 0, 0.8f, WHITE);
        }
        else
        {
            // DrawTextureEx(character1.getTextureR(), {char1HitBox.x + offsetXL * scale + character1.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char1HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character1.curr, {character1.entityBoxHead.x + offsetXL + character1.WidthOffset, character1.entityBoxHead.y + offsetY + character1.HeightOffset}, 0, 0.8f, WHITE);

            // DrawTextureEx(character2.getTexture(), {char2HitBox.x + offsetXR * scale + character2.getTextureR().width * scale + offsetXSH * scale, floor + (floor - char2HitBox.y) + offsetYSH * scale}, 180, scale * 0.8f, shadowColor);
            DrawTextureEx(character2.currR, {character2.entityBoxHead.x + offsetXR + character2.WidthOffset, character2.entityBoxHead.y + offsetY + character2.HeightOffset}, 0, 0.8f, WHITE);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_KP_0))
        {
            *screen = 1;
            break;
        }
    }
}