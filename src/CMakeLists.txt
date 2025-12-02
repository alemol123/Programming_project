add_library(programming_project_lib
    game.c
    input.c
    stats.c
    timer.c
    ui_sdl.c
    utils.c
    word_list.c
)
add_executable(programming_project
    main.c
)
target_link_libraries(programming_project PRIVATE programming_project_lib)

target_link_libraries(programming_project_lib PRIVATE
    /opt/homebrew/opt/sdl2/lib/libSDL2.dylib
    /opt/homebrew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib

)