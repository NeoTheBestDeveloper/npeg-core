#include <math.h>

#include "../math/matrix.h"
#include "../math/trig.h"
#include "algorithms.h"
#include "types.h"

// TODO: USE AVX INSTRUCTIONS.
// TODO: Threads.

static void matrix_u16_bilinear_inter(const Matrix* src, Matrix* dst) {
    u16** src_data = (u16**)src->data;
    u16** dst_data = (u16**)dst->data;

    i64 src_height = src->height;
    i64 src_width = src->width;

    for (i64 i = 1; i < src_height - 2; i++) {
        f32 y = (f32)i;
        f32 y1 = y + 1.0f;
        f32 y2 = y - 1.0f;

        f32 y2_minus_y1_inv = 1 / (y2 - y1);
        f32 y2_minus_y = y2 - y;
        f32 y_minus_y1 = y - y1;

        for (i64 j = 1; j < src_width - 2; j++) {
            f32 x = (f32)j;
            f32 x1 = x - 1.0f;
            f32 x2 = x + 1.0f;

            f32 Q11 = (f32)src_data[i + 1][j - 1];
            f32 Q12 = (f32)src_data[i - 1][j - 1];
            f32 Q21 = (f32)src_data[i + 1][j + 1];
            f32 Q22 = (f32)src_data[i - 1][j + 1];

            f32 x2_minus_x1 = x2 - x1;
            f32 x2_minus_x = x2 - x;
            f32 x_minus_x1 = x - x1;

            f32 first_factor = x2_minus_x / x2_minus_x1;
            f32 second_factor = x_minus_x1 / x2_minus_x1;

            f32 f_x_y1 = first_factor * Q11 + second_factor * Q21;
            f32 f_x_y2 = first_factor * Q12 + second_factor * Q22;

            f32 f_x_y = roundf(y2_minus_y * y2_minus_y1_inv * f_x_y1 + y_minus_y1 * y2_minus_y1_inv * f_x_y2);
            dst_data[i][j] = (u8)f_x_y;
        }
    }
}

static void matrix_u8_bilinear_inter(const Matrix* src, Matrix* dst) {
    u8** src_data = (u8**)src->data;
    u8** dst_data = (u8**)dst->data;

    i64 src_height = src->height;
    i64 src_width = src->width;

    for (i64 i = 0; i < src_height; i++) {
        f32 y = (f32)i;
        f32 y1 = y + 1.0f;
        f32 y2 = y - 1.0f;

        f32 y2_minus_y1_inv = 1 / (y2 - y1);
        f32 y2_minus_y = y2 - y;
        f32 y_minus_y1 = y - y1;

        for (i64 j = 0; j < src_width; j++) {
            f32 x = (f32)j;
            f32 x1 = x - 1.0f;
            f32 x2 = x + 1.0f;

            f32 Q11 = (f32)src_data[i + 1][j - 1];
            f32 Q12 = (f32)src_data[i - 1][j - 1];
            f32 Q21 = (f32)src_data[i + 1][j + 1];
            f32 Q22 = (f32)src_data[i - 1][j + 1];

            f32 x2_minus_x1 = x2 - x1;
            f32 x2_minus_x = x2 - x;
            f32 x_minus_x1 = x - x1;

            f32 first_factor = x2_minus_x / x2_minus_x1;
            f32 second_factor = x_minus_x1 / x2_minus_x1;

            f32 f_x_y1 = first_factor * Q11 + second_factor * Q21;
            f32 f_x_y2 = first_factor * Q12 + second_factor * Q22;

            f32 f_x_y = roundf(y2_minus_y * y2_minus_y1_inv * f_x_y1 + y_minus_y1 * y2_minus_y1_inv * f_x_y2);
            dst_data[i][j] = (u8)f_x_y;
        }
    }
}

void matrix_interpolate(Matrix* m, Interpolation inter) {
    Matrix res;
    if (inter != INTER_NONE) {
        res = matrix_new(m->width, m->height, m->matrix_type, true);
    }

    if (m->matrix_type == U8_MATRIX) {
        switch (inter) {
        case INTER_LINIAR:
            matrix_u8_bilinear_inter(m, &res);
            break;
        case INTER_CUBIC:
        case INTER_LANCZOS:
        case INTER_SINC:
        case INTER_NONE:
        default:
            return;
        }
    } else {
        switch (inter) {
        case INTER_LINIAR:
            matrix_u16_bilinear_inter(m, &res);
            break;
        case INTER_CUBIC:
        case INTER_LANCZOS:
        case INTER_SINC:
        case INTER_NONE:
        default:
            return;
        }
    }

    matrix_free(m);
    *m = res;
}
