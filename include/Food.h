#ifndef FOOD_H
#define FOOD_H

#include "Point.h"
#include <vector>

class Food
{
    Point position;

public:
    Food() : position(0, 0) {}

    void generateNew(int maxX, int maxY, const std::vector<Point>& occupiedPositions);
    Point getPosition() const { return position; }
};
#endif //FOOD_H
