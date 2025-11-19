cmake_minimum_required(VERSION 3.10)

project(TypingRace C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Source and include directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INC_DIR})

file(GLOB SRC_FILES
    ${SRC_DIR}/*.c
)

# Find SDL2
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    message(STATUS "Found SDL2: ${SDL2_INCLUDE_DIRS}")
    include_directories(${SDL2_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "SDL2 not found. Please install SDL2 development files.")
endif()

add_executable(typing_race ${SRC_FILES})

target_link_libraries(typing_race ${SDL2_LIBRARIES})
