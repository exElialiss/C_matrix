#ifndef S21_TEST_MATRIX_H_
#define S21_TEST_MATRIX_H_

#include <check.h>
#include <stdlib.h>
#include <unistd.h>

#include "../s21_matrix.h"

Suite *suite_create_matrix(void);
Suite *remove_matrix_suite(void);
Suite *eq_matrix_suite(void);
Suite *sum_matrix_suite(void);
Suite *sub_matrix_suite(void);
Suite *mult_number_test(void);
Suite *mult_matrix_test(void);
Suite *suite_transpose_matrix(void);
Suite *suite_determinant(void);
Suite *suite_calc_complements(void);
Suite *inverse_suite(void);

void run_testcase(Suite *testcase);

#endif