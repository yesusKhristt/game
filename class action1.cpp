#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Action1::Action1(std::string action, json data, int spriteWidth, int spriteHeight, int imageWidth, int imageHeight, int FPS, std::ifstream &file)
{
   frame = 0;
   // IDLE ANIMATION
   char filename[100];

   // sprintf(filename, "%sCount", action.c_str());
   //  modifies address in string and puts it to filename
   //  sprintf(filename, "resources/backgrounds/background1/%04d.png", i + 1);  // Simplified filename formatting
   // frameCount = data[filename];
   fps = FPS;
   int start;
   sprintf(filename, "%sStart", action.c_str());
   start = data[filename];
   int end;
   sprintf(filename, "%sEnd", action.c_str());
   end = data[filename];
   frameCount = end - start + 1;
   counter = 0;
   delay = 0;
   flick = 0;

   if (frameCount > 0)
   {
      Animation = new Texture2D[frameCount];
      AnimationR = new Texture2D[frameCount];
   }
   else
   {
      Animation = nullptr;
      AnimationR = nullptr;
   }

   // sprintf(filename, "%sAddress", action.c_str());

   if (!file)
   {
      std::cerr << "Failed to load: " << filename << std::endl;
      Animation = {}; // Set to empty texture
   }

   // Read image metadata
   Image spriteSheet = {};
   file.read(reinterpret_cast<char *>(&spriteSheet.width), sizeof(spriteSheet.width));
   file.read(reinterpret_cast<char *>(&spriteSheet.height), sizeof(spriteSheet.height));
   file.read(reinterpret_cast<char *>(&spriteSheet.format), sizeof(spriteSheet.format));
   file.read(reinterpret_cast<char *>(&spriteSheet.mipmaps), sizeof(spriteSheet.mipmaps));

   // Allocate and read image data (assuming RGBA)
   size_t dataSize = GetPixelDataSize(spriteSheet.width, spriteSheet.height, spriteSheet.format);
   spriteSheet.data = malloc(dataSize);
   file.read(reinterpret_cast<char *>(spriteSheet.data), dataSize);
   // file.close();

   for (int i = start; i <= end; i++)
   {
      // Crop a portion of the image (600x800 blocks)
      Image frame = ImageFromImage(spriteSheet,
                                   (Rectangle){i * (float)imageWidth, 0, (float)imageWidth, (float)imageHeight});

      // Convert cropped image to texture and store

      // ImageResize(&frame, spriteWidth, spriteHeight);
      Animation[i - start] = LoadTextureFromImage(frame);
      ImageFlipHorizontal(&frame);
      AnimationR[i - start] = LoadTextureFromImage(frame);

      // Clean up temp image
      UnloadImage(frame);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      // Debugging text
      DrawText(TextFormat("Loading Current Frame: %d / %d", i, frameCount), 50, 50, 20, DARKGRAY);

      EndDrawing();
   }

   // Done with full sprite sheet image
   UnloadImage(spriteSheet);
}

Texture2D Action1::returnTexture()
{
   return Animation[frame];
}

Texture2D Action1::returnTextureR()
{
   return AnimationR[frame];
}

void Action1::resetFrame()
{
   frame = 0;
}

int Action1::incFrame()
{
   counter++;
   if (counter >= fps)
   {
      // if (flick)
      //{
      flick = 0;
      counter = 0;
      frame++;
      if (frame > frameCount - 1)
      {
         frame = 0;
         return 0;
      }
      else
      {
         return 1;
      }
   }
   //}
   // return 0;
   else
   {
      return 0;
   }
}
int Action1::decFrame()
{
   counter++;
   if (counter >= fps)
   {
      // if (flick)
      //{
      flick = 0;
      counter = 0;
      frame--;
      if (frame < 0)
      {
         frame = frameCount - 1;
         return 0;
      }
      else
      {
         return 1;
      }
      //}
      // return 0;
   }
   else
   {
      return 0;
   }
}

int Action1::Delay(int time)
{
   delay++;
   if (delay == time)
   {
      delay = 0;
      return 1;
   }
   return 0;
}

int Action1::returnFrame()
{
   return frame;
}

int Action1::returnFrameCount()
{
   return frameCount;
}

Action1::~Action1()
{
   if (Animation)
   {
      for (int i = 0; i < frameCount; ++i)
      {
         UnloadTexture(Animation[i]);
      }
      delete[] Animation;
      Animation = nullptr;
   }

   if (AnimationR)
   {
      for (int i = 0; i < frameCount; ++i)
      {
         UnloadTexture(AnimationR[i]);
      }
      delete[] AnimationR;
      AnimationR = nullptr;
   }
}