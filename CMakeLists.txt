cmake_minimum_required(VERSION 3.0)

project(graphEditor VERSION 1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Add header files
include_directories(headers)
include_directories(SDL2/include)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against the SDL2 library
target_link_libraries(${PROJECT_NAME} SDL2)

# Set the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
