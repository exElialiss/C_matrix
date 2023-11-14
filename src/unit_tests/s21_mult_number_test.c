#include "s21_matrix_test.h"

START_TEST(num_mul_test_0) {
  int rows1 = 2, cols1 = 3;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -58.0;
  A.matrix[0][1] = -50.0;
  A.matrix[0][2] = -66.0;
  A.matrix[1][0] = -94.0;
  A.matrix[1][1] = 95.0;
  A.matrix[1][2] = -67.0;
  int status = s21_mult_number(&A, 948.0939352882323, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -54989.448246717475, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -63522.29366431156, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_valid) {
  matrix_t A, result, check_result;
  double number = _i;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &check_result);

  A.matrix[0][0] = 134564.99999991;
  A.matrix[0][1] = 24;
  A.matrix[1][0] = -322;
  A.matrix[1][1] = 444;

  check_result.matrix[0][0] = A.matrix[0][0] * number;
  check_result.matrix[0][1] = A.matrix[0][1] * number;
  check_result.matrix[1][0] = A.matrix[1][0] * number;
  check_result.matrix[1][1] = A.matrix[1][1] * number;

  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &check_result), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check_result);
}
END_TEST

START_TEST(test_mult_number_invalid_A) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &result);

  double number = -2.995848;

  int r = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(r, 0);

  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}

START_TEST(test_mult_number_memory_error) {
  matrix_t A, result;
  s21_create_matrix(1000000000, 1000000000, &A);
  s21_create_matrix(1000000000, 1000000000, &result);

  double number = 2.0;

  int r = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(r, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

Suite *mult_number_test(void) {
  Suite *s = suite_create("mult_number_test");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, num_mul_test_0);
  tcase_add_loop_test(tc, test_mult_number_valid, 1, 8);
  tcase_add_test(tc, test_mult_number_invalid_A);
  tcase_add_test(tc, test_mult_number_memory_error);

  suite_add_tcase(s, tc);

  return s;
}