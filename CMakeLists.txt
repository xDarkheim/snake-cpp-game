cmake_minimum_required(VERSION 3.10)
project(Snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(Snake
        main.cpp
        Game.cpp
        Snake.cpp
        Food.cpp
)

# Include headers
target_include_directories(Snake PRIVATE .)

# Link SFML libraries
target_link_libraries(Snake sfml-graphics sfml-window sfml-system)
