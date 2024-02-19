#include <check.h>
#include <stdio.h>

#include "../custom_matrix.h"

#define MATRIX_ER 1
#define CALC_ER 2

void custom_set(double *nums, matrix_t *A) {
  int count = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = nums[count];
      count++;
    }
  }
}
/* CREATE */
START_TEST(create_1) {
  matrix_t A;
  int rows = 0;
  int columns = 1;
  int res = custom_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, MATRIX_ER);
}
END_TEST

START_TEST(create_2) {
  int rows = 10;
  int columns = 10;
  int res = custom_create_matrix(rows, columns, NULL);
  ck_assert_int_eq(res, MATRIX_ER);
}
END_TEST

/* REMOVE */
START_TEST(remove_1) { custom_remove_matrix(NULL); }
END_TEST

START_TEST(remove_2) {
  matrix_t A;
  custom_create_matrix(10, 10, &A);
  custom_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

/* EQUAL */
START_TEST(equal_1) {
  int res = custom_eq_matrix(NULL, NULL);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_2) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 10, &A);
  custom_create_matrix(10, 10, &B);
  A.rows = 0;
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  A.rows = 10;
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(equal_3) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 10, &A);
  custom_create_matrix(10, 9, &B);
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(equal_4) {
  matrix_t A;
  matrix_t B;
  double nums[4] = {123.456, 2, 3, 4};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_set(nums, &A);
  custom_set(nums, &B);
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(equal_5) {
  matrix_t A;
  matrix_t B;
  double A_nums[4] = {1.2345678, 2, 3, 4};
  double B_nums[4] = {1.2345678, 2, 3, 4};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(equal_6) {
  matrix_t A;
  matrix_t B;
  double A_nums[4] = {1.23456789, 2, 3, 4};
  double B_nums[4] = {1.23456789, 2, 3, 4};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(equal_7) {
  matrix_t A;
  matrix_t B;
  double A_nums[4] = {1.2345678, 2, 3, 4};
  double B_nums[4] = {1.2345677, 2, 3, 4};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  int res = custom_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

/* SUM */
START_TEST(sum_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  custom_create_matrix(1, 1, &A);
  custom_create_matrix(1, 1, &B);
  custom_create_matrix(1, 1, &C);
  A.matrix[0][0] = 38.12389;
  B.matrix[0][0] = -129.4910;
  C.matrix[0][0] = -91.36711;
  int res = custom_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sum_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double B_nums[4] = {109428035910.10189, -19872409.1489, 3, 140912.5};
  double result_nums[4] = {109428157149.21489, -19870008.02498, -348898.2,
                           2529926.5};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_create_matrix(2, 2, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sum_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                      912039.12389,  129034.23400, 0,         1203,
                      9000000.123};
  double B_nums[9] = {
      109428035910.1024189, -19872409.1489, 3, 140912.5, 0, 12930124, 1942.3489,
      102.234891,           10230912.1};
  double result_nums[9] = {
      109428157149.2244319, -19870008.02498, -348898.2, 2529926.5,
      912039.12389,         13059158.234,    1942.3489, 1305.234891,
      19230912.223};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &B);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);

  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sum_4) {
  matrix_t A;
  int res = custom_sum_matrix(NULL, &A, &A);
  ck_assert_int_eq(res, 1);
}

START_TEST(sum_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 1, &B);
  int res = custom_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(sum_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(10, 10, &A);
  custom_create_matrix(10, 10, &B);
  A.rows = 0;
  int res = custom_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(sum_7) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double B_nums[6] = {2, 3, 4, 5, 6, 7};
  double result_nums[6] = {3, 5, 7, 9, 11, 13};
  custom_create_matrix(3, 2, &A);
  custom_create_matrix(3, 2, &B);
  custom_create_matrix(3, 2, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}

/* SUB */
START_TEST(sub_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  custom_create_matrix(1, 1, &A);
  custom_create_matrix(1, 1, &B);
  custom_create_matrix(1, 1, &C);
  A.matrix[0][0] = 38.12389;
  B.matrix[0][0] = -129.4910;
  C.matrix[0][0] = 167.61489;
  int res = custom_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sub_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double B_nums[4] = {109910.10189, -19872409.1489, 3, 140912.5};
  double result_nums[4] = {11329.01111, 19874810.27282, -348904.2, 2248101.5};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_create_matrix(2, 2, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sub_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                      912039.12389,  129034.23400, 0,         1203,
                      9000000.123};
  double B_nums[9] = {
      109428035910.1024189, -19872409.1489, 3, 140912.5, 0, 12930124, 1942.3489,
      102.234891,           10230912.1};
  double result_nums[9] = {
      -109427914670.9804059, 19874810.27282, -348904.2,  2248101.5,
      912039.12389,          -12801089.766,  -1942.3489, 1100.765109,
      -1230911.977};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &B);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(sub_4) {
  matrix_t A;
  int res = custom_sub_matrix(NULL, &A, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 1, &B);
  int res = custom_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(sub_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(10, 10, &A);
  custom_create_matrix(10, 10, &B);
  A.rows = 0;
  int res = custom_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(sub_7) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double B_nums[6] = {2, 3, 4, 5, 6, 7};
  double result_nums[6] = {-1, -1, -1, -1, -1, -1};
  custom_create_matrix(3, 2, &A);
  custom_create_matrix(3, 2, &B);
  custom_create_matrix(3, 2, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int result = custom_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(result, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

/* MULTI NUM */
START_TEST(multi_num_1) {
  matrix_t A;
  int res = custom_mult_number(NULL, 10, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(multi_num_2) {
  matrix_t A;
  matrix_t C;
  custom_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = custom_mult_number(&A, 10, &C);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(multi_num_3) {
  matrix_t A;
  double number = 3.12890;
  matrix_t B;
  matrix_t C;
  double A_nums[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double result_nums[4] = {379345.0606657, 7512.876633288, -1091676.96468,
                           7474985.9046};
  custom_create_matrix(2, 2, &A);
  custom_create_matrix(2, 2, &B);
  custom_set(A_nums, &A);
  custom_set(result_nums, &B);
  int result = custom_mult_number(&A, number, &C);
  ck_assert_int_eq(custom_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(result, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(multi_num_4) {
  matrix_t A;
  double number = 3901.904;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                      912039.12389,  129034.23400, 0,         1203,
                      9000000.123};
  double result_nums[9] = {473063415.139012752,
                           9368955.02794368,
                           -1361378987.8848,
                           9321703282.656,
                           3558689105.66288656,
                           503479193.781536,
                           0,
                           4693990.512,
                           35117136479.934192};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &B);
  custom_set(A_nums, &A);
  custom_set(result_nums, &B);
  int res = custom_mult_number(&A, number, &C);
  ck_assert_int_eq(custom_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

/* TRANSPOSE */
START_TEST(transpose_1) {
  matrix_t A;
  int res = custom_transpose(NULL, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = custom_transpose(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double result_nums[6] = {1, 4, 2, 5, 3, 6};
  custom_create_matrix(2, 3, &A);
  custom_create_matrix(3, 2, &C);
  custom_set(A_nums, &A);
  custom_set(result_nums, &C);
  int res = custom_transpose(&A, &B);
  ck_assert_int_eq(custom_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double result_nums[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(result_nums, &C);
  int res = custom_transpose(&A, &B);
  ck_assert_int_eq(custom_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[6] = {1, 2, 3, 4, 5, 6};
  double result_nums[6] = {1, 3, 5, 2, 4, 6};
  custom_create_matrix(3, 2, &A);
  custom_create_matrix(2, 3, &C);
  custom_set(A_nums, &A);
  custom_set(result_nums, &C);
  int res = custom_transpose(&A, &B);
  ck_assert_int_eq(custom_eq_matrix(&C, &B), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

/* MULTI MAT */
START_TEST(multi_mat_1) {
  matrix_t A;
  int result = custom_mult_matrix(NULL, &A, &A);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(multi_mat_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(10, 10, &A);
  custom_create_matrix(10, 10, &B);
  A.rows = 0;
  int result = custom_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 1);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(multi_mat_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(2, 3, &A);
  custom_create_matrix(2, 3, &B);
  int result = custom_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, 2);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
}
END_TEST

START_TEST(multi_mat_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double B_nums[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double result_nums[9] = {92.4, 117.6, 205.8, 268.8};
  custom_create_matrix(2, 3, &A);
  custom_create_matrix(3, 2, &B);
  custom_create_matrix(2, 2, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(multi_mat_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[9] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2, 8.4, 9.6, 10.8};
  double B_nums[9] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0, 24.5, 28.0, 31.5};
  double result_nums[9] = {126,   151.2, 176.4, 277.2, 340.2,
                           403.2, 428.4, 529.2, 630};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &B);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

START_TEST(multi_mat_6) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  double A_nums[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double B_nums[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double result_nums[9] = {37.8,  50.4,  63,  79.8, 109.2,
                           138.6, 121.8, 168, 214.2};
  custom_create_matrix(3, 2, &A);
  custom_create_matrix(2, 3, &B);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(B_nums, &B);
  custom_set(result_nums, &C);
  int res = custom_mult_matrix(&A, &B, &D);
  ck_assert_int_eq(custom_eq_matrix(&C, &D), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
  custom_remove_matrix(&D);
}
END_TEST

/* DETERMINANT */
START_TEST(deter_1) {
  int result = custom_determinant(NULL, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(deter_2) {
  matrix_t A;
  double det;
  custom_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = custom_determinant(&A, &det);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_3) {
  matrix_t A;
  double det;
  custom_create_matrix(10, 9, &A);
  int res = custom_determinant(&A, &det);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_4) {
  matrix_t A;
  double det;
  double det_true = 984.1238;
  custom_create_matrix(1, 1, &A);
  A.matrix[0][0] = 984.1238;
  int res = custom_determinant(&A, &det);
  ck_assert_double_eq_tol(det, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_5) {
  matrix_t A;
  double det;
  double det_true = -347879921061.47;
  double A_nums[9] = {18248.2488, 91293.124898, 300.1,  390.1123, 44.5, 0,
                      1,          1238.4,       9999.99};
  custom_create_matrix(3, 3, &A);
  custom_set(A_nums, &A);
  int res = custom_determinant(&A, &det);
  ck_assert_double_eq_tol(det, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_6) {
  matrix_t A;
  double det;
  double det_true = -40;
  double A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  custom_create_matrix(3, 3, &A);
  custom_set(A_nums, &A);
  int res = custom_determinant(&A, &det);
  ck_assert_double_eq_tol(det, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_7) {
  matrix_t A;
  double det;
  double det_true = -1369800;
  double A_nums[25] = {1,  2,  3,   4, 5,  6,  7,  8,  9,  10, 11, 12, 49,
                       14, 15, 161, 7, 18, 19, 20, 64, 48, 1,  2,  3};
  custom_create_matrix(5, 5, &A);
  custom_set(A_nums, &A);
  int res = custom_determinant(&A, &det);
  ck_assert_double_eq_tol(det, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(deter_8) {
  matrix_t A;
  double det;
  double det_true = 17187;
  double A_nums[4] = {9, 2, 96, 1931};
  custom_create_matrix(2, 2, &A);
  custom_set(A_nums, &A);
  int res = custom_determinant(&A, &det);
  ck_assert_double_eq_tol(det, det_true, 1e+08);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
}
END_TEST

/* COMPLEMENTS */
START_TEST(complements_1) {
  int result = custom_calc_complements(NULL, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(complements_2) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = custom_calc_complements(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(complements_3) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 9, &A);
  int res = custom_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(complements_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(1, 1, &A);
  custom_create_matrix(1, 1, &C);
  A.matrix[0][0] = 984.1238;
  C.matrix[0][0] = 984.1238;
  int res = custom_calc_complements(&A, &B);
  ck_assert_int_eq(custom_eq_matrix(&B, &C), 0);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(complements_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double result_nums[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(result_nums, &C);
  int res = custom_calc_complements(&A, &B);
  ck_assert_int_eq(custom_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

/* INVERSE */
START_TEST(inverse_1) {
  int res = custom_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 10, &A);
  A.rows = 0;
  int res = custom_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_3) {
  matrix_t A;
  matrix_t B;
  custom_create_matrix(10, 9, &A);
  int res = custom_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  custom_create_matrix(1, 1, &A);
  custom_create_matrix(1, 1, &C);
  A.matrix[0][0] = 42.12849;
  C.matrix[0][0] = 1 / 42.12849;
  int res = custom_inverse_matrix(&A, &B);
  ck_assert_double_eq(custom_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_5) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double A_nums[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double result_nums[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  custom_create_matrix(3, 3, &A);
  custom_create_matrix(3, 3, &C);
  custom_set(A_nums, &A);
  custom_set(result_nums, &C);
  int res = custom_inverse_matrix(&A, &B);
  ck_assert_double_eq(custom_eq_matrix(&B, &C), 1);
  ck_assert_int_eq(res, 0);
  custom_remove_matrix(&A);
  custom_remove_matrix(&B);
  custom_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_6) {
  matrix_t A;
  matrix_t B;
  double A_nums[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                       14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
  custom_create_matrix(5, 5, &A);
  custom_set(A_nums, &A);
  int res = custom_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  custom_remove_matrix(&A);
}
END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tcase_creat = tcase_create("CREATE");
  tcase_add_test(tcase_creat, create_1);
  tcase_add_test(tcase_creat, create_2);
  suite_add_tcase(suite, tcase_creat);

  TCase *tcase_remove = tcase_create("REMOVE");
  tcase_add_test(tcase_remove, remove_1);
  tcase_add_test(tcase_remove, remove_2);
  suite_add_tcase(suite, tcase_remove);

  TCase *tcase_equal = tcase_create("EQUAL");
  tcase_add_test(tcase_equal, equal_1);
  tcase_add_test(tcase_equal, equal_2);
  tcase_add_test(tcase_equal, equal_3);
  tcase_add_test(tcase_equal, equal_4);
  tcase_add_test(tcase_equal, equal_5);
  tcase_add_test(tcase_equal, equal_6);
  tcase_add_test(tcase_equal, equal_7);
  suite_add_tcase(suite, tcase_equal);

  TCase *tcase_sum = tcase_create("SUM");
  tcase_add_test(tcase_sum, sum_1);
  tcase_add_test(tcase_sum, sum_2);
  tcase_add_test(tcase_sum, sum_3);
  tcase_add_test(tcase_sum, sum_4);
  tcase_add_test(tcase_sum, sum_5);
  tcase_add_test(tcase_sum, sum_6);
  tcase_add_test(tcase_sum, sum_7);
  suite_add_tcase(suite, tcase_sum);

  TCase *tcase_sub = tcase_create("SUB");
  tcase_add_test(tcase_sub, sub_1);
  tcase_add_test(tcase_sub, sub_2);
  tcase_add_test(tcase_sub, sub_3);
  tcase_add_test(tcase_sub, sub_4);
  tcase_add_test(tcase_sub, sub_5);
  tcase_add_test(tcase_sub, sub_6);
  tcase_add_test(tcase_sub, sub_7);
  suite_add_tcase(suite, tcase_sub);

  TCase *tcase_multi_num = tcase_create("MULTI_NUM");
  tcase_add_test(tcase_multi_num, multi_num_1);
  tcase_add_test(tcase_multi_num, multi_num_2);
  tcase_add_test(tcase_multi_num, multi_num_3);
  tcase_add_test(tcase_multi_num, multi_num_4);
  suite_add_tcase(suite, tcase_multi_num);

  TCase *tcase_transpose = tcase_create("TRANSPOSE");
  tcase_add_test(tcase_transpose, transpose_1);
  tcase_add_test(tcase_transpose, transpose_2);
  tcase_add_test(tcase_transpose, transpose_3);
  tcase_add_test(tcase_transpose, transpose_4);
  tcase_add_test(tcase_transpose, transpose_5);
  suite_add_tcase(suite, tcase_transpose);

  TCase *tcase_multi_mat = tcase_create("MULTI_MAT");
  tcase_add_test(tcase_multi_mat, multi_mat_1);
  tcase_add_test(tcase_multi_mat, multi_mat_2);
  tcase_add_test(tcase_multi_mat, multi_mat_3);
  tcase_add_test(tcase_multi_mat, multi_mat_4);
  tcase_add_test(tcase_multi_mat, multi_mat_5);
  tcase_add_test(tcase_multi_mat, multi_mat_6);
  suite_add_tcase(suite, tcase_multi_mat);

  TCase *tcase_deter = tcase_create("DETERMINANT");
  tcase_add_test(tcase_deter, deter_1);
  tcase_add_test(tcase_deter, deter_2);
  tcase_add_test(tcase_deter, deter_3);
  tcase_add_test(tcase_deter, deter_4);
  tcase_add_test(tcase_deter, deter_5);
  tcase_add_test(tcase_deter, deter_6);
  tcase_add_test(tcase_deter, deter_7);
  tcase_add_test(tcase_deter, deter_8);
  suite_add_tcase(suite, tcase_deter);

  TCase *tcase_complements = tcase_create("COMPLEMENTS");
  tcase_add_test(tcase_complements, complements_1);
  tcase_add_test(tcase_complements, complements_2);
  tcase_add_test(tcase_complements, complements_3);
  tcase_add_test(tcase_complements, complements_4);
  tcase_add_test(tcase_complements, complements_5);
  suite_add_tcase(suite, tcase_complements);

  TCase *tcase_inverse = tcase_create("INVERSE");
  tcase_add_test(tcase_inverse, inverse_1);
  tcase_add_test(tcase_inverse, inverse_2);
  tcase_add_test(tcase_inverse, inverse_3);
  tcase_add_test(tcase_inverse, inverse_4);
  tcase_add_test(tcase_inverse, inverse_5);
  tcase_add_test(tcase_inverse, inverse_6);
  suite_add_tcase(suite, tcase_inverse);
  return suite;
}

int main() {
  int count;
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}