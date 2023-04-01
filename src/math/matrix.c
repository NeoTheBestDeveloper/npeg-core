#include <malloc.h>
#include <string.h>

#include "die.h"
#include "matrix.h"

Matrix matrix_new(i64 width, i64 height, MatrixType matrix_type,
                  bool fill_zeroes) {
    Matrix matrix = {
        .height = height,
        .width = width,
    };

    switch (matrix_type) {
    case U8_MATRIX: {
        matrix.data = malloc(sizeof(u8 *) * (u64)height);
        u8 **data = (u8 **)matrix.data;

        if (fill_zeroes) {
            for (i64 i = 0; i < height; ++i) {
                data[i] = calloc((u64)width, sizeof(u8));
            }
        } else {
            for (i64 i = 0; i < height; ++i) {
                data[i] = malloc(sizeof(u8) * (u64)width);
            }
        }
        break;
    }

    case U16_MATRIX: {
        matrix.data = malloc(sizeof(u16 *) * (u64)height);
        if (fill_zeroes) {
            for (i64 i = 0; i < height; i++) {
                matrix.data[i] = calloc((u64)width, sizeof(u16));
            }
        } else {
            for (i64 i = 0; i < height; i++) {
                matrix.data[i] = malloc(sizeof(u16) * (u64)width);
            }
        }
        break;
    }

    default:
        die("Error: unknow matrix format. Aviable: U8_MATRIX, U16_MATRIX "
            "only.\n",
            NULL)
    }

    return matrix;
}

Matrix matrix_copy(const Matrix *src) {
    Matrix dst = matrix_new(src->width, src->height, src->matrix_type, false);

    for (i64 i = 0; i < src->height; ++i) {
        memcpy(dst.data[i], src->data[i], (u64)(src->width));
    }

    return dst;
}

bool matrix_cmp(const Matrix *m1, const Matrix *m2) {
    if (m1->matrix_type != m2->matrix_type) {
        return false;
    }

    if (m1->height != m2->height || m1->width != m2->width) {
        return false;
    }

    if (m1->matrix_type == U8_MATRIX) {
        u8 **data1 = (u8 **)m1->data;
        u8 **data2 = (u8 **)m2->data;
        for (i64 i = 0; i < m1->height; ++i) {
            if (0 !=
                memcmp(data1[i], data2[i], sizeof *data1 * (u64)m1->width)) {
                return false;
            }
        }
        return true;
    } else {
        u16 **data1 = (u16 **)m1->data;
        u16 **data2 = (u16 **)m2->data;
        for (i64 i = 0; i < m1->height; ++i) {
            if (0 !=
                memcmp(data1[i], data2[i], sizeof *data1 * (u64)m1->width)) {
                return false;
            }
        }
        return true;
    }
}
void matrix_free(Matrix *matrix) {
    for (i64 i = 0; i < matrix->height; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}
