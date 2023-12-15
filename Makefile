SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += src/engine/raycaster.c
OBJ_NAME = main

INCLUDE_PATHS = -Iinclude -F/Library/Frameworks -I/Library/Frameworks/SDL2_image.framework/Headers

COMPILER_FLAGS = -std=c11 -Wall -O0 -g

LINKER_FLAGS = -lSDL2 -framework SDL2_image -Wl,-rpath,/Library/Frameworks

LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.28.5/lib -Llib

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)




