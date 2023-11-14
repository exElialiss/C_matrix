#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!A || A->matrix == NULL)
    err = INVALID_MATRIX;
  else if (A->rows < 1 || A->columns < 1)
    err = INVALID_MATRIX;
  else if (A->rows != A->columns)
    err = CALCULATION_ERROR;
  else {
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0)
      err = CALCULATION_ERROR;
    else if (A->rows == 1) {
      s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else {
      if (s21_calc_complements(A, result) == 2)
        err = CALCULATION_ERROR;
      else {
        matrix_t result_t;
        s21_transpose(result, &result_t);
        s21_remove_matrix(result);
        s21_mult_number(&result_t, 1.0 / det, result);
        s21_remove_matrix(&result_t);
      }
    }
  }
  return err;
}