cmake_minimum_required(VERSION 3.0)

# Download and configure Hunter
#include("cmake/HunterGate.cmake")
#HunterGate(
#    URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
#    SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
#)

project(graphEditor VERSION 1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use Hunter to download the SDL2 library
#hunter_add_package(SDL2)
#find_package(SDL2 CONFIG REQUIRED)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

#set(SDL2_PATH "D:\Downloads\SDL2-devel-2.26.4-VC")
#set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
#set(SDL2_LIBRARY "${SDL2_PATH}/lib/x64/SDL2.lib")

# Link the SDL2 library
find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

# Set the installation directory
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
