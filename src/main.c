#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/SDL2/SDL.h"
#include "engine/assert.h"
#include "engine/utils.h"

/*
* Each number represents a specific tile or elem in map 
* 1 represents wall tiles or bound
* 0 represents empty space
* 2, 3, 4 represents specific obj or elemt
*/
static u8 MAPDATA[8 * 8] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 3, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 4, 4, 0, 1,
    1, 0, 0, 0, 4, 0, 0, 1,
    1, 0, 3, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool quit;

    v2 pos, dir, plane;
} state;

static void verline(int x, int y0, int y1, u32 color) {
    for (int y = y0; y < y1; y++) {
        state.pixels[(y * SCREEN_WIDTH) + x] = color;
    }
}

void render() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        const f32 xcam = (2 * (x / (f32) (SCREEN_WIDTH))) - 1;

        const v2 dir = {
            state.dir.x + state.plane.x * xcam,
            state.dir.y + state.plane.y * xcam
        };

        v2 pos = state.pos;
        v2i ipos = { (int) pos.x, (int) pos.y };
        
        const v2 deltadist = {
            fabsf(dir.x) < 1e-20 ? 1e30 : fabsf(1.0f / dir.x),
            fabsf(dir.y) < 1e-20 ? 1e30 : fabsf(1.0f / dir.y),
        };

        v2 sidedist = {
            deltadist.x * (dir.x < 0 ? (pos.x - ipos.x) : (ipos.x + 1 - pos.x)),
            deltadist.y * (dir.y < 0 ? (pos.y - ipos.y) : (ipos.y + 1 - pos.y)),
        };

        const v2i step = { (int) sign(dir.x), (int) sign(dir.y) };


    }
}

int main(int argc, char* argv[]) {
    ASSERT(
        !SDL_Init(SDL_INIT_VIDEO),
        "SDL failed to initialize: %s\n",
        SDL_GetError()
    );

    state.window = 
        SDL_CreateWindow(
            "DEMO",
            SDL_WINDOWPOS_CENTERED_DISPLAY(1),
            SDL_WINDOWPOS_CENTERED_DISPLAY(1),
            1280,
            720,
            SDL_WINDOW_ALLOW_HIGHDPI
        );

    ASSERT(
        state.window, 
        "Failed to create SDL window: %s\n", 
        SDL_GetError()
    );
    
    state.renderer = 
        SDL_CreateRenderer(
            state.window,
            -1,
            SDL_RENDERER_PRESENTVSYNC
        );
    ASSERT(
        state.renderer,
        "Failed to create SDL window: %s\n", 
        SDL_GetError()
    );

    state.texture = 
        SDL_CreateTexture(
            state.renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        );

    while (!state.quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    state.quit = true;
                    break;
            }
        }
        
        state.pixels[(10 * SCREEN_WIDTH) + 5] = 0xFFFF00FF;

        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
        SDL_RenderCopyEx(
            state.renderer,
            state.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL
        );
        SDL_RenderPresent(state.renderer);
    }

    SDL_DestroyTexture(state.texture);
    SDL_DestroyWindow(state.window);
    return 0;
}
