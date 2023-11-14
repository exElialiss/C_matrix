#include "s21_matrix.h"

void matrix_null(matrix_t *A) {
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}