#include "s21_matrix_test.h"
START_TEST(test_sub_matrix_valid) {
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

  check_result.matrix[0][0] = A.matrix[0][0] - B.matrix[0][0];
  check_result.matrix[0][1] = A.matrix[0][1] - B.matrix[0][1];
  check_result.matrix[1][0] = A.matrix[1][0] - B.matrix[1][0];
  check_result.matrix[1][1] = A.matrix[1][1] - B.matrix[1][1];

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &check_result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_result);
}
END_TEST

START_TEST(test_sub_matrix_invalid_A) {
  matrix_t A, B, result;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sub_matrix_invalid_B) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(-2, 66, &B);
  s21_create_matrix(2, 2, &result);

  int r = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sub_matrix_diff_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(2, 2, &result);

  int r = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

START_TEST(test_sub_matrix_empty_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  s21_create_matrix(0, 0, &result);

  int r = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(r, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

Suite *sub_matrix_suite(void) {
  Suite *s = suite_create("sub_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sub_matrix_valid);
  tcase_add_test(tc, test_sub_matrix_invalid_A);
  tcase_add_test(tc, test_sub_matrix_invalid_B);
  tcase_add_test(tc, test_sub_matrix_diff_sizes);
  tcase_add_loop_test(tc, test_sub_matrix_empty_matrix, 1, 10);

  suite_add_tcase(s, tc);

  return s;
}