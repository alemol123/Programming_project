# test for game logic
add_executable(test_game_logic test_game_logic.c)
target_include_directories(test_game_logic PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_game_logic PRIVATE programming_project_lib)
add_test(NAME test_game_logic COMMAND test_game_logic)

# test for stats
add_executable(test_stats test_stats.c)
target_include_directories(test_stats PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_stats PRIVATE programming_project_lib)
add_test(NAME test_stats COMMAND test_stats)

# test for timer
add_executable(test_timer test_timer.c)
target_include_directories(test_timer PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_timer PRIVATE programming_project_lib)
add_test(NAME test_timer COMMAND test_timer)

# test for words
add_executable(test_words test_words.c)
target_include_directories(test_words PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_words PRIVATE programming_project_lib)
add_test(NAME test_words COMMAND test_words)
