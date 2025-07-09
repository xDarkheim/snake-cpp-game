#include "Game.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

Game::Game()
    : snake(Point(BOARD_WIDTH / 2, BOARD_HEIGHT / 2)),
      score(0),
      bestScore(0),
      gameOver(false),
      paused(false),
      inMenu(true)
{
    loadBestScore();
    generateFood();
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE + 60), "Snake Game");
    sf::Clock clock;
    float timer = 0.0f, delay = 0.15f;

    // Menu buttons initialization
    MenuButton startBtn, exitBtn, restartBtn, menuBtn;
    startBtn.rect = sf::FloatRect(CELL_SIZE * BOARD_WIDTH / 2 - 110, 180, 220, 48);
    startBtn.label = "Start";
    startBtn.color = sf::Color(80, 180, 80);
    startBtn.hoverColor = sf::Color(120, 220, 120);

    exitBtn.rect = sf::FloatRect(BOARD_WIDTH * CELL_SIZE / 2 - 110, 250, 220, 40);
    exitBtn.label = "Exit";
    exitBtn.color = sf::Color(180, 80, 80);
    exitBtn.hoverColor = sf::Color(220, 120, 120);

    restartBtn.rect = sf::FloatRect(BOARD_WIDTH * CELL_SIZE / 2 - 110, 180, 220, 48);
    restartBtn.label = "Restart";
    restartBtn.color = sf::Color(80, 180, 80);
    restartBtn.hoverColor = sf::Color(120, 220, 120);

    menuBtn.rect = sf::FloatRect(BOARD_WIDTH * CELL_SIZE / 2 - 110, 250, 220, 40);
    menuBtn.label = "Menu";
    menuBtn.color = sf::Color(180, 80, 80);
    menuBtn.hoverColor = sf::Color(220, 120, 120);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            processEvent(event, &window, &startBtn, &exitBtn, &restartBtn, &menuBtn);
        }

        if (!paused && !gameOver && !inMenu)
        {
            timer += clock.restart().asSeconds();
            if (timer > delay)
            {
                update();
                timer = 0;
            }
        }
        else
        {
            clock.restart();
        }

        render(window, &startBtn, &exitBtn, &restartBtn, &menuBtn);
    }
}

// Handles all events, including mouse support for menu buttons
void Game::processEvent(const sf::Event& event, sf::RenderWindow* window,
                        MenuButton* startBtn, MenuButton* exitBtn,
                        MenuButton* restartBtn, MenuButton* menuBtn)
{
    sf::Vector2f mousePos;
    if (window)
        mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    // Reset hover state for all buttons
    if (startBtn) startBtn->hovered = false;
    if (exitBtn) exitBtn->hovered = false;
    if (restartBtn) restartBtn->hovered = false;
    if (menuBtn) menuBtn->hovered = false;

    if (inMenu)
    {
        if (startBtn && startBtn->rect.contains(mousePos))
            startBtn->hovered = true;
        if (exitBtn && exitBtn->rect.contains(mousePos))
            exitBtn->hovered = true;

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (startBtn && startBtn->rect.contains(mousePos))
            {
                inMenu = false;
                gameOver = false;
                paused = false;
                reset();
                return;
            }
            if (exitBtn && exitBtn->rect.contains(mousePos))
            {
                if (window) window->close();
                return;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                inMenu = false;
                gameOver = false;
                paused = false;
                reset();
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                if (window) window->close();
            }
        }
        return;
    }

    if (gameOver)
    {
        if (restartBtn && restartBtn->rect.contains(mousePos))
            restartBtn->hovered = true;
        if (menuBtn && menuBtn->rect.contains(mousePos))
            menuBtn->hovered = true;

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (restartBtn && restartBtn->rect.contains(mousePos))
            {
                reset();
                gameOver = false;
                paused = false;
                inMenu = false;
                return;
            }
            if (menuBtn && menuBtn->rect.contains(mousePos))
            {
                inMenu = true;
                return;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                reset();
                gameOver = false;
                paused = false;
                inMenu = false;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                inMenu = true;
            }
        }
        return;
    }

    // Snake controls
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                if (snake.getDirection() != Direction::DOWN)
                    snake.setDirection(Direction::UP);
                paused = false;
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                if (snake.getDirection() != Direction::UP)
                    snake.setDirection(Direction::DOWN);
                paused = false;
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                if (snake.getDirection() != Direction::RIGHT)
                    snake.setDirection(Direction::LEFT);
                paused = false;
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                if (snake.getDirection() != Direction::LEFT)
                    snake.setDirection(Direction::RIGHT);
                paused = false;
                break;
            case sf::Keyboard::Space:
                paused = !paused;
                break;
            case sf::Keyboard::Q:
            case sf::Keyboard::Escape:
                inMenu = true;
                break;
            default:
                break;
        }
    }
}

