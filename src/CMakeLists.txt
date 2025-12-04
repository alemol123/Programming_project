add_library(programming_project_lib
    game.c
    input.c
    stats.c
    timer.c
    ui_sdl.c
    utils.c
    word_list.c
  )
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(programming_project_lib PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
add_executable(programming_project main.c)
target_link_libraries(programming_project PRIVATE programming_project_lib)
