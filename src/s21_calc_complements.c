#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!A || A->matrix == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows < 1 || A->columns < 1) {
    err = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    err = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = 1;
    } else {
      matrix_t B;
      s21_create_matrix(A->rows - 1, A->columns - 1, &B);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          double det = 0;
          for (int b_row = 0; b_row < B.rows; b_row++) {
            for (int b_col = 0; b_col < B.columns; b_col++) {
              if (b_col < j && b_row < i) {
                B.matrix[b_row][b_col] = A->matrix[b_row][b_col];
              }
              if (b_col >= j && b_row >= i) {
                B.matrix[b_row][b_col] = A->matrix[b_row + 1][b_col + 1];
              }
              if (b_col < j && b_row >= i) {
                B.matrix[b_row][b_col] = A->matrix[b_row + 1][b_col];
              }
              if (b_col >= j && b_row < i) {
                B.matrix[b_row][b_col] = A->matrix[b_row][b_col + 1];
              }
            }
          }
          s21_determinant(&B, &det);
          result->matrix[i][j] = det * pow(-1.0, i + j);
        }
      }
      s21_remove_matrix(&B);
    }
  }
  return err;
}