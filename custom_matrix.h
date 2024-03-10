#ifndef SRC_CUSTOM_MATRIX_H_
#define SRC_CUSTOM_MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define EPSILON 1e-7

typedef enum { OK, MATRIX_ERROR, ARITHMETIC_ERROR } StatusCode;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// matrix_core.c
int custom_create_matrix(int rows, int columns, matrix_t *result);
void custom_remove_matrix(matrix_t *A);
int custom_eq_matrix(matrix_t *A, matrix_t *B);
int custom_transpose(matrix_t *A, matrix_t *result);
int custom_inverse_matrix(matrix_t *A, matrix_t *result);

// matrix_arithmetic.c
int custom_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_mult_number(matrix_t *A, double number, matrix_t *result);
int custom_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_calc_complements(matrix_t *A, matrix_t *result);
int custom_determinant(matrix_t *A, double *result);

// matrix_support.c
StatusCode calculate_determinant(matrix_t *A, double *result);
StatusCode calculate_minor(matrix_t *orig, int dodge_row, int dodge_col,
                           double *result);
StatusCode fill_complements(matrix_t *A, matrix_t *result);
StatusCode custom_prepare_complements_matrix(matrix_t *A,
                                             matrix_t *complementsT);
void custom_apply_inverse_formula(matrix_t *complementsT, double determinant,
                                  matrix_t *result);

#endif /* SRC_CUSTOM_MATRIX_H_ */
