#pragma once

#include <stdbool.h>
#include <types.h>

typedef enum {
    U8_MATRIX = 0,
    U16_MATRIX = 1,
} MatrixType;

// Matrix work with unsigned integer types as u8 or u16.
typedef struct {
    i64 height, width;
    void** data;
    MatrixType matrix_type;
} Matrix;

Matrix matrix_new(i64 width, i64 height, MatrixType matrix_type, bool fill_zeroes);
Matrix matrix_copy(const Matrix* src);
void matrix_free(Matrix* matrix);
bool matrix_cmp(const Matrix* m1, const Matrix* m2);
