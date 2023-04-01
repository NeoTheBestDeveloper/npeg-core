#pragma once

#include "../math/matrix.h"
#include "types.h"

typedef enum {
    INTER_NONE = 0,
    INTER_LINIAR = 1,
    INTER_CUBIC = 2,
    INTER_LANCZOS = 3,
    INTER_SINC = 4,
} Interpolation;

void matrix_interpolate(Matrix* m, Interpolation inter);
void matrix_rotate(Matrix* m, f32 degrees, Interpolation inter);
