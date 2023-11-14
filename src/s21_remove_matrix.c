#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != 0) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != 0) {
        free(A->matrix[i]);
        A->matrix[i] = 0;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}