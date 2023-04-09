cmake_minimum_required(VERSION 3.21)

project(graphEditor VERSION 1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

# Add the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(headers)


# Find the SDL2 library
if (UNIX)
    find_package(SDL2 REQUIRED)
elseif (WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2")
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
    set(SDL2_LIBRARY "${SDL2_DIR}/bin")
    set(SDL2_LIB_DIR "${SDL2_DIR}/lib")

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})
endif()

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

if (UNIX)
    # Link against the SDL2 library
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2)
    
    file(GLOB PROJECT_DEPENDENCIES ${SDL2_LIBRARY}/*.dll)
    foreach(Dependency IN LISTS PROJECT_DEPENDENCIES)
        file(
            COPY ${Dependency}
            DESTINATION ${OUTPUT_DIR}
        )
    endforeach()
endif()

file(
    COPY assets
    DESTINATION ${OUTPUT_DIR}
)

# Set the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
