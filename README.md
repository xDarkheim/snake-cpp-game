# 🐍 Snake Game

Classic Snake game implemented in C++ with a console interface.

## 📁 Project Structure
- `main.cpp` — Entry point
- `Game.*` — Game logic and rendering
- `Snake.*` — Snake class implementation
- `Food.*` — Food generation system
- `Point.h` — Coordinate structure
- `Direction.h` — Direction enumeration
- `best_score.txt` — High score storage
- `CMakeLists.txt` — Build configuration

## 🛠️ Requirements
- C++11 or higher
- CMake 3.10+
- Linux/Unix terminal

## 🎮 Features
- Console-based graphics
- WASD controls
- Food generation
- Collision detection
- Growing snake mechanics
- Score tracking
- Best score persistence

## 🎯 Controls
- W — Move up
- S — Move down
- A — Move left
- D — Move right
- Q — Quit game

## 📦 Build and Run
```bash
mkdir build && cd build
cmake ..
make
./Snake
```
