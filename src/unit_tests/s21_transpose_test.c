#include "s21_matrix_test.h"

START_TEST(test_transpose_1) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  matrix_t result;
  int rowA = 10, colA = 3;
  s21_create_matrix(rowA, colA, &A);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) A.matrix[i][j] = 25;
  A.matrix[0][0] = -10;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  s21_transpose(&A, &result);
  ck_assert_double_eq(result.matrix[0][0], -10);
  ck_assert_double_eq(result.matrix[1][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 2);
  for (int i = 0; i < A.columns; i++) {
    for (int j = 0; j < A.rows; j++) {
      if (j + i > 1) ck_assert_double_eq(result.matrix[i][j], 25);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_2) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, NULL), 1);
}
END_TEST

START_TEST(test_transpose_3) {
  matrix_t A, B;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  B.rows = 0;
  B.columns = 0;
  B.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, &B), 1);
}
END_TEST

START_TEST(test_transpose_4) {
  matrix_t A, B;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  B.rows = 0;
  B.columns = 0;
  B.matrix = NULL;
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_transpose(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_5) {
  matrix_t A, B;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  B.rows = 0;
  B.columns = 0;
  B.matrix = NULL;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_6) {
  matrix_t A, B;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  B.rows = 0;
  B.columns = 0;
  B.matrix = NULL;
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_7) {
  matrix_t A = {0}, result = {0};
  int rows = 3, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_8) {
  matrix_t A = {0}, result = {0};
  int rows = 31, columns = 52;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_10) {
  matrix_t A = {0}, result = {0};
  int rows = 51, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_9) {
  matrix_t A = {0}, result = {0};
  A.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, &result), 1);
}
END_TEST

START_TEST(test_transpose_11) {
  matrix_t A = {0}, result = {0}, result_tmp = {0};
  int rows = 3, columns = 2;
  int sum = 0;
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_create_matrix(columns, rows, &result_tmp);
  result_tmp.matrix[0][0] = 1;
  result_tmp.matrix[0][1] = 2;
  result_tmp.matrix[0][2] = 3;
  result_tmp.matrix[1][0] = 4;
  result_tmp.matrix[1][1] = 5;
  result_tmp.matrix[1][2] = 6;
  s21_transpose(&A, &result);
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      if (fabs(result_tmp.matrix[i][j] - result.matrix[i][j]) > 1e-8) {
        sum++;
      }
    }
  }
  ck_assert_int_eq(sum, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_tmp);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("suite_transpose_matrix");
  TCase *tc = tcase_create("case_transpose_matrix");

  tcase_add_test(tc, test_transpose_1);
  tcase_add_test(tc, test_transpose_2);
  tcase_add_test(tc, test_transpose_3);
  tcase_add_test(tc, test_transpose_4);
  tcase_add_test(tc, test_transpose_5);
  tcase_add_test(tc, test_transpose_6);
  tcase_add_test(tc, test_transpose_7);
  tcase_add_test(tc, test_transpose_8);
  tcase_add_test(tc, test_transpose_9);
  tcase_add_test(tc, test_transpose_10);
  tcase_add_test(tc, test_transpose_11);

  suite_add_tcase(s, tc);
  return s;
}