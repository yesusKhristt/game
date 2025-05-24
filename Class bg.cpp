#include "ball.h"
#include <iostream>
#include <raylib.h>
#include "json.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

using json = nlohmann::json;

/*
Background::Background(const std::string &jsonPath)
{
   std::ifstream file(jsonPath, std::ios::in); // open json file in path, read only
   if (file)
   {
      json data;
      file >> data;
      file.close();

      frameCount = data["frameCount"];
      monitorWidth = data["monitorWidth"];
      monitorHeight = data["monitorHeight"];

      if (frameCount > 0)
      {
         bgArray = new Texture2D[frameCount]; // Dynamically alocating memory for frames
      }
      else
      {
         bgArray = nullptr;
      }
      frame = frameCount / 2;
      std::string address = data["frameAddress"];

      for (int i = 0; i < frameCount; i++)
      {
         char filename[100];

         sprintf(filename, "%s/%04d.png", address.c_str(), i + 1); // modifies address in string and puts it to filename
         // sprintf(filename, "resources/backgrounds/background1/%04d.png", i + 1);  // Simplified filename formatting

         std::cout << "Loading: " << filename << std::endl; // Debugging output

         if (!FileExists(filename)) // Check if file exists
         {
            std::cout << "Error: File not found - " << filename << std::endl;
            continue;
         }

         Image img = LoadImage(filename);
         if (img.data == NULL) // Check if image loaded properly
         {
            std::cout << "Error: Could not load " << filename << std::endl;
            continue;
         }

         // ImageResize(&img, monitorWidth, monitorHeight);
         bgArray[i] = LoadTextureFromImage(img);
         UnloadImage(img);

         BeginDrawing();
         ClearBackground(RAYWHITE);

         // Debugging text
         DrawText(TextFormat("Loading Current Frame: %d / %d", i, frameCount), 50, 50, 20, DARKGRAY);

         EndDrawing();
      }
   }
}
*/

Background::Background(const std::string &jsonPath)
{
   std::ifstream file(jsonPath, std::ios::in); // open json file in path, read only
   if (file)
   {
      json data;
      file >> data;
      file.close();

      frameCount = data["frameCount"];
      monitorWidth = data["monitorWidth"];
      monitorHeight = data["monitorHeight"];
      speed = data["speed"];
      ch1X = data["ch1X"];
      ch1Y = data["ch1Y"];
      ch2X = data["ch2X"];
      ch2Y = data["ch2Y"];
      fps = data["fps"];
      gap = data["gap"];
      counter = 0;

      if (frameCount > 0)
      {
         bgArray = new Texture2D[frameCount]; // Dynamically alocating memory for frames
      }
      else
      {
         bgArray = nullptr;
      }
      frame = frameCount / 2;
      std::string address = data["frameAddress"];

      Image img = {};

      // Load first spritesheet before loop
      {
         char filename[256];
         sprintf(filename, "%s/ghetto_1.dat", address.c_str());

         std::ifstream file(filename, std::ios::binary);
         if (!file)
         {
            std::cerr << "Failed to load initial file: " << filename << std::endl;
            return;
         }

         file.read(reinterpret_cast<char *>(&img.width), sizeof(img.width));
         file.read(reinterpret_cast<char *>(&img.height), sizeof(img.height));
         file.read(reinterpret_cast<char *>(&img.format), sizeof(img.format));
         file.read(reinterpret_cast<char *>(&img.mipmaps), sizeof(img.mipmaps));

         size_t dataSize = GetPixelDataSize(img.width, img.height, img.format);
         img.data = malloc(dataSize);
         file.read(reinterpret_cast<char *>(img.data), dataSize);
         file.close();
      }

      for (int i = 0; i < frameCount; ++i)
      {
         Image frame = ImageFromImage(img,
                                      (Rectangle){(int)(i % 34) * (float)monitorWidth, 0, (float)monitorWidth, (float)monitorHeight});

         // ImageResize(&frame, monitorWidth, monitorHeight);
         bgArray[i] = LoadTextureFromImage(frame);
         UnloadImage(frame);

         BeginDrawing();
         ClearBackground(RAYWHITE);
         DrawText(TextFormat("Loading Background Frames: %d / %d", i, frameCount), 50, 50, 20, DARKGRAY);
         EndDrawing();

         // Only replace image when needed (every 34th frame)
         if ((i + 1) % 34 == 0)
         {
            UnloadImage(img);
            img = {};

            char filename[256];
            sprintf(filename, "%s/ghetto_%d.dat", address.c_str(), (i / 34) + 2);

            std::ifstream file(filename, std::ios::binary);
            if (!file)
            {
               std::cerr << "Failed to load: " << filename << std::endl;
               bgArray[i] = {}; // Set to empty texture
               continue;
            }

            file.read(reinterpret_cast<char *>(&img.width), sizeof(img.width));
            file.read(reinterpret_cast<char *>(&img.height), sizeof(img.height));
            file.read(reinterpret_cast<char *>(&img.format), sizeof(img.format));
            file.read(reinterpret_cast<char *>(&img.mipmaps), sizeof(img.mipmaps));

            size_t dataSize = GetPixelDataSize(img.width, img.height, img.format);
            img.data = malloc(dataSize);
            file.read(reinterpret_cast<char *>(img.data), dataSize);
            file.close();
         }
      }

      // After loop, safely free the last used spritesheet
      if (img.data != nullptr)
      {
         UnloadImage(img);
      }
   }
}

