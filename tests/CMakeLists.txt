# CMake configuration for unit tests

# Make sure SDL2 & pthreads targets exist in this directory
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

# We assume:
# - include_directories(${PROJECT_SOURCE_DIR}/include) was already called
#   in the top-level CMakeLists.txt
# - programming_project_lib is defined in src/CMakeLists.txt

# ---- test_words -----------------------------

add_executable(test_words
    test_words.c
)

target_link_directories(test_words
    PRIVATE
        $ENV{CONDA_PREFIX}/lib
)

target_link_libraries(test_words
    programming_project_lib
    SDL2::SDL2
    SDL2_ttf
    Threads::Threads
)

add_test(NAME test_words COMMAND test_words)

# ---- test_game_logic ------------------------

add_executable(test_game_logic
    test_game_logic.c
)

target_link_directories(test_game_logic
    PRIVATE
        $ENV{CONDA_PREFIX}/lib
)

target_link_libraries(test_game_logic
    programming_project_lib
    SDL2::SDL2
    SDL2_ttf
    Threads::Threads
)

add_test(NAME test_game_logic COMMAND test_game_logic)

# ---- test_stats -----------------------------

add_executable(test_stats
    test_stats.c
)

target_link_directories(test_stats
    PRIVATE
        $ENV{CONDA_PREFIX}/lib
)

target_link_libraries(test_stats
    programming_project_lib
    SDL2::SDL2
    SDL2_ttf
    Threads::Threads
)

add_test(NAME test_stats COMMAND test_stats)

# ---- test_timer -----------------------------

add_executable(test_timer
    test_timer.c
)

target_link_directories(test_timer
    PRIVATE
        $ENV{CONDA_PREFIX}/lib
)

target_link_libraries(test_timer
    programming_project_lib
    SDL2::SDL2
    SDL2_ttf
    Threads::Threads
)

add_test(NAME test_timer COMMAND test_timer)



