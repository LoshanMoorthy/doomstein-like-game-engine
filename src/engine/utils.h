#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <math.h>

#include "../../include/SDL2/SDL.h"

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

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216

#define EYE_Z 1.65f
#define HFOV DEG2RAD(90.0f)
#define VFOV 0.5f

#define ZNEAR 0.0001f 
#define ZFAR 128.0f

/* Macros */

#define v2_to_v2i(_v) ({ __typeof__(_v) __v = (_v); (v2i) { __v.x, __v.y }; })
#define v2i_to_v2(_v) ({ __typeof__(_v) __v = (_v); (v2) { __v.x, __v.y }; })

#define dot(_v0, _v1) ({ __typeof__(_v0) __v0 = (_v0), __v1 = (_v1); (__v0.x * __v1.x) + (__v0.y * __v1.y); })
#define length(_vl) ({ __typeof__(_vl) __vl = (_vl); sqrtf(dot(__vl, __vl)); })
#define normalize(_vn) ({ __typeof__(_vn) __vn = (_vn); const f32 l = length(__vn); (__typeof__(_vn)) { __vn.x / l, __vn.y / l }; })
#define min(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a < __b ? __a : __b; })
#define max(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a > __b ? __a : __b; })
#define clamp(_x, _mi, _ma) (min(max(_x, _mi), _ma))
#define ifnan(_x, _alt) ({ __typeof__(_x) __x = (_x); isnan(__x) ? (_alt) : __x; })

// -1 right, 0 on, 1 left
#define point_side(_p, _a, _b) ({                                              \
        __typeof__(_p) __p = (_p), __a = (_a), __b = (_b);                         \
        -(((__p.x - __a.x) * (__b.y - __a.y))                                  \
            - ((__p.y - __a.y) * (__b.x - __a.x)));                            \
    })

/* Structs */

typedef struct v2_s { f32 x, y; } v2;
typedef struct v2i_s { i32 x, y; } v2i;

/* Function */
v2 rotate(v2 v, f32 a);
v2 intersect_segments(v2 a0, v2 a1, v2 b0, v2 b1);
