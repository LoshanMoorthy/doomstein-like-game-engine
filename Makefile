SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += src/engine/raycaster.c
OBJ_NAME = main
INCLUDE_PATHS = -Iinclude -I../../include/SDL2_image
COMPILER_FLAGS = -std=c11 -Wall -O0 -g
LINKER_FLAGS = -lSDL2 -lSDL2_image

LIBRARY_PATHS = -L/opt/homebrew/Cellar/sdl2/2.28.5/lib -Llib

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)



