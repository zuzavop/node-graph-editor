# CMakeList.txt: Projekt CMake pro graphEditor, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("graphEditor"  VERSION 1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/../src/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/../headers")

find_package(SDL2 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/../SDL2")
include_directories(${SDL2_INCLUDE_DIRS})

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

file(GLOB PROJECT_DEPENDENCIES "${SDL2_DIR}/../lib/x64/*.dll")

foreach(Dependency IN LISTS PROJECT_DEPENDENCIES)
    file(
        COPY ${Dependency}
        DESTINATION ${CMAKE_BINARY_DIR}
    )
endforeach()

file(
    COPY "${CMAKE_SOURCE_DIR}/../assets"
    DESTINATION ${CMAKE_BINARY_DIR}
)
