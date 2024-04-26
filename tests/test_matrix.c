// #include <criterion/criterion.h>

#include "../src/math/matrix.h"
#include "types.h"

int main(int argc, char* argv[]) { return 0; }

// Test(u8_matrix, test_matrix_fill_zero) {
//     Matrix m1 = matrix_new(3, 3, U8_MATRIX, 1);
//     Matrix m2 = matrix_new(3, 3, U8_MATRIX, 1);
//
//     u8** m1_data = (u8**)m1.data;
//     u8** m2_data = (u8**)m2.data;
//     u8 zeros[3] = {0};
//
//     for (i64 i = 0; i < 3; ++i) {
//         cr_assert_arr_eq(m1_data[i], zeros, sizeof *m1_data[i]);
//         cr_assert_arr_eq(m2_data[i], zeros, sizeof *m1_data[i]);
//     }
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
//
// Test(u8_matrix, test_matrix_cmp) {
//     Matrix m1 = matrix_new(3, 3, U8_MATRIX, 0);
//     Matrix m2 = matrix_new(3, 3, U8_MATRIX, 0);
//
//     u8** m1_data = (u8**)m1.data;
//     u8** m2_data = (u8**)m2.data;
//
//     for (i64 i = 0; i < 3; ++i) {
//         for (i64 j = 0; j < 3; ++j) {
//             m1_data[i][j] = (u8)(i + j);
//             m2_data[i][j] = (u8)(i + j);
//         }
//     }
//
//     cr_assert(matrix_cmp(&m1, &m2));
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
//
// Test(u8_matrix, test_matrix_copy) {
//     Matrix m1 = matrix_new(3, 3, U8_MATRIX, 0);
//     Matrix m2 = matrix_copy(&m1);
//
//     cr_assert(matrix_cmp(&m1, &m2));
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
//
//
// Test(u16_matrix, test_matrix_fill_zero) {
//     Matrix m1 = matrix_new(3, 3, U16_MATRIX, 1);
//     Matrix m2 = matrix_new(3, 3, U16_MATRIX, 1);
//
//     u16** m1_data = (u16**)m1.data;
//     u16** m2_data = (u16**)m2.data;
//     u16 zeros[3] = {0};
//
//     for (i64 i = 0; i < 3; ++i) {
//         cr_assert_arr_eq(m1_data[i], zeros, sizeof *m1_data[i]);
//         cr_assert_arr_eq(m2_data[i], zeros, sizeof *m1_data[i]);
//     }
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
//
// Test(u16_matrix, test_matrix_cmp) {
//     Matrix m1 = matrix_new(3, 3, U16_MATRIX, 0);
//     Matrix m2 = matrix_new(3, 3, U16_MATRIX, 0);
//
//     u16** m1_data = (u16**)m1.data;
//     u16** m2_data = (u16**)m2.data;
//
//     for (i64 i = 0; i < 3; ++i) {
//         for (i64 j = 0; j < 3; ++j) {
//             m1_data[i][j] = (u16)(i + j);
//             m2_data[i][j] = (u16)(i + j);
//         }
//     }
//
//     cr_assert(matrix_cmp(&m1, &m2));
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
//
// Test(u16_matrix, test_matrix_copy) {
//     Matrix m1 = matrix_new(3, 3, U16_MATRIX, 0);
//     Matrix m2 = matrix_copy(&m1);
//
//     cr_assert(matrix_cmp(&m1, &m2));
//
//     matrix_free(&m1);
//     matrix_free(&m2);
// }
