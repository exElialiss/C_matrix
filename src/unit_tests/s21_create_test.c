#include "s21_matrix_test.h"

START_TEST(s21_create_matrix_test_1) {
  int rows = 4, columns = 4;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t A;
  int result = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(result, INVALID_MATRIX);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(s21_create_matrix_test_3) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INVALID_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_4) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INVALID_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_5) {
  matrix_t result;
  int rows = 2, columns = 10;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(0, exit_code);
}
END_TEST

START_TEST(s21_create_matrix_test_6) {
  matrix_t result;
  int rows = 2, columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(0, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_matrix_test_7) {
  matrix_t result = {0};
  int rows = 0;
  int columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(1, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_matrix_test_8) {
  matrix_t result = {0};
  int rows = 0, columns = 0;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(s21_create_matrix_test_9) {
  matrix_t result = {0};
  int rows = 4, columns = -7;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(s21_create_matrix_test_10) {
  ck_assert_int_eq(1, s21_create_matrix(0, 0, NULL));
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, s21_create_matrix_test_1);
  tcase_add_test(tc, s21_create_matrix_test_2);
  tcase_add_test(tc, s21_create_matrix_test_3);
  tcase_add_test(tc, s21_create_matrix_test_4);
  tcase_add_test(tc, s21_create_matrix_test_5);
  tcase_add_test(tc, s21_create_matrix_test_6);
  tcase_add_test(tc, s21_create_matrix_test_7);
  tcase_add_test(tc, s21_create_matrix_test_8);
  tcase_add_test(tc, s21_create_matrix_test_9);
  tcase_add_test(tc, s21_create_matrix_test_10);

  suite_add_tcase(s, tc);
  return s;
}