// Rendering with interactive menu buttons and centered text
void Game::render(sf::RenderWindow& window,
                  MenuButton* startBtn, MenuButton* exitBtn,
                  MenuButton* restartBtn, MenuButton* menuBtn)
{
    // Draw gradient background
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(window.getSize().x, 0);
    background[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    background[3].position = sf::Vector2f(0, window.getSize().y);
    background[0].color = sf::Color(40, 40, 60);
    background[1].color = sf::Color(40, 40, 60);
    background[2].color = sf::Color(20, 20, 30);
    background[3].color = sf::Color(20, 20, 30);
    window.draw(background);

    // Draw game border
    sf::RectangleShape border(sf::Vector2f(BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE));
    border.setPosition(0, 0);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(3);
    border.setOutlineColor(sf::Color(180, 180, 220));
    window.draw(border);

    // Draw food with highlight
    sf::CircleShape foodCircle(CELL_SIZE / 2 - 3);
    foodCircle.setFillColor(sf::Color(255, 80, 80));
    foodCircle.setOutlineThickness(2);
    foodCircle.setOutlineColor(sf::Color(255, 180, 180));
    foodCircle.setOrigin(foodCircle.getRadius(), foodCircle.getRadius());
    foodCircle.setPosition(food.getPosition().x * CELL_SIZE + CELL_SIZE / 2, food.getPosition().y * CELL_SIZE + CELL_SIZE / 2);
    window.draw(foodCircle);

    // Draw snake
    for (const auto& segment : snake.getBody())
    {
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
        cell.setPosition(segment.x * CELL_SIZE + 2, segment.y * CELL_SIZE + 2);
        if (segment == snake.getHead()) {
            cell.setFillColor(sf::Color(80, 255, 80));
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color(40, 180, 40));
        } else {
            cell.setFillColor(sf::Color(100, 200, 100));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(60, 120, 60));
        }
        window.draw(cell);
    }

    // Helper for drawing shadowed text
    auto drawShadowedText = [&](sf::RenderTarget& target, const sf::Text& text, sf::Color shadowColor = sf::Color(0,0,0,120), float offset = 2.f) {
        sf::Text shadow = text;
        shadow.setFillColor(shadowColor);
        shadow.move(offset, offset);
        target.draw(shadow);
        target.draw(text);
    };

    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    if (fontLoaded)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(22);
        text.setFillColor(sf::Color::White);

        if (inMenu)
        {
            // Title
            text.setString("SNAKE GAME");
            text.setCharacterSize(38);
            text.setStyle(sf::Text::Bold);
            sf::FloatRect titleRect = text.getLocalBounds();
            text.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
            text.setPosition(BOARD_WIDTH * CELL_SIZE / 2.0f, 80);
            drawShadowedText(window, text);

            // Best score
            text.setString("Best score: " + std::to_string(bestScore));
            text.setCharacterSize(22);
            text.setStyle(sf::Text::Regular);
            sf::FloatRect bestRect = text.getLocalBounds();
            text.setOrigin(bestRect.left + bestRect.width / 2.0f, bestRect.top + bestRect.height / 2.0f);
            text.setPosition(BOARD_WIDTH * CELL_SIZE / 2.0f, 130);
            drawShadowedText(window, text);

            // Start button
            sf::RectangleShape startShape(sf::Vector2f(startBtn->rect.width, startBtn->rect.height));
            startShape.setPosition(startBtn->rect.left, startBtn->rect.top);
            startShape.setFillColor(startBtn->hovered ? startBtn->hoverColor : startBtn->color);
            startShape.setOutlineThickness(3);
            startShape.setOutlineColor(sf::Color(40, 120, 40));
            window.draw(startShape);

            text.setString("Start");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            sf::FloatRect startTextRect = text.getLocalBounds();
            text.setOrigin(startTextRect.left + startTextRect.width / 2.0f, startTextRect.top + startTextRect.height / 2.0f);
            text.setPosition(
                startBtn->rect.left + startBtn->rect.width / 2.0f,
                startBtn->rect.top + startBtn->rect.height / 2.0f
            );
            drawShadowedText(window, text);

            // Exit button
            sf::RectangleShape exitShape(sf::Vector2f(exitBtn->rect.width, exitBtn->rect.height));
            exitShape.setPosition(exitBtn->rect.left, exitBtn->rect.top);
            exitShape.setFillColor(exitBtn->hovered ? exitBtn->hoverColor : exitBtn->color);
            exitShape.setOutlineThickness(3);
            exitShape.setOutlineColor(sf::Color(120, 40, 40));
            window.draw(exitShape);

            text.setString("Exit");
            text.setCharacterSize(22);
            text.setFillColor(sf::Color::White);
            sf::FloatRect exitTextRect = text.getLocalBounds();
            text.setOrigin(exitTextRect.left + exitTextRect.width / 2.0f, exitTextRect.top + exitTextRect.height / 2.0f);
            text.setPosition(
                exitBtn->rect.left + exitBtn->rect.width / 2.0f,
                exitBtn->rect.top + exitBtn->rect.height / 2.0f
            );
            drawShadowedText(window, text);
        }
        else if (gameOver)
        {
            // Game Over title
            text.setString("GAME OVER");
            text.setCharacterSize(38);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color(255, 80, 80));
            sf::FloatRect overRect = text.getLocalBounds();
            text.setOrigin(overRect.left + overRect.width / 2.0f, overRect.top + overRect.height / 2.0f);
            text.setPosition(BOARD_WIDTH * CELL_SIZE / 2.0f, 80);
            drawShadowedText(window, text, sf::Color(0,0,0,180), 3.f);

            // Score info
            text.setString("Score: " + std::to_string(score) + "   Best: " + std::to_string(bestScore));
            text.setCharacterSize(22);
            text.setStyle(sf::Text::Regular);
            text.setFillColor(sf::Color::White);
            sf::FloatRect scoreRect = text.getLocalBounds();
            text.setOrigin(scoreRect.left + scoreRect.width / 2.0f, scoreRect.top + scoreRect.height / 2.0f);
            text.setPosition(BOARD_WIDTH * CELL_SIZE / 2.0f, 130);
            drawShadowedText(window, text);

            // Restart button
            sf::RectangleShape restartShape(sf::Vector2f(restartBtn->rect.width, restartBtn->rect.height));
            restartShape.setPosition(restartBtn->rect.left, restartBtn->rect.top);
            restartShape.setFillColor(restartBtn->hovered ? restartBtn->hoverColor : restartBtn->color);
            restartShape.setOutlineThickness(3);
            restartShape.setOutlineColor(sf::Color(40, 120, 40));
            window.draw(restartShape);

            text.setString("Restart");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            sf::FloatRect restartTextRect = text.getLocalBounds();
            text.setOrigin(restartTextRect.left + restartTextRect.width / 2.0f, restartTextRect.top + restartTextRect.height / 2.0f);
            text.setPosition(
                restartBtn->rect.left + restartBtn->rect.width / 2.0f,
                restartBtn->rect.top + restartBtn->rect.height / 2.0f
            );
            drawShadowedText(window, text);

            // Menu button
            sf::RectangleShape menuShape(sf::Vector2f(menuBtn->rect.width, menuBtn->rect.height));
            menuShape.setPosition(menuBtn->rect.left, menuBtn->rect.top);
            menuShape.setFillColor(menuBtn->hovered ? menuBtn->hoverColor : menuBtn->color);
            menuShape.setOutlineThickness(3);
            menuShape.setOutlineColor(sf::Color(120, 40, 40));
            window.draw(menuShape);

            text.setString("Menu");
            text.setCharacterSize(22);
            text.setFillColor(sf::Color::White);
            sf::FloatRect menuTextRect = text.getLocalBounds();
            text.setOrigin(menuTextRect.left + menuTextRect.width / 2.0f, menuTextRect.top + menuTextRect.height / 2.0f);
            text.setPosition(
                menuBtn->rect.left + menuBtn->rect.width / 2.0f,
                menuBtn->rect.top + menuBtn->rect.height / 2.0f
            );
            drawShadowedText(window, text);
        }
        else
        {
            // Score bar
            text.setString("Score: " + std::to_string(score) + "   Best: " + std::to_string(bestScore) +
                           (paused ? "   [PAUSED]" : ""));
            text.setCharacterSize(22);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Regular);
            text.setPosition(5, BOARD_HEIGHT * CELL_SIZE + 8);
            drawShadowedText(window, text);

            // Controls
            text.setString("WASD / Arrows - Move   SPACE - Pause   ESC - Menu");
            text.setCharacterSize(16);
            text.setFillColor(sf::Color(180, 180, 220));
            text.setPosition(5, BOARD_HEIGHT * CELL_SIZE + 36);
            drawShadowedText(window, text, sf::Color(0,0,0,100), 1.5f);
        }
    }

    window.display();
}

