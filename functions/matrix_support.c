#include "../custom_matrix.h"

StatusCode calculate_determinant(matrix_t *A, double *result) {
  StatusCode status = OK;
  *result = 0;
  for (int j = 0; j < A->columns; j++) {
    matrix_t minorMatrix;
    status = custom_create_matrix(A->rows - 1, A->columns - 1, &minorMatrix);
    if (status != OK) {
      *result = 0;
      break;
    }
    for (int row = 1; row < A->rows; row++) {
      for (int col = 0, minorCol = 0; col < A->columns; col++) {
        if (col != j) {
          minorMatrix.matrix[row - 1][minorCol++] = A->matrix[row][col];
        }
      }
    }
    double minorResult;
    custom_determinant(&minorMatrix, &minorResult);
    *result += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minorResult;
    custom_remove_matrix(&minorMatrix);
  }
  return status;
}

StatusCode calculate_minor(matrix_t *orig, int dodge_row, int dodge_col,
                           double *result) {
  StatusCode status = OK;
  if (orig->rows <= 1) {
    return ARITHMETIC_ERROR;
  }

  matrix_t minorMatrix;
  status = custom_create_matrix(orig->rows - 1, orig->columns - 1, &minorMatrix);
  if (status == OK) {
    int di = 0, dj = 0;
    for (size_t i = 0; i < minorMatrix.rows; i++) {
      if (i == dodge_row) di = 1;
      dj = 0;
      for (size_t j = 0; j < minorMatrix.columns; j++) {
        if (j == dodge_col) dj = 1;
        minorMatrix.matrix[i][j] = orig->matrix[i + di][j + dj];
      }
    }

    status = custom_determinant(&minorMatrix, result);
    custom_remove_matrix(&minorMatrix);
  } else {
    *result = 0;
    status = MATRIX_ERROR;
  }
  return status;
}

StatusCode fill_complements(matrix_t *A, matrix_t *result) {
  StatusCode status = OK;
  for (size_t i = 0; i < A->rows; i++) {
    for (size_t j = 0; j < A->columns; j++) {
      double answer = 0;
      status = calculate_minor(A, i, j, &answer);
      if (status != OK) {
        return status;
      }
      result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * answer;
    }
  }
  return status;
}

StatusCode custom_prepare_complements_matrix(matrix_t *A, matrix_t *complementsT) {
  StatusCode status = MATRIX_ERROR;
  matrix_t complements;
  if (custom_calc_complements(A, &complements) == OK) {
    if (custom_transpose(&complements, complementsT) == OK) {
      status = OK;
    }
    custom_remove_matrix(&complements);
  }
  return status;
}

void custom_apply_inverse_formula(matrix_t *complementsT, double determinant,
                               matrix_t *result) {
  for (size_t i = 0; i < complementsT->rows; i++) {
    for (size_t j = 0; j < complementsT->columns; j++) {
      result->matrix[i][j] = (1.0 / determinant) * complementsT->matrix[i][j];
    }
  }
}