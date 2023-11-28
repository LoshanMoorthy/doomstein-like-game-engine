#include "raycaster.h"
#include "utils.h"
#include "assert.h"

#include <math.h>

#define v2_to_v2i(_v) ({ __typeof__(_v) __v = (_v); (v2i) { __v.x, __v.y }; })
#define v2i_to_v2(_v) ({ __typeof__(_v) __v = (_v); (v2) { __v.x, __v.y }; })


#define min(a, b) ({ __typeof__(a) _a = (a), _b = (b); _a < _b ? _a : _b; })
#define max(a, b) ({ __typeof__(a) _a = (a), _b = (b); _a > _b ? _a : _b; })
#define clamp(_x, _mi, _ma) (min(max(_x, _mi), _ma))
#define ifnan(_x, _alt) ({ __typeof__(_x) __x = (_x); isnan(__x) ? (_alt) : __x; })
#define sign(a) ({                                       \
        __typeof__(a) _a = (a);                          \
        (__typeof__(a))(_a < 0 ? -1 : (_a > 0 ? 1 : 0)); \
    })
// -1 right, 0 on, 1 left
#define point_side(_p, _a, _b) ({                                              \
        __typeof__(_p) __p = (_p), __a = (_a), __b = (_b);                         \
        -(((__p.x - __a.x) * (__b.y - __a.y))                                  \
            - ((__p.y - __a.y) * (__b.x - __a.x)));                            \
    })

/*
* Each number represents a specific tile or elem in map 
* 1 represents wall tiles or bound
* 0 represents empty space
* 2, 3, 4 represents specific obj or elemt
*/
static u8 MAPDATA[MAP_SIZE * MAP_SIZE] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 3, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 4, 4, 0, 1,
    1, 0, 0, 0, 4, 0, 0, 1,
    1, 0, 3, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void verline(State *state, int x, int y0, int y1, u32 color) {
    for (int y = y0; y < y1; y++) {
        state->pixels[(y * SCREEN_WIDTH) + x] = color;
    }
}

void render(State *state) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // x coordinate in space from [-1, 1]
        const f32 xcam = (2 * (x / (f32) (SCREEN_WIDTH))) - 1;
        
        // ray dir through this column
        const v2 dir = {
            state->dir.x + state->plane.x * xcam,
            state->dir.y + state->plane.y * xcam
        };

        v2 pos = state->pos;
        v2i ipos = { (int) pos.x, (int) pos.y };
        
        // dist ray must travel from one x/y side to the next
        const v2 deltadist = {
            fabsf(dir.x) < 1e-20 ? 1e30 : fabsf(1.0f / dir.x),
            fabsf(dir.y) < 1e-20 ? 1e30 : fabsf(1.0f / dir.y),
        };
        
        // dist from start pos to first x/y side
        v2 sidedist = {
            deltadist.x * (dir.x < 0 ? (pos.x - ipos.x) : (ipos.x + 1 - pos.x)),
            deltadist.y * (dir.y < 0 ? (pos.y - ipos.y) : (ipos.y + 1 - pos.y)),
        };
        
        // int step dir for x/y, calc from overall diff
        const v2i step = { (int) sign(dir.x), (int) sign(dir.y) };

        struct { int val, side; v2 pos; } hit = { 0, 0, { 0.0f, 0.0f } };

        while (!hit.val) {
            if (sidedist.x < sidedist.y) {
                sidedist.x += deltadist.x;
                ipos.x += step.x;
                hit.side = 0;
            } else {
                sidedist.y += deltadist.y;
                ipos.y += step.y;
                hit.side = 1;
            }

            ASSERT(
                ipos.x >= 0
                && ipos.x < MAP_SIZE
                && ipos.y >= 0
                && ipos.y < MAP_SIZE,
                "DDA out of bounds"
            );

            hit.val = MAPDATA[ipos.y * MAP_SIZE + ipos.x];
        }

        u32 color;
        switch (hit.val) {
            case 1: color = 0xFF0000FF; break;
            case 2: color = 0xFF00FF00; break;
            case 3: color = 0xFFFF0000; break;
            case 4: color = 0xFFFF00FF; break;
        }
        
        // darken colors on y-side
        if (hit.side == 1) {
            const u32
                br = ((color & 0xFF00FF) * 0xC0) >> 8,
                g  = ((color & 0x00FF00) * 0xC0) >> 8;

            color = 0xFF000000 | (br & 0xFF00FF) | (g & 0x00FF00);
        }

        hit.pos = (v2) { pos.x + sidedist.x, pos.y + sidedist.y };

        // distance to hit
        const f32 dperp =
            hit.side == 0 ?
                (sidedist.x - deltadist.x)
                : (sidedist.y - deltadist.y);

        // Perfom perspective division, calculate line height relative to screen center 
        const int
            h = (int) (SCREEN_HEIGHT / dperp),
            y0 = max((SCREEN_HEIGHT / 2) - (h / 2), 0),
            y1 = min((SCREEN_HEIGHT / 2) + (h / 2), SCREEN_HEIGHT - 1);

        verline(state, x, 0, y0, 0xFF202020);
        verline(state, x, y0, y1, color);
        verline(state, x, y1, SCREEN_HEIGHT - 1, 0xFF505050);
    }
}

void rot(State *state, f32 rot) {
    const v2 d = state->dir, p = state->plane;
    state->dir.x = d.x * cos(rot) - d.y * sin(rot);
    state->dir.y = d.x * sin(rot) + d.y * cos(rot);
    state->plane.x = p.x * cos(rot) - p.y * sin(rot);
    state->plane.y = p.x * sin(rot) + p.y * cos(rot);
}

