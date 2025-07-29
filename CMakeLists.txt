cmake_minimum_required(VERSION 3.10)
project(Snake VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.c"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets to build directory
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()

# Install rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    install(DIRECTORY assets DESTINATION share/${PROJECT_NAME})
endif()