void Game::update()
{
    snake.updateDirection();
    Point newHead = getTeleportedHead();

    if (snake.checkSelfCollision(newHead))
    {
        gameOver = true;
        if (score > bestScore)
        {
            bestScore = score;
            saveBestScore();
        }
        return;
    }

    if (newHead == food.getPosition())
    {
        snake.grow(newHead);
        score += 10;
        generateFood();
    }
    else
    {
        snake.move(newHead);
    }
}

Point Game::getTeleportedHead() const
{
    Point newHead = snake.getNextHeadPosition();
    if (newHead.x < 0) newHead.x = BOARD_WIDTH - 1;
    else if (newHead.x >= BOARD_WIDTH) newHead.x = 0;
    if (newHead.y < 0) newHead.y = BOARD_HEIGHT - 1;
    else if (newHead.y >= BOARD_HEIGHT) newHead.y = 0;
    return newHead;
}

void Game::generateFood()
{
    std::vector<Point> occupiedPositions(snake.getBody().begin(), snake.getBody().end());
    food.generateNew(BOARD_WIDTH, BOARD_HEIGHT, occupiedPositions);
}

void Game::loadBestScore()
{
    std::ifstream in(BEST_SCORE_FILE);
    if (in)
        in >> bestScore;
    else
        bestScore = 0;
}

void Game::saveBestScore()
{
    std::ofstream out(BEST_SCORE_FILE);
    if (out)
        out << bestScore;
}

void Game::reset()
{
    snake = Snake(Point(BOARD_WIDTH / 2, BOARD_HEIGHT / 2));
    score = 0;
    generateFood();
}
