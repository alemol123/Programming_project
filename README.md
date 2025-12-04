Typing Race Game 
================================

This repository is a C project for a Typing Race game using SDL2.

Prerequisites
================================
Install the dependencies using conda:

    conda env create -f environment.yml
    
This will create an environment called project which you can activate with: 

    conda activate project

If you do not have Conda installed, you can get it from:
https://github.com/conda-forge/miniforge

You must activate the environment each time you open a new terminal.

Build and Run 
================================
To build:

    mkdir build
    cd build
    cmake ..
    cmake --build .

Run the tests: 

    cd build
    ctest

Run the program:

    ./build/src/programming_project


