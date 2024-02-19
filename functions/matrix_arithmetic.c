#include "../custom_matrix.h"

int custom_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  StatusCode status = OK;
  if (A && B && A->rows > 0 && B->rows > 0 && A->columns > 0 &&
      B->columns > 0) {
    if ((A->columns == B->columns) && (B->rows == A->rows)) {
      status = custom_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (size_t i = 0; i < A->rows; i++) {
          for (size_t j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      status = ARITHMETIC_ERROR;
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
int custom_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  StatusCode status = OK;
  if (A && B && A->rows > 0 && B->rows > 0 && A->columns > 0 &&
      B->columns > 0) {
    if ((A->columns == B->columns) && (B->rows == A->rows)) {
      status = custom_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (size_t i = 0; i < A->rows; i++) {
          for (size_t j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      status = ARITHMETIC_ERROR;
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
int custom_mult_number(matrix_t *A, double number, matrix_t *result) {
  StatusCode status = OK;
  if (A && A->columns > 0 && A->rows > 0) {
    if (isnan(number) || isinf(number)) {
      status = ARITHMETIC_ERROR;
    } else {
      status = custom_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (size_t i = 0; i < A->rows; i++) {
          for (size_t j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
          }
        }
      }
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
int custom_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  StatusCode status = OK;
  if (A && B && A->columns > 0 && A->rows > 0 && B->columns > 0 &&
      B->rows > 0) {
    if (A->columns == B->rows) {
      status = custom_create_matrix(A->rows, B->columns, result);
      if (status == OK) {
        for (size_t i = 0; i < A->rows; i++) {
          for (size_t j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (size_t k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      status = ARITHMETIC_ERROR;
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
int custom_determinant(matrix_t *A, double *result) {
  StatusCode status = OK;
  if (!(A && result && A->rows > 0 && A->columns > 0)) {
    status = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    status = ARITHMETIC_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    status = calculate_determinant(A, result);
  }
  return status;
}
int custom_calc_complements(matrix_t *A, matrix_t *result) {
  StatusCode status = OK;
  if (!(A && A->rows == A->columns && A->rows >= 1)) {
    status =
        (A && A->rows > 0 && A->columns > 0) ? ARITHMETIC_ERROR : MATRIX_ERROR;
  } else if (A->rows == 1) {
    status = custom_create_matrix(1, 1, result);
    if (status == OK) {
      result->matrix[0][0] = 1;
    }
  } else {
    status = custom_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
      status = fill_complements(A, result);
      if (status != OK) {
        custom_remove_matrix(result);
      }
    }
  }
  return status;
}