Typing Race Game 
================================

This repository is a *skeleton* C project for a Typing Race game using SDL2.

To build (if SDL2 and sdl2-config are installed):

    cd ~/Programming_project
    rm -rf build
    mkdir build
    cd build
    cmake ..
    cmake --build .


Run the program:

    ./build/src/programming_project

At the moment, the .c files only contain skeleton comments and no logic.
We will implement the game in the src/ files.

SDL2 note:
- On macOS with Homebrew you may need to install SDL2 via:
    brew install sdl2
