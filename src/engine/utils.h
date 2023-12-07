#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <math.h>

#include "../../include/SDL2/SDL.h"

/* Constants */

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

#define EYE_Z 1.65f
#define HFOV DEG2RAD(90.0f)
#define VFOV 0.5f

#define ZNEAR 0.0001f 
#define ZFAR 128.0f
