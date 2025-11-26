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

target_link_libraries(programming_project
    /opt/homebrew/opt/sdl2/lib/libSDL2.dylib
    /opt/homebrew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib

)