int Background::retSpeed()
{
   return speed;
}

int Background::getFrame()
{
   return frame;
}

int Background::getFrameCount()
{
   return frameCount;
}

Texture2D Background::getTexture()
{
   return bgArray[frame];
}

int Background::incFrame()
{
   counter++;
   if (counter >= fps)
   {
      counter = 0;
      frame++;
      if (frame > frameCount - 1)
      {
         frame = frameCount - 1;
         return 0;
      }
      else
      {
         return 1;
      }
   }

   return 0;
}

int Background::decFrame()
{
   counter++;
   if (counter >= fps)
   {
      counter = 0;
      frame--;
      if (frame < 0)
      {
         frame = 0;
         return 0;
      }
      else
      {
         return 1;
      }
   }
   return 0;
}

Background::~Background()
{
   if (bgArray)
   {
      for (int i = 0; i < frameCount; ++i)
      {
         UnloadTexture(bgArray[i]);
      }
      delete[] bgArray;
      bgArray = nullptr;
   }
}

/*
Texture2D Background::LoadTextureFromBinary(const std::string &filePath)
{
   std::ifstream file(filePath, std::ios::binary);
   if (!file)
   {
      std::cerr << "Failed to open .dat file: " << filePath << std::endl;
      return Texture2D{};
   }

   Image image = {};
   file.read(reinterpret_cast<char *>(&image.width), sizeof(image.width));
   file.read(reinterpret_cast<char *>(&image.height), sizeof(image.height));
   file.read(reinterpret_cast<char *>(&image.format), sizeof(image.format));
   file.read(reinterpret_cast<char *>(&image.mipmaps), sizeof(image.mipmaps));

   size_t dataSize = image.width * image.height * 4; // assuming uncompressed RGBA
   image.data = malloc(dataSize);
   file.read(reinterpret_cast<char *>(image.data), dataSize);

   Texture2D texture = LoadTextureFromImage(image);
   UnloadImage(image); // Free CPU memory, texture is now on GPU
   return texture;
}

std::vector<std::string> GetDATFiles(const std::string &folder)
{
   std::vector<std::string> files;
   DIR *dir = opendir(folder.c_str());
   if (!dir)
   {
      std::cerr << "Could not open folder: " << folder << std::endl;
      return files;
   }

   struct dirent *entry;
   while ((entry = readdir(dir)) != nullptr)
   {
      std::string filename = entry->d_name;
      if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".dat")
      {
         files.push_back(folder + "\\" + filename); // Windows-style
      }
   }

   closedir(dir);
   return files;
}
*/