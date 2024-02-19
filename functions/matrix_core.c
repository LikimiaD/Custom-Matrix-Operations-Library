#include "../custom_matrix.h"

int custom_create_matrix(int rows, int columns, matrix_t *result) {
  StatusCode status = OK;
  if (result && rows > 0 && columns > 0) {
    result->matrix = (double **)malloc(sizeof(double *) * rows);
    result->rows = rows;
    result->columns = columns;
    if (result->matrix != NULL) {
      for (size_t i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(sizeof(double) * columns);
        if (result->matrix[i] == NULL) {
          for (size_t j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          status = MATRIX_ERROR;
          break;
        }
      }
    } else {
      status = MATRIX_ERROR;
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
void custom_remove_matrix(matrix_t *A) {
  if (A) {
    for (size_t row = 0; row < A->rows; row++) {
      free(A->matrix[row]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}
int custom_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!A || !B || (A->rows != B->rows) || (A->columns != B->columns)) {
    result = FAILURE;
  } else {
    if (A->rows == 1 && B->rows == 1) {
      result =
          fabs(A->matrix[0][0] - B->matrix[0][0]) < 1e-07 ? SUCCESS : FAILURE;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
            result = FAILURE;
            break;
          }
        }
      }
    }
  }
  return result;
}
int custom_transpose(matrix_t *A, matrix_t *result) {
  StatusCode status = OK;
  if (A && A->rows > 0 && A->columns > 0) {
    status = custom_create_matrix(A->columns, A->rows, result);
    if (status == OK) {
      for (size_t i = 0; i < A->rows; i++) {
        for (size_t j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    status = MATRIX_ERROR;
  }
  return status;
}
int custom_inverse_matrix(matrix_t *A, matrix_t *result) {
  StatusCode status = MATRIX_ERROR;
  double determinant = 0;
  if (A && A->rows == A->columns && custom_determinant(A, &determinant) == OK &&
      determinant != 0) {
    matrix_t complementsT;
    if (custom_prepare_complements_matrix(A, &complementsT) == OK) {
      if (custom_create_matrix(A->rows, A->columns, result) == OK) {
        custom_apply_inverse_formula(&complementsT, determinant, result);
        status = OK;
      }
      custom_remove_matrix(&complementsT);
    }
  } else if (A && A->rows > 0 && A->columns > 0) {
    status = ARITHMETIC_ERROR;
  }
  return status;
}