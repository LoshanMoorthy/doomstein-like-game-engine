SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) # Add all source files in src directory
SRC_FILES += src/engine/raycaster.c       # Add the file containing render and rot functions
OBJ_NAME = main
INCLUDE_PATHS = -Iinclude
COMPILER_FLAGS = -std=c11 -Wall -O0 -g
LINKER_FLAGS = -lSDL2

# Set the library path explicitly
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.28.5/lib

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)


