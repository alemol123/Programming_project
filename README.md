Typing Race Game 
================================

This repository is a *skeleton* C project for a Typing Race game using SDL2.

Prerequisites
================================
Install the dependencies using conda:

    conda env create -f environment.yml
    
This will create an environment called project which you can activate with: 

    conda activate project

If you do not have Conda installed, you can get it from:
https://github.com/conda-forge/miniforge

You must activate the environment each time you open a new terminal.

To build (if SDL2 and sdl2-config are installed):

    cd ~/Programming_project
    rm -rf build
    mkdir build
    cd build
    cmake ..
    cmake --build .

Run the tests: 
    ./tests/test_words
    ./tests/test_stats
    ./tests/test_timer
    ./tests/test_game_logic

Run the program:

    ./build/src/programming_project


At the moment, the .c files only contain skeleton comments and no logic.
We will implement the game in the src/ files.

SDL2 note:
- On macOS with Homebrew you may need to install SDL2 via:
    brew install sdl2
