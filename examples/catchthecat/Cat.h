#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat: public Agent {
public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;

    std::vector<Point2D> returnNeighbors(Point2D pos);
    bool neighborExists(std::vector<Point2D> list, Point2D pos);
};

#endif  // CAT_H
