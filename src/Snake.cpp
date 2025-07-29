#include "Snake.h"

// Constructor
Snake::Snake(Point startPos)
    : currentDirection(Direction::RIGHT), nextDirection(Direction::RIGHT)
{
    body.push_back(startPos);
}

// Set the movement direction
void Snake::setDirection(Direction dir)
{
    if ((currentDirection == Direction::UP && dir == Direction::DOWN) ||
        (currentDirection == Direction::DOWN && dir == Direction::UP) ||
        (currentDirection == Direction::LEFT && dir == Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && dir == Direction::LEFT))
        return;
    nextDirection = dir;
}

// Check if the snake's body contains the point pos
bool Snake::contains(Point pos) const
{
    for (const Point& segment : body)
        if (segment == pos)
            return true;
    return false;
}

// Move the snake (without growing)
void Snake::move(const Point& newHead)
{
    body.push_front(newHead);
    body.pop_back();
}

// Grow the snake (add a head)
void Snake::grow(const Point& newHead)
{
    body.push_front(newHead);
}

// Update the current direction
void Snake::updateDirection()
{
    currentDirection = nextDirection;
}

// Get the next head position
Point Snake::getNextHeadPosition() const
{
    Point head = body.front();
    switch (currentDirection)
    {
        case Direction::UP:    return Point(head.x, head.y - 1);
        case Direction::DOWN:  return Point(head.x, head.y + 1);
        case Direction::LEFT:  return Point(head.x - 1, head.y);
        case Direction::RIGHT: return Point(head.x + 1, head.y);
        default:               return head;
    }
}

// Check for self-collision
bool Snake::checkSelfCollision(const Point& newHead) const
{
    for (const Point& segment : body)
        if (newHead == segment)
            return true;
    return false;
}
