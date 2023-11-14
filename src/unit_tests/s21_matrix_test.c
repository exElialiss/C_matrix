#include "s21_matrix_test.h"

void run_tests(void) {
  Suite *list_cases[] = {
      suite_create_matrix(),    remove_matrix_suite(),    eq_matrix_suite(),
      sum_matrix_suite(),       sub_matrix_suite(),       mult_number_test(),
      mult_matrix_test(),       suite_transpose_matrix(), suite_determinant(),
      suite_calc_complements(), inverse_suite(),          NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("%s%d%s", "TEST ", counter_testcase, "\n");
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_tests();
  return 0;
}
