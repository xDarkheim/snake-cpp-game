#ifndef POINT_H
#define POINT_H

class Point
{
public:
    int x, y;

    explicit Point(int x = 0, int y = 0) : x(x), y(y){}

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

#endif //POINT_H
