#include "s21_matrix_test.h"

START_TEST(test_mult_matrix_1) {
  matrix_t origin_1, origin_2, result_matrix = {0};

  s21_create_matrix(2, 3, &origin_1);
  s21_create_matrix(3, 2, &origin_2);

  origin_2.matrix[0][0] = 1;
  origin_2.matrix[0][1] = 4;
  origin_2.matrix[1][0] = 2;
  origin_2.matrix[1][1] = 5;
  origin_2.matrix[2][0] = 3;
  origin_2.matrix[2][1] = 6;

  origin_1.matrix[0][0] = 1;
  origin_1.matrix[0][1] = -1;
  origin_1.matrix[0][2] = 1;
  origin_1.matrix[1][0] = 2;
  origin_1.matrix[1][1] = 3;
  origin_1.matrix[1][2] = 4;

  int result = s21_mult_matrix(&origin_1, &origin_2, &result_matrix);
  ck_assert_int_eq(result, 0);

  ck_assert_double_eq(result_matrix.matrix[0][0], 2);
  ck_assert_double_eq(result_matrix.matrix[1][1], 47);

  s21_remove_matrix(&origin_1);
  s21_remove_matrix(&origin_2);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_mult_matrix_2) {
  matrix_t origin_1, origin_2, result_matrix;
  int result = s21_create_matrix(2, 3, &origin_1);
  ck_assert_int_eq(result, 0);
  result = s21_create_matrix(4, 1, &origin_2);
  ck_assert_int_eq(result, 0);

  origin_1.matrix[0][0] = 1;
  origin_1.matrix[0][1] = 2;
  origin_1.matrix[0][2] = 2;
  origin_1.matrix[1][0] = 3;
  origin_1.matrix[1][1] = 7;
  origin_1.matrix[1][2] = 0.1;

  result = s21_mult_matrix(&origin_1, &origin_2, &result_matrix);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&origin_1);
  s21_remove_matrix(&origin_2);
}

START_TEST(test_mult_matrix_3) {
  matrix_t origin_1, result_matrix;
  int result = s21_create_matrix(2, 3, &origin_1);
  ck_assert_int_eq(result, 0);

  origin_1.matrix[0][0] = 1;
  origin_1.matrix[0][1] = 2;
  origin_1.matrix[0][2] = 2;
  origin_1.matrix[1][0] = 3;
  origin_1.matrix[1][1] = 7;
  origin_1.matrix[1][2] = 0.1;

  result = s21_mult_matrix(&origin_1, NULL, &result_matrix);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&origin_1);
}

START_TEST(test_mult_matrix_4) {
  matrix_t origin_1, origin_2, result_matrix;
  int result = s21_create_matrix(2, 3, &origin_1);
  ck_assert_int_eq(result, 0);

  result = s21_create_matrix(3, 3, &origin_2);
  ck_assert_int_eq(result, 0);

  origin_2.rows = -3;

  origin_1.matrix[0][0] = 1;
  origin_1.matrix[0][1] = 2;
  origin_1.matrix[0][2] = 2;
  origin_1.matrix[1][0] = 3;
  origin_1.matrix[1][1] = 7;
  origin_1.matrix[1][2] = 0.1;

  result = s21_mult_matrix(&origin_1, NULL, &result_matrix);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&origin_1);
  origin_2.rows = 3;
  s21_remove_matrix(&origin_2);
}

START_TEST(mulM_0) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  matrix_t B;
  B.rows = 0;
  B.columns = 0;
  B.matrix = NULL;
  matrix_t result;
  int rowA = 3, rowB = 2, colA = 2, colB = 3;
  s21_create_matrix(rowA, colA, &A);
  s21_create_matrix(rowB, colB, &B);
  int t = 1;
  for (int i = 0; i < A.columns; i++)
    for (int j = 0; j < A.rows; j++) A.matrix[j][i] = t++;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  s21_mult_matrix(&A, &B, &result);
  ck_assert_double_eq(result.matrix[0][0], 9);
  ck_assert_double_eq(result.matrix[0][1], 11);
  ck_assert_double_eq(result.matrix[0][2], 17);
  ck_assert_double_eq(result.matrix[1][0], 12);
  ck_assert_double_eq(result.matrix[1][1], 13);
  ck_assert_double_eq(result.matrix[1][2], 22);
  ck_assert_double_eq(result.matrix[2][0], 15);
  ck_assert_double_eq(result.matrix[2][1], 15);
  ck_assert_double_eq(result.matrix[2][2], 27);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix3) {
  matrix_t m = {0};
  int rows = 2;
  int cols = 3;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  int rows1 = 4;
  int cols1 = 5;
  s21_create_matrix(rows1, cols1, &mtx);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), CALCULATION_ERROR);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mul_matrix_1_err) {
  int rows = 2, columns = 3, rows2 = 2, columns2 = 3;
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mul_matrix_2_err) {
  int rows = 2, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_mult_matrix(&A, NULL, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_1) {
  int rows1 = 2, cols1 = 3;
  int rows2 = 3, cols2 = 2;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -53.0;
  A.matrix[0][1] = -18.0;
  A.matrix[0][2] = -40.0;
  A.matrix[1][0] = -28.0;
  A.matrix[1][1] = 16.0;
  A.matrix[1][2] = 60.0;
  B.matrix[0][0] = -7.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = -7.0;
  B.matrix[1][1] = -4.0;
  B.matrix[2][0] = -3.0;
  B.matrix[2][1] = -2.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 617.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -296.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_2) {
  int rows1 = 2, cols1 = 2;
  int rows2 = 2, cols2 = 2;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 2.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = -1.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *mult_matrix_test(void) {
  Suite *s = suite_create("mult_matrix_test");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_mult_matrix_1);
  tcase_add_test(tc, test_mult_matrix_2);
  tcase_add_test(tc, test_mult_matrix_3);
  tcase_add_test(tc, test_mult_matrix_4);
  tcase_add_test(tc, mulM_0);
  tcase_add_test(tc, mult_matrix3);
  tcase_add_test(tc, s21_mul_matrix_1_err);
  tcase_add_test(tc, s21_mul_matrix_2_err);
  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);

  suite_add_tcase(s, tc);

  return s;
}