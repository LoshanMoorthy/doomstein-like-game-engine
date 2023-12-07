#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/SDL2/SDL.h"
#include "engine/assert.h"
#include "engine/utils.h"
#include "engine/raycaster.h"

#define normalize(u) ({              \
        const v2 _u = (u);           \
        const f32 l = length(_u);    \
        (v2) { _u.x / l, _u.y / l }; \
    })
#define length(v) ({ const v2 _v = (v); sqrtf(dot(_v, _v)); })
#define dot(v0, v1)                  \
    ({ const v2 _v0 = (v0), _v1 = (v1); (_v0.x * _v1.x) + (_v0.y * _v1.y); })

int main(int argc, char* argv[]) {

    State state;

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
        "Failed to create SDL renderer: %s\n", 
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
    ASSERT(
        state.texture,
        "Failed to create SDL texture: %s\n", SDL_GetError()
    );

    state.pos = (v2) { 2, 2 };
    state.dir = normalize(((v2) { -1.0f, 0.1f }));
    state.plane = (v2) { 0.0f, 0.66f };

    while (!state.quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    state.quit = true;
                    break;
            }
        }

        const f32
            rot_speed = 3.0f * 0.016f,
            move_speed = 3.0f * 0.016;

        Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_LEFT])
            rot(&state, +rot_speed);
        if (keystate[SDL_SCANCODE_RIGHT])
            rot(&state, -rot_speed);
        if (keystate[SDL_SCANCODE_UP]) {
            state.pos.x += state.dir.x * move_speed;
            state.pos.y += state.dir.y * move_speed;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            state.pos.x -= state.dir.x * move_speed;
            state.pos.y -= state.dir.y * move_speed;
        }
        
        memset(state.pixels, 0, sizeof(state.pixels));
        render(&state);

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
    
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyTexture(state.texture);
    SDL_DestroyWindow(state.window);
    return 0;
}
