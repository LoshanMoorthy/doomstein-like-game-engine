#pragma once

#include "../../include/SDL2/SDL.h"
#include "vector2.h"

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

/* Typdefs */

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef size_t   usize;
typedef ssize_t  isize;

/* Constants */

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
#define MAP_SIZE 8

/* Structs */ 

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool quit;

    v2 pos, dir, plane;
} State;


void verline(State *state, int x, int y0, int y1, u32 color);
void render(State *state);
void rot(State *state, f32 rot);
void load_wall_texture(SDL_Renderer* renderer);

