cmake_minimum_required(VERSION 3.0)
project(graphEditor)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the SDL2 library
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

# Set the C++ standard to C++17
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
