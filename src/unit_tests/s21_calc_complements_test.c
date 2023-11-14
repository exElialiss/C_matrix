#include "s21_matrix_test.h"

START_TEST(test_1) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(0, 0, &m);
  if (codec) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, 1);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_2) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, INVALID_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_3) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(0, 0, &m);
  if (codec == OK) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, 1);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_4) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &expected);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;

  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;

  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_5) {
  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;

  m.matrix[1][0] = 2;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 6;

  m.matrix[2][0] = 3;
  m.matrix[2][1] = 6;
  m.matrix[2][2] = 9;

  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&result);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(complements_0) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  matrix_t result;
  int rowA = 3, colA = 3;
  s21_create_matrix(rowA, colA, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  s21_calc_complements(&A, &result);
  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 10);
  ck_assert_double_eq(result.matrix[0][2], -20);
  ck_assert_double_eq(result.matrix[1][0], 4);
  ck_assert_double_eq(result.matrix[1][1], -14);
  ck_assert_double_eq(result.matrix[1][2], 8);
  ck_assert_double_eq(result.matrix[2][0], -8);
  ck_assert_double_eq(result.matrix[2][1], -2);
  ck_assert_double_eq(result.matrix[2][2], 4);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(complements_1) {
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), 1);
}
END_TEST

START_TEST(complements_2) {
  matrix_t A;
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  ck_assert_int_eq(s21_calc_complements(NULL, &A), 1);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t a = {0};
  matrix_t res = {0};
  matrix_t m = {0};
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &res);

  res.matrix[0][0] = 0;
  res.matrix[0][1] = 10;
  res.matrix[0][2] = -20;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = -14;
  res.matrix[1][2] = 8;
  res.matrix[2][0] = -8;
  res.matrix[2][1] = -2;
  res.matrix[2][2] = 4;
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;
  s21_calc_complements(&a, &m);
  ck_assert_int_eq(s21_eq_matrix(&res, &m), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  s21_calc_complements(&A, &B);
  C.matrix[0][0] = 0.0;
  C.matrix[0][1] = 10.0;
  C.matrix[0][2] = -20.0;
  C.matrix[1][0] = 4.0;
  C.matrix[1][1] = -14.0;
  C.matrix[1][2] = 8.0;
  C.matrix[2][0] = -8.0;
  C.matrix[2][1] = -2.0;
  C.matrix[2][2] = 4.0;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(empty) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(size_mismatch) {
  matrix_t a = {0};
  matrix_t b = {0};
  s21_create_matrix(1, 2, &a);
  ck_assert_int_eq(s21_calc_complements(&a, &b), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(complements) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  s21_calc_complements(&m, &res);

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_n1) {
  matrix_t A;
  matrix_t res;

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = -123;
  int code = s21_calc_complements(&A, &res);

  double fact = res.matrix[0][0];

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(fact, 1);
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t A, result;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j / 3.3;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A, result;
  int rows = 10, columns = 7;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A, result;
  A.matrix = NULL;
  A.rows = 0;
  A.columns = 0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), 1);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t A, result, result_true;
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &result_true);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  result_true.matrix[0][0] = 0;
  result_true.matrix[0][1] = 10;
  result_true.matrix[0][2] = -20;
  result_true.matrix[1][0] = 4;
  result_true.matrix[1][1] = -14;
  result_true.matrix[1][2] = 8;
  result_true.matrix[2][0] = -8;
  result_true.matrix[2][1] = -2;
  result_true.matrix[2][2] = 4;
  s21_calc_complements(&A, &result);
  ck_assert_int_eq(s21_eq_matrix(&result, &result_true), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_true);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, complements_0);
  tcase_add_test(tc, complements_1);
  tcase_add_test(tc, complements_2);
  tcase_add_test(tc, s21_calc_complements_1);
  tcase_add_test(tc, s21_calc_complements_2);
  tcase_add_test(tc, complements);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, size_mismatch);
  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_3);
  tcase_add_test(tc, calc_complements_4);
  tcase_add_test(tc, calc_complements_5);
  tcase_add_test(tc, calc_complements_n1);

  suite_add_tcase(s, tc);
  return s;
}
