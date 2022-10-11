#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher: public Agent {
 public:
    explicit Catcher():Agent(){};
    Point2D Move(World*) override;

    std::vector<Point2D> returnNeighbors(Point2D pos);
    bool neighborExists(std::vector<Point2D> list, Point2D pos);
};

#endif  // CATCHER_H
