#include "s21_matrix_test.h"

START_TEST(test_remove_matrix_1) {
  matrix_t A = {NULL, 0, 0};
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_4) {
  matrix_t A;
  s21_create_matrix(1000, 1000, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_5) {
  matrix_t A;
  s21_create_matrix(18, 29, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_6) {
  matrix_t A = {NULL, -1, 5};
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_7) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.rows = -1;
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_8) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.columns = -1;
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_9) {
  matrix_t A = {NULL, 2, 2};
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_10) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[1] = NULL;
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

Suite *remove_matrix_suite(void) {
  Suite *s = suite_create("remove_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_remove_matrix_1);
  tcase_add_test(tc, test_remove_matrix_2);
  tcase_add_test(tc, test_remove_matrix_3);
  tcase_add_test(tc, test_remove_matrix_4);
  tcase_add_test(tc, test_remove_matrix_5);
  tcase_add_test(tc, test_remove_matrix_6);
  tcase_add_test(tc, test_remove_matrix_7);
  tcase_add_test(tc, test_remove_matrix_8);
  tcase_add_test(tc, test_remove_matrix_9);
  tcase_add_test(tc, test_remove_matrix_10);

  suite_add_tcase(s, tc);

  return s;
}