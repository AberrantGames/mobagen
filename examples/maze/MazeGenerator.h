#ifndef MOBAGEN_MAZEGENERATOR_H
#define MOBAGEN_MAZEGENERATOR_H

#include "MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>

// please do not use this one anymore. Move your code to the specific implementation.
// I am going to rename this interface soon to be a naive implementation.
class MazeGenerator: public MazeGeneratorBase {
 public:
  std::string GetName() override {return "deprecated";};
  // todo: in order to step work properly, you have to store your current exploration status in the MazeGenerator members
  // Steps should return true if it made changes in the world
  bool Step(World* world) override;
  void Clear(World* world) override;

  Point2D randomPoint(World* world);
  std::vector<Point2D> getNeighbors(World* world, const Point2D& point);

  //list of points visited
  std::vector<Point2D> cells;
  //list for what is already visited
  std::map<int, std::map<int, bool>> visited;
  //bool for if the maze is blank or not
  bool isFirstStep = true;
};

#endif
