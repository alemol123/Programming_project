cmake_minimum_required(VERSION 3.21)
project(programming_project C)

set(PROJECT_AUTHOR "Ale, Luna, Sanad")

# Windows does not support C23 yet
if(NOT MSVC)
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED True)
endif()
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)
enable_testing()
add_subdirectory(src)
