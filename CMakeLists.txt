cmake_minimum_required(VERSION 3.10)
project(Programming_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/*.c"
)


include_directories(${INC_DIR})
# --- SDL2 setup ---
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h
  PATHS /opt/homebrew/include/SDL2 /usr/local/include/SDL2
)
find_library(SDL2_LIBRARY SDL2
  PATHS /opt/homebrew/lib /usr/local/lib
)
if (NOT SDL2_INCLUDE_DIR OR NOT SDL2_LIBRARY)
    message(FATAL_ERROR "SDL2 not found. Please install it with 'brew install sdl2'")
endif()

include_directories(${SDL2_INCLUDE_DIR})
message(STATUS "Using SDL2 include dir: ${SDL2_INCLUDE_DIR}")
message(STATUS "Using SDL2 library: ${SDL2_LIBRARY}")

# --- Define the executable target ---
add_executable(programming_project ${SRC_FILES})

# --- Link SDL2 library ---
target_link_libraries(programming_project ${SDL2_LIBRARY})
