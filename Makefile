# Typing Race Game - Makefile with SDL2 support
#
# Usage:
#   make        -> builds the 'typing_race' executable
#   make clean  -> removes object files and binary
#
# This Makefile assumes you have SDL2 installed and that the command
#   sdl2-config
# exists on your system (common on macOS Homebrew and Linux).
# If it does not, your teacher or TA can adjust the SDL2_CFLAGS and SDL2_LIBS
# below to match your installation paths.

CC      = gcc
SRC_DIR = src
INC_DIR = include

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/game.c \
      $(SRC_DIR)/word_list.c \
      $(SRC_DIR)/timer.c \
      $(SRC_DIR)/input.c \
      $(SRC_DIR)/ui_sdl.c \
      $(SRC_DIR)/stats.c \
      $(SRC_DIR)/utils.c

OBJ = $(SRC:.c=.o)

TARGET = typing_race

# Try to use sdl2-config if available
SDL2_CFLAGS = $(shell sdl2-config --cflags 2>/dev/null)
SDL2_LIBS   = $(shell sdl2-config --libs 2>/dev/null)

# If sdl2-config is not found, you can manually set these, e.g.:
# SDL2_CFLAGS = -I/usr/local/include/SDL2 -D_THREAD_SAFE
# SDL2_LIBS   = -L/usr/local/lib -lSDL2

CFLAGS  = -Wall -Wextra -I$(INC_DIR) $(SDL2_CFLAGS)
LDFLAGS = $(SDL2_LIBS)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
