#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/SDL2/SDL.h"
#include "engine/assert.h"
#include "engine/utils.h"

struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    bool quit;
} state;

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
        SDL_RenderPresent(state.renderer);
    }

    SDL_DestroyTexture(state.texture);
    SDL_DestroyWindow(state.window);
    return 0;
}
