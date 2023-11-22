#pragma once

#include <stdio.h>
#include <stdlib.h>

// Inspiration from jdh
#define ASSERT(_e, ...) \
    do { \
        if (!(_e)) { \
            fprintf(stderr, __VA_ARGS__); \
            exit(1); \
        } \
    } while (0)
