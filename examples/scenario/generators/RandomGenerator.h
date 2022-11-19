#ifndef MOBAGEN_RANDOMSCENARIOGENERATOR_H
#define MOBAGEN_RANDOMSCENARIOGENERATOR_H

#include "../GeneratorBase.h"
#include "Vector2.h"
#include "Point2D.h"

class RandomScenarioGenerator: public ScenarioGeneratorBase{
 public:
  std::vector<Color32> Generate(int sideSize, float displacement=0) override;
  std::vector<Color32> Limiar(std::vector<Color32> colors, int size);
  std::vector<Color32> Fault(std::vector<Color32> colors, int size, int depth);
  Color32 gradient(Color32 color1, Color32 color2, float f);
  std::string GetName() override;
};

#endif  // MOBAGEN_RANDOMSCENARIOGENERATOR_H
