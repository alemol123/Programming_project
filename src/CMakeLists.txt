# CMake configuration inside src/ for building the typing game

# List of source files (excluding main.c for library)
set(SOURCES
    game.c
    timer.c
    stats.c
    input.c
    utils.c
    ui_sdl.c
    word_list.c
)

# Create a library of core game logic (no SDL window)
add_library(programming_project_lib ${SOURCES})

target_include_directories(programming_project_lib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Create the executable (game)
add_executable(programming_project main.c)

target_include_directories(programming_project
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find pthreads
find_package(Threads REQUIRED)

# Include SDL2 headers
target_include_directories(programming_project
    PRIVATE
        $ENV{CONDA_PREFIX}/include/SDL2
)

# Link directories
target_link_directories(programming_project
    PRIVATE
        $ENV{CONDA_PREFIX}/lib
)

# Link SDL + pthreads
target_link_libraries(programming_project
    programming_project_lib
    SDL2::SDL2
    SDL2_ttf
    Threads::Threads
)

# Use C11
set_target_properties(programming_project PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
)
