cmake_minimum_required(VERSION 3.0)
project(graphEditor)

# Download and configure Hunter
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.252.tar.gz"
    SHA1 "a92dabf5a5a8e5c9b67ebb0a7b46d45c8f61e96b"
)

# Use Hunter to download the SDL2 library
hunter_add_package(SDL2)
find_package(SDL2 CONFIG REQUIRED)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the SDL2 library
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

# Set the C++ standard to C++17
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
