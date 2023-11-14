#include "s21_matrix_test.h"

START_TEST(test_inverse_1) {
  matrix_t origin_1, result_matrix;
  int result = s21_create_matrix(3, 3, &origin_1);
  ck_assert_int_eq(result, 0);

  origin_1.matrix[0][0] = 2;
  origin_1.matrix[0][1] = 5;
  origin_1.matrix[0][2] = 7;

  origin_1.matrix[1][0] = 6;
  origin_1.matrix[1][1] = 3;
  origin_1.matrix[1][2] = 4;

  origin_1.matrix[2][0] = 5;
  origin_1.matrix[2][1] = -2;
  origin_1.matrix[2][2] = -3;

  result = s21_inverse_matrix(&origin_1, &result_matrix);
  ck_assert_int_eq(result, 0);

  ck_assert_double_eq(result_matrix.matrix[0][0], 1);
  ck_assert_double_eq(result_matrix.matrix[0][1], -1);
  ck_assert_double_eq(result_matrix.matrix[0][2], 1);
  ck_assert_double_eq(result_matrix.matrix[1][0], -38);
  ck_assert_double_eq(result_matrix.matrix[1][1], 41);
  ck_assert_double_eq(result_matrix.matrix[1][2], -34);
  ck_assert_double_eq(result_matrix.matrix[2][0], 27);
  ck_assert_double_eq(result_matrix.matrix[2][1], -29);
  ck_assert_double_eq(result_matrix.matrix[2][2], 24);

  s21_remove_matrix(&origin_1);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_inverse_2) {
  matrix_t origin_1, result_matrix;
  int result = s21_create_matrix(3, 3, &origin_1);
  ck_assert_int_eq(result, 0);

  origin_1.matrix[0][0] = 1;
  origin_1.matrix[0][1] = 2;
  origin_1.matrix[0][2] = 3;

  origin_1.matrix[1][0] = 4;
  origin_1.matrix[1][1] = 5;
  origin_1.matrix[1][2] = 6;

  origin_1.matrix[2][0] = 7;
  origin_1.matrix[2][1] = 8;
  origin_1.matrix[2][2] = 9;

  result = s21_inverse_matrix(&origin_1, &result_matrix);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&origin_1);
}

START_TEST(test_inverse_3) {
  matrix_t origin_1, result_matrix;
  int result = s21_create_matrix(2, 3, &origin_1);
  ck_assert_int_eq(result, 0);

  result = s21_inverse_matrix(&origin_1, &result_matrix);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&origin_1);
}

START_TEST(test_inverse_4) {
  matrix_t result_matrix;

  int result = s21_inverse_matrix(NULL, &result_matrix);
  ck_assert_int_eq(result, 1);
}

START_TEST(test_inverse_5) {
  matrix_t origin, result_matrix;
  int result = s21_create_matrix(2, 2, &origin);
  ck_assert_int_eq(result, 0);

  origin.matrix[0][0] = 3;
  origin.matrix[0][1] = 4;
  origin.matrix[1][0] = 5;
  origin.matrix[1][1] = 7;

  result = s21_inverse_matrix(&origin, &result_matrix);
  ck_assert_int_eq(result, 0);

  ck_assert_double_eq(result_matrix.matrix[0][0], 7);
  ck_assert_double_eq(result_matrix.matrix[0][1], -4);
  ck_assert_double_eq(result_matrix.matrix[1][0], -5);
  ck_assert_double_eq(result_matrix.matrix[1][1], 3);

  s21_remove_matrix(&origin);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_inverse_6) {
  matrix_t origin, result_matrix;
  int result = s21_create_matrix(1, 1, &origin);
  ck_assert_int_eq(result, 0);

  origin.matrix[0][0] = 1;

  result = s21_inverse_matrix(&origin, &result_matrix);
  ck_assert_int_eq(result, 0);

  ck_assert_double_eq(result_matrix.matrix[0][0], 1);

  s21_remove_matrix(&origin);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 5;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    s21_remove_matrix(&m);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 4, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_normal) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int codec1, codec2;
  codec1 = s21_create_matrix(3, 3, &m);
  if (!codec1) codec2 = s21_create_matrix(3, 3, &expected);

  if (!codec1 && !codec2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *inverse_suite(void) {
  Suite *s;
  TCase *tc_core = tcase_create("core");

  s = suite_create("inverse_matrix");
  tcase_add_test(tc_core, test_inverse_1);
  tcase_add_test(tc_core, test_inverse_2);
  tcase_add_test(tc_core, test_inverse_3);
  tcase_add_test(tc_core, test_inverse_4);
  tcase_add_test(tc_core, test_inverse_5);
  tcase_add_test(tc_core, test_inverse_6);

  tcase_add_test(tc_core, test_normal);
  tcase_add_test(tc_core, test_not_sqare);
  tcase_add_test(tc_core, test_zero_det);
  tcase_add_test(tc_core, test_incorrect);
  tcase_add_test(tc_core, test_one_by_one);
  suite_add_tcase(s, tc_core);

  return s;
}