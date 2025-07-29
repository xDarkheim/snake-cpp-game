#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include "Direction.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

class Game
{
    Snake snake;
    Food food;
    int score;
    int bestScore;
    bool gameOver;
    bool paused;
    bool inMenu;

    // Menu button struct
    struct MenuButton {
        sf::FloatRect rect;
        std::string label;
        sf::Color color;
        sf::Color hoverColor;
        bool hovered = false;
    };

    void generateFood();
    Point getTeleportedHead() const;
    void loadBestScore();
    void saveBestScore();
    void reset();

public:
    static const int BOARD_WIDTH = 20;
    static const int BOARD_HEIGHT = 20;
    static const int CELL_SIZE = 24;
    static constexpr const char* BEST_SCORE_FILE = "best_score.txt";

    Game();

    void run();
    void processEvent(const sf::Event& event,
                     sf::RenderWindow* window = nullptr,
                     MenuButton* startBtn = nullptr,
                     MenuButton* exitBtn = nullptr,
                     MenuButton* restartBtn = nullptr,
                     MenuButton* menuBtn = nullptr);
    void update();
    void render(sf::RenderWindow& window,
                MenuButton* startBtn = nullptr,
                MenuButton* exitBtn = nullptr,
                MenuButton* restartBtn = nullptr,
                MenuButton* menuBtn = nullptr) const;

    bool isGameOver() const { return gameOver; }
    int getScore() const { return score; }
    int getBestScore() const { return bestScore; }
};

#endif //GAME_H
