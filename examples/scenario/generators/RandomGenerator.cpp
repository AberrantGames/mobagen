#include "RandomGenerator.h"
#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include <iostream>
// do not use this one to your assignment. this is my sample generator
std::vector<Color32> RandomScenarioGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;
//   create your own function for noise generation
  siv::BasicPerlinNoise<float> noise;
  noise.reseed(1337);
//  Noise noise(1337, 1024,0,255);
  for(int l=0; l<sideSize; l++){
    for(int c=0;c<sideSize; c++){
      float rgb = abs(noise.octave3D(c/50.0,l/50.0, displacement, 2)*255);
      colors.emplace_back(rgb, rgb, rgb);
//      double color = noise.noise(c/50.0,l/50.0);
//      colors.emplace_back(color,color,color);
    }
  }
  std::cout<<colors.size() << std::endl;

  colors = Fault(colors, sideSize, 25);
  return Limiar(colors, sideSize);
}
std::string RandomScenarioGenerator::GetName() { return "EXAMPLE"; }

std::vector<Color32> RandomScenarioGenerator::Limiar(std::vector<Color32> colors, int size) {
  std::vector<Color32> out;
  for (auto line = 0; line < size; line++) {
    for (auto column = 0; column < size; column++) {
      auto color = colors[(line * size) + column];

      if (color.r < 15) {
        out.push_back(gradient(Color::Blue, Color::Yellow, (color.r / 15.0f)));
      } else if (color.r < 50) {
        out.push_back(gradient(Color::Yellow, Color::Red, ((color.r - 15.0f) / 35.0f)));
      } else if (color.r < 100) {
        out.push_back(gradient(Color::Red, Color::Purple, ((color.r - 50.0f) / 50.0f)));
      } else if (color.r < 150) {
        out.push_back(gradient(Color::Purple, Color::White, ((color.r - 100.0f) / 50.0f)));
      } else if (color.r < 200) {
        out.push_back(gradient(Color::White, Color::Beige, ((color.r - 150.0f) / 50.0f)));
      } else {
        out.push_back(Color::Beige);
      }

      //if (color.r < 15) {
      //  out.push_back(gradient(Color::Blue, Color::Yellow, (color.r / 15.0f)));
      //} else if (color.r < 50) {
      //  out.push_back(gradient(Color::Yellow, Color::Green, ((color.r - 15.0f) / 35.0f)));
      //} else if (color.r < 100) {
      //  out.push_back(gradient(Color::Green, Color::Gray, ((color.r - 50.0f) / 50.0f)));
      //} else if (color.r < 200) {
      //  out.push_back(gradient(Color::Gray, Color::White, ((color.r - 100.0f) / 100.0f)));
      //} else {
      //  out.push_back(Color::White);
      //}
    }
  }
  return out;
}

Color32 RandomScenarioGenerator::gradient(Color32 color1, Color32 color2, float f) {
  Color32 newColor;

  newColor.r = color1.r * (1.0 - f) + (color2.r * f);
  newColor.g = color1.g * (1.0 - f) + (color2.g * f);
  newColor.b = color1.b * (1.0 - f) + (color2.b * f);

  return newColor;
}

std::vector<Color32> RandomScenarioGenerator::Fault(std::vector<Color32> colors, int size, int depth) {
  std::vector<Color32> out;
  int faultCenterX = rand() % size;
  int faultCenterY = rand() % size;
  float direction = rand() % 6;
  float dx = cos(direction);
  float dy = sin(direction);

  for (auto line = 0; line < size; line++) {
    for (auto column = 0; column < size; column++) {
      auto color = colors[(line * size) + column];

      float ox = faultCenterX - line;
      float oy = faultCenterY - column;
      float dp = ox * dx + oy * dy;

      if (dp > 0) {
        Color32 newColor;

        if (dp < dx + depth && dp < dy + depth) {
          newColor.r = color.r + dp;
          newColor.g = color.r + dp;
          newColor.b = color.r + dp;
          if (color.r + depth > 255) {
            newColor.r = 255.0f;
            newColor.g = 255.0f;
            newColor.b = 255.0f;
          }
        } else if (color.r + depth > 255) {
          newColor.r = 255.0f;
          newColor.g = 255.0f;
          newColor.b = 255.0f;
        } else {
          newColor.r = color.r + depth;
          newColor.g = color.r + depth;
          newColor.b = color.r + depth;
        }

        out.push_back(newColor);
      } else {
        Color32 newColor;

        if (dp > dx - depth && dp > dy - depth) {
          newColor.r = color.r + dp;
          newColor.g = color.r + dp;
          newColor.b = color.r + dp;
          if (color.r - depth < 0) {
            newColor.r = 0.0f;
            newColor.g = 0.0f;
            newColor.b = 0.0f;
          }
        } else if (color.r - depth < 0) {
          newColor.r = 0.0f;
          newColor.g = 0.0f;
          newColor.b = 0.0f;
        } else {
          newColor.r = color.r - depth;
          newColor.g = color.r - depth;
          newColor.b = color.r - depth;
        }

        out.push_back(newColor);
      }
    }
  }

  return out;
}