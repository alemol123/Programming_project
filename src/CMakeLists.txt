add_executable(programming_project
    main.c
    timer.c
    ui_sdl.c
    utils.c
    word_list.c
    game.c
    stats.c
    input.c 
)

find_package(SDL2 REQUIRED)
target_link_libraries(programming_project SDL2::SDL2
)



