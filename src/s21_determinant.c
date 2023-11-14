#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int err = OK;
  if (A == NULL || A->matrix == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0) {
    err = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    err = CALCULATION_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
      err = OK;
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      err = OK;
    } else {
      *result = 0;
      for (int i = 0; i < A->rows; ++i) {
        matrix_t minor_matrix;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix);
        for (int j = 1; j < A->rows; ++j) {
          for (int k = 0, l = 0; k < A->columns; ++k) {
            if (k == i) continue;
            minor_matrix.matrix[j - 1][l++] = A->matrix[j][k];
          }
        }
        double minor_matrix_det = 0;
        int error = s21_determinant(&minor_matrix, &minor_matrix_det);
        s21_remove_matrix(&minor_matrix);
        if (error != 0) {
          err = CALCULATION_ERROR;
          break;
        }
        if (i % 2 == 0) {
          *result += A->matrix[0][i] * minor_matrix_det;
        } else {
          *result -= A->matrix[0][i] * minor_matrix_det;
        }
      }
    }
  }
  return err;
}