#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // Game board dimensions
    constexpr int BOARD_WIDTH = 20;
    constexpr int BOARD_HEIGHT = 20;
    constexpr int CELL_SIZE = 24;

    // Window settings
    constexpr int WINDOW_WIDTH = BOARD_WIDTH * CELL_SIZE;
    constexpr int WINDOW_HEIGHT = BOARD_HEIGHT * CELL_SIZE + 100; // Extra space for UI

    // Game timing
    constexpr float INITIAL_SPEED = 0.2f; // Seconds between moves
    constexpr float SPEED_INCREMENT = 0.01f;
    constexpr float MIN_SPEED = 0.05f;

    // Colors (RGBA)
    constexpr unsigned int BACKGROUND_COLOR = 0x000000FF; // Black
    constexpr unsigned int SNAKE_COLOR = 0x00FF00FF;      // Green
    constexpr unsigned int FOOD_COLOR = 0xFF0000FF;       // Red
    constexpr unsigned int BORDER_COLOR = 0xFFFFFFFF;     // White

    // File paths
    constexpr const char* BEST_SCORE_FILE = "best_score.txt";
    constexpr const char* WINDOW_TITLE = "Snake Game";
}

#endif // CONFIG_H
