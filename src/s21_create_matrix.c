#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    if (result != NULL) {
      matrix_null(result);
    }
    err = INVALID_MATRIX;
  } else {
    double **matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++) {
      matrix[i] = (double *)malloc(columns * sizeof(double));
      if (matrix[i] == NULL) {
        for (int j = 0; j < i; j++) {
          free(matrix[j]);
        }
        free(matrix);
        matrix_null(result);
        err = CALCULATION_ERROR;
        break;
      }
    }
    if (err == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          matrix[i][j] = 0.0;
        }
      }
      result->matrix = matrix;
      result->rows = rows;
      result->columns = columns;
    }
  }

  return err;
}
