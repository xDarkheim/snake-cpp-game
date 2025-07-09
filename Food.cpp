#include "Food.h"
#include <random>
#include <algorithm>

void Food::generateNew(int maxX, int maxY, const std::vector<Point>& occupiedPositions)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> disX(0, maxX - 1);
    std::uniform_int_distribution<> disY(0, maxY - 1);

    Point newPos;
    do
    {
        newPos = Point(disX(gen), disY(gen));
    } while (std::find(occupiedPositions.begin(), occupiedPositions.end(), newPos) != occupiedPositions.end());

    position = newPos;
}
