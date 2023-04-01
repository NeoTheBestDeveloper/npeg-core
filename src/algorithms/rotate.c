#include <malloc.h>
#include <math.h>
#include <pthread.h>

#include "../math/matrix.h"
#include "../math/trig.h"
#include "algorithms.h"
#include "threads_utils.h"
#include "types.h"

typedef struct {
    void** rows;
    const Matrix* src;
    i64 from, count;
    f32 sin_a, cos_a;
} RotateThreadArgs;

typedef struct {
    i64 from, count;
} RotateThreadResult;

#define BLOCK_SIZE 64

static inline void _matrix_u8_rotate_sub(f32 width_half, f32 height_half, f32 cos_a, f32 sin_a, f32 old_y_mult_sin_a,
                                         f32 old_y_mult_cos_a, i64 src_width, u8** rows, u8** src_data, i64 i, i64 j,
                                         i64 src_height) {
    f32 old_x = width_half - (f32)j;

    f32 new_x = old_x * cos_a - old_y_mult_sin_a;
    f32 new_y = old_y_mult_cos_a + old_x * sin_a;

    i64 new_j = (i64)(width_half - new_x);
    i64 new_i = (i64)(height_half - new_y);

    if (new_i >= src_height) {
        return;
    } else if (new_j >= src_width) {
        return;
    } else if (new_j < 0) {
        return;
    } else if (new_i < 0) {
        return;
    }
    rows[new_i][new_j] = src_data[i][j];
}

static inline void _matrix_u8_rotate(f32 sin_a, f32 cos_a, i64 i, f32 height_half, f32 width_half, i64 src_width,
                                     u8** rows, u8** src_data, i64 src_height) {
    f32 old_y = height_half - (f32)i;
    f32 old_y_mult_sin_a = old_y * sin_a;
    f32 old_y_mult_cos_a = old_y * cos_a;

    for (i64 j = 0; j < src_width; j += BLOCK_SIZE) {
        for (i64 k = BLOCK_SIZE - 1; k != 0; --k) {
            i64 idx = j + k;
            if (idx < src_width) {
                _matrix_u8_rotate_sub(width_half, height_half, cos_a, sin_a, old_y_mult_sin_a, old_y_mult_cos_a,
                                      src_width, rows, src_data, i, idx, src_height);
            }
        }
    }
}

static void* matrix_u8_rotate(void* _args) {
    RotateThreadArgs* args = (RotateThreadArgs*)_args;

    u8** src_data = (u8**)args->src->data;

    i64 src_width = args->src->width;
    i64 src_height = args->src->height;
    f32 height_half = (f32)(args->src->height >> 1);
    f32 width_half = (f32)(args->src->width >> 1);

    f32 sin_a = args->sin_a;
    f32 cos_a = args->cos_a;
    i64 last_row = args->from + args->count;
    i64 first_row = args->from;
    u8** rows = (u8**)args->rows;

    for (i64 i = first_row; i < last_row; i += BLOCK_SIZE) {
        for (i64 k = BLOCK_SIZE - 1; k != 0; --k) {
            i64 idx = i + k;
            if (idx < last_row) {
                _matrix_u8_rotate(sin_a, cos_a, idx, height_half, width_half, src_width, rows, src_data, src_height);
            }
        }
    }
    free(args);

    return NULL;
}

static inline void _matrix_u16_rotate_sub(f32 width_half, f32 height_half, f32 cos_a, f32 sin_a, f32 old_y_mult_sin_a,
                                          f32 old_y_mult_cos_a, i64 src_width, u16** rows, u16** src_data, i64 i, i64 j,
                                          i64 src_height) {
    f32 old_x = width_half - (f32)j;

    f32 new_x = old_x * cos_a - old_y_mult_sin_a;
    f32 new_y = old_y_mult_cos_a + old_x * sin_a;

    i64 new_j = (i64)(width_half - new_x);
    i64 new_i = (i64)(height_half - new_y);

    if (new_i >= src_height) {
        return;
    } else if (new_j >= src_width) {
        return;
    } else if (new_j < 0) {
        return;
    } else if (new_i < 0) {
        return;
    }
    rows[new_i][new_j] = src_data[i][j];
}

static inline void _matrix_u16_rotate(f32 sin_a, f32 cos_a, i64 i, f32 height_half, f32 width_half, i64 src_width,
                                      u16** rows, u16** src_data, i64 src_height) {
    f32 old_y = height_half - (f32)i;
    f32 old_y_mult_sin_a = old_y * sin_a;
    f32 old_y_mult_cos_a = old_y * cos_a;

    for (i64 j = 0; j < src_width; j += BLOCK_SIZE) {
        for (i64 k = BLOCK_SIZE - 1; k != 0; --k) {
            i64 idx = j + k;
            if (idx < src_width) {
                _matrix_u16_rotate_sub(width_half, height_half, cos_a, sin_a, old_y_mult_sin_a, old_y_mult_cos_a,
                                       src_width, rows, src_data, i, idx, src_height);
            }
        }
    }
}

static void* matrix_u16_rotate(void* _args) {
    RotateThreadArgs* args = (RotateThreadArgs*)_args;

    u16** src_data = (u16**)args->src->data;

    i64 src_width = args->src->width;
    i64 src_height = args->src->height;
    f32 height_half = (f32)(args->src->height >> 1);
    f32 width_half = (f32)(args->src->width >> 1);

    f32 sin_a = args->sin_a;
    f32 cos_a = args->cos_a;
    i64 last_row = args->from + args->count;
    i64 first_row = args->from;
    u16** rows = (u16**)args->rows;

    for (i64 i = first_row; i < last_row; i += BLOCK_SIZE) {
        for (i64 k = BLOCK_SIZE - 1; k != 0; --k) {
            i64 idx = i + k;
            if (idx < last_row) {
                _matrix_u16_rotate(sin_a, cos_a, idx, height_half, width_half, src_width, rows, src_data, src_height);
            }
        }
    }
    free(args);

    return NULL;
}

void matrix_rotate(Matrix* m, f32 degrees, Interpolation inter) {
    Matrix res = matrix_new(m->width, m->height, m->matrix_type, true);

    f32 cos_a = cosf(deg_to_rad(degrees));
    f32 sin_a = sinf(deg_to_rad(degrees));

    i64 threads_count = get_procs_count();
    pthread_t* threads = (pthread_t*)malloc(sizeof *threads * (u64)threads_count);

    void* (*rotate_function)(void*) = (m->matrix_type == U8_MATRIX) ? &matrix_u8_rotate : &matrix_u16_rotate;

    for (i64 i = threads_count - 1; i != 0; --i) {
        RotateThreadArgs* data = (RotateThreadArgs*)malloc(sizeof *data);

        data->src = m;
        data->sin_a = sin_a;
        data->cos_a = cos_a;
        data->from = (m->height / threads_count) * i;
        data->count = (m->height / threads_count);
        data->rows = res.data;

        pthread_create(threads + i, NULL, rotate_function, data);
    }

    for (i64 i = threads_count - 1; i != 0; --i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);

    matrix_interpolate(&res, inter);

    matrix_free(m);
    *m = res;
}
