#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <deque>
#include "Point.h"
#include "Direction.h"

class Snake
{
    std::deque<Point> body;            // The segments of the snake's body
    Direction currentDirection;        // The current direction of the snake
    Direction nextDirection;           // The next direction the snake will move towards

public:
    // Constructor to initialize the snake's position
    Snake(Point startPos);

    // Set the snake's direction
    void setDirection(Direction dir);

    // Move the snake to a new head position
    void move(const Point& newHead);

    // Grow the snake by adding a new head segment
    void grow(const Point& newHead);

    // Update the snake's direction based on the next direction
    void updateDirection();

    // Get the position of the snake's next head
    Point getNextHeadPosition() const;

    // Check if moving to the new head position will cause the snake to collide with itself
    bool checkSelfCollision(const Point& newHead) const;

    // Get the current direction of the snake
    Direction getDirection() const { return currentDirection; }

    // Get the segments of the snake's body
    const std::deque<Point>& getBody() const { return body; }

    // Get the position of the snake's head
    Point getHead() const { return body.front(); }

    // Check if the snake's body contains a specific point
    bool contains(Point pos) const;
};

#endif // SNAKE_H
