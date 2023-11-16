#include "s21_matrix_test.h"

START_TEST(test_sum_matrix_valid) {
  matrix_t A, B, result, check_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &check_result);

  A.matrix[0][0] = 134564.99999991;
  A.matrix[0][1] = 24;
  A.matrix[1][0] = -322;
  A.matrix[1][1] = 444;

  B.matrix[0][0] = 134564.99996999;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3412;
  B.matrix[1][1] = 2224;

  check_result.matrix[0][0] = A.matrix[0][0] + B.matrix[0][0];
  check_result.matrix[0][1] = A.matrix[0][1] + B.matrix[0][1];
  check_result.matrix[1][0] = A.matrix[1][0] + B.matrix[1][0];
  check_result.matrix[1][1] = A.matrix[1][1] + B.matrix[1][1];

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &check_result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_result);
}
END_TEST

START_TEST(test_sum_matrix_invalid_A) {
  matrix_t A, B, result;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sum_matrix_invalid_B) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(-2, 66, &B);
  s21_create_matrix(2, 2, &result);

  int r = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sum_matrix_different_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(2, 2, &result);

  int r = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sum_matrix_valid_empty_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  s21_create_matrix(0, 0, &result);

  int r = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(sum_test_1) {
  int rows1 = 2, cols1 = 3;
  int rows2 = 2, cols2 = 3;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  s21_create_matrix(rows2, cols2, &result);
  A.matrix[0][0] = 695.0;
  A.matrix[0][1] = 930.0;
  A.matrix[0][2] = 363.0;
  A.matrix[1][0] = -60.0;
  A.matrix[1][1] = 842.0;
  A.matrix[1][2] = -291.0;
  B.matrix[0][0] = -61.0;
  B.matrix[0][1] = -91.0;
  B.matrix[0][2] = -94.0;
  B.matrix[1][0] = -10.0;
  B.matrix[1][1] = 17.0;
  B.matrix[1][2] = 71.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 634.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 839.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 269.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -70.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 859.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], -220.0, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *sum_matrix_suite(void) {
  Suite *s = suite_create("sum_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sum_matrix_valid);
  tcase_add_test(tc, test_sum_matrix_invalid_A);
  tcase_add_test(tc, test_sum_matrix_invalid_B);
  tcase_add_test(tc, test_sum_matrix_different_sizes);
  tcase_add_loop_test(tc, test_sum_matrix_valid_empty_matrix, 1, 10);
  tcase_add_test(tc, sum_test_1);

  suite_add_tcase(s, tc);

  return s;
}