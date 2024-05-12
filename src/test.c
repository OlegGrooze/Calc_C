#include <check.h>

#include "smartcalc.h"

START_TEST(DEPOSIT_CALCULATOR1) {
  long double depositAmount = 500;
  int period = 365;
  long double percent = 30;
  long double tax = 35;
  int frequency = 0;
  int capitalization = 0;
  long double payment = 0;
  long double invoiceSum = 0;
  long double taxSum = 0;

  deposit_calculator(depositAmount, period, percent, tax, frequency,
                     capitalization, &payment, &invoiceSum, &taxSum);

  ck_assert_ldouble_eq(payment, 150);
  ck_assert_ldouble_eq(invoiceSum, 500);
  ck_assert_ldouble_eq(taxSum, 39.375);
}
END_TEST
START_TEST(DEPOSIT_CALCULATOR2) {
  long double depositAmount = 500;
  int period = 365;
  long double percent = 30;
  long double tax = 35;
  int frequency = 91;
  int capitalization = 1;
  long double payment = 0;
  long double invoiceSum = 0;
  long double taxSum = 0;

  deposit_calculator(depositAmount, period, percent, tax, frequency,
                     capitalization, &payment, &invoiceSum, &taxSum);

  ck_assert_ldouble_eq_tol(payment, 167.22, 1e-2);
  ck_assert_ldouble_eq_tol(invoiceSum, 667.22, 1e-2);
  ck_assert_ldouble_eq_tol(taxSum, 45.0677, 1e-2);
}
END_TEST
START_TEST(DEPOSIT_CALCULATOR3) {
  long double depositAmount = 123.12;
  int period = 18000;
  long double percent = 11;
  long double tax = 35;
  int frequency = 0;
  int capitalization = 0;
  long double payment = 0;
  long double invoiceSum = 0;
  long double taxSum = 0;

  deposit_calculator(depositAmount, period, percent, tax, frequency,
                     capitalization, &payment, &invoiceSum, &taxSum);

  ck_assert_ldouble_eq_tol(payment, 667.88, 1e-2);
  ck_assert_ldouble_eq_tol(invoiceSum, 123.12, 1e-2);
  ck_assert_ldouble_eq_tol(taxSum, 0, 234);
}
END_TEST

START_TEST(CREDIT_CALCULATOR_ANNUITY1) {
  long double creditAmount = 89124.34;
  int period = 9;
  long double percent = 17;
  int type = ANNUITY;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, NULL, NULL);

  ck_assert_ldouble_eq_tol(payment, 10617.3, 1e-2);
  ck_assert_ldouble_eq_tol(overpayment, 6431.36, 1e-2);
  ck_assert_ldouble_eq_tol(totalPayment, 95555.70, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY2) {
  long double creditAmount = 439809.32;
  int period = 1;
  long double percent = 1;
  int type = ANNUITY;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, NULL, NULL);

  ck_assert_ldouble_eq_tol(payment, 440175.83, 1e-2);
  ck_assert_ldouble_eq_tol(overpayment, 366.51, 1e-2);
  ck_assert_ldouble_eq_tol(totalPayment, 440175.83, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY3) {
  long double creditAmount = 439809.32;
  int period = 1;
  long double percent = 0.01;
  int type = ANNUITY;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, NULL, NULL);

  ck_assert_ldouble_eq_tol(payment, 439812.99, 1e-2);
  ck_assert_ldouble_eq_tol(overpayment, 3.67, 1e-2);
  ck_assert_ldouble_eq_tol(totalPayment, 439812.99, 1e-2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY4) {
  long double creditAmount = 100;
  int period = 600;
  long double percent = 15;
  int type = ANNUITY;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, NULL, NULL);

  ck_assert_ldouble_eq_tol(payment, 1.25, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 650, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 750, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_ANNUITY5) {
  long double creditAmount = 324812.24;
  int period = 600;
  long double percent = 15;
  int type = ANNUITY;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, NULL, NULL);

  ck_assert_ldouble_eq_tol(payment, 4062.51, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 2112693.76, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 2437506.00, 1e2);
}
END_TEST

START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED1) {
  long double creditAmount = 89124.34;
  int period = 9;
  long double percent = 17;
  int type = DIFFERENTIATED;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double max = 0;
  long double min = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, &max, &min);

  ck_assert_ldouble_eq_tol(max, 11165.30, 1e2);
  ck_assert_ldouble_eq_tol(min, 10042.99, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 6312.97, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 95437.31, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED2) {
  long double creditAmount = 439809.32;
  int period = 1;
  long double percent = 1;
  int type = DIFFERENTIATED;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double max = 0;
  long double min = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, &max, &min);

  ck_assert_ldouble_eq_tol(max, 440175.83, 1e2);
  ck_assert_ldouble_eq_tol(min, 440175.83, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 366.51, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 440175.83, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED3) {
  long double creditAmount = 439809.32;
  int period = 1;
  long double percent = 0.01;
  int type = DIFFERENTIATED;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double max = 0;
  long double min = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, &max, &min);

  ck_assert_ldouble_eq_tol(max, 439812.99, 1e2);
  ck_assert_ldouble_eq_tol(min, 439812.99, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 3.67, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 439812.99, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED4) {
  long double creditAmount = 100;
  int period = 600;
  long double percent = 15;
  int type = DIFFERENTIATED;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double max = 0;
  long double min = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, &max, &min);

  ck_assert_ldouble_eq_tol(max, 1.42, 1e2);
  ck_assert_ldouble_eq_tol(min, 0.17, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 375.63, 1e2);
  ck_assert_ldouble_eq_tol(totalPayment, 475.63, 1e2);
}
END_TEST
START_TEST(CREDIT_CALCULATOR_DIFFERENTIATED5) {
  long double creditAmount = 324812.24;
  int period = 600;
  long double percent = 15;
  int type = DIFFERENTIATED;
  long double payment = 0;
  long double overpayment = 0;
  long double totalPayment = 0;
  long double max = 0;
  long double min = 0;
  credit_calculator(creditAmount, period, percent, type, &payment, &overpayment,
                    &totalPayment, &max, &min);

  ck_assert_ldouble_eq_tol(max, 4601.51, 1e2);
  ck_assert_ldouble_eq_tol(min, 548.12, 1e2);
  ck_assert_ldouble_eq_tol(overpayment, 1220075.98, 1e3);
  ck_assert_ldouble_eq_tol(totalPayment, 1544888.22, 1e3);
}
END_TEST

START_TEST(SMART_CALCULATOR_NUMBERS1) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("2 + 3 / 4", 0, result);  // 2 3 4 / +

  ck_assert_str_eq(result, "2.7500000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS2) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-3 - 4", 0, result);  // -3 4 -

  ck_assert_str_eq(result, "-7.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS3) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("5", 0, result);  // 5

  ck_assert_str_eq(result, "5.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS4) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("(2 + 3 / 4)", 0, result);  // 2 3 4 / +

  ck_assert_str_eq(result, "2.7500000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS5) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("2 - -3", 0, result);  // 2 -3 -

  ck_assert_str_eq(result, "5.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS6) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("+2 + 3", 0, result);  // 2 3 +

  ck_assert_str_eq(result, "5.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS7) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-(1 - 152)", 0, result);

  ck_assert_str_eq(result, "151.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS8) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-1 * -1 * (-1 * -1)", 0, result);

  ck_assert_str_eq(result, "1.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS9) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-1 * -1 * -1", 0, result);

  ck_assert_str_eq(result, "-1.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS10) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-1 * (10 - -15)", 0, result);

  ck_assert_str_eq(result, "-25.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS11) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("1 - 3 * -1 + 2 / -2 ^ 3", 0, result);

  ck_assert_str_eq(result, "3.7500000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS12) {
  char result[512] = {0};
  int RESULT_CODE =
      smart_calculator("(1 - 5) + (2 * (3 - 5) + (2 * (4 / 8)))", 0, result);

  ck_assert_str_eq(result, "-7.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS13) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("9124.234 + 3849.1239", 0, result);

  ck_assert_str_eq(result, "12973.3579000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS14) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator(".1 / .1", 0, result);

  ck_assert_str_eq(result, "1.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS15) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("1 / 0", 0, result);

  ck_assert_str_eq(result, "INF");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS16) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("0 / 0", 0, result);

  ck_assert_str_eq(result, "NAN");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS17) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator(
      "-.9 / -0.3 + (((((128 / 16) * 2) + 3) - 4) / 8)", 0, result);

  ck_assert_str_eq(result, "4.8750000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS18) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("1 - (-4)", 0, result);

  ck_assert_str_eq(result, "5.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS19) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("5 mod 3", 0, result);

  ck_assert_str_eq(result, "2.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS20) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("442 mod 35 * 28", 0, result);

  ck_assert_str_eq(result, "616.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS21) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("442 mod 35 ^ 3", 0, result);

  ck_assert_str_eq(result, "442.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS22) {
  char result[512] = {0};
  int RESULT_CODE =
      smart_calculator("2893.124 mod 129.324 mod 1.32", 0, result);

  ck_assert_str_eq(result, "0.4760000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS23) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("+", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS24) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS25) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("*", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS26) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("mod", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS27) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("mod 3", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS28) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("* 3", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS29) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("3 *", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS30) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("- 3", 0, result);

  ck_assert_str_eq(result, "-3.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS31) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("1.1.2 / 2.1", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS32) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("x", 2.5, result);

  ck_assert_str_eq(result, "2.5000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS33) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("x + x", 2.5, result);

  ck_assert_str_eq(result, "5.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS34) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("x / x", 2.5, result);

  ck_assert_str_eq(result, "1.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS35) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("45 * (*28 + 31)", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS36) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-2^2", 0, result);

  ck_assert_str_eq(result, "4.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS37) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("2^2^3", 0, result);

  ck_assert_str_eq(result, "64.0000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS38) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("3,5*2,8", 0, result);

  ck_assert_str_eq(result, "9.8000000");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS39) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("3----", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS40) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("**", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS41) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-^+", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_NUMBERS42) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("^*", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST

START_TEST(SMART_CALCULATOR_FUNCTIONS1) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(1)", 0, result);

  ck_assert_str_eq(result, "0.5403023");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS2) {
  char result[512] = {0};
  int RESULT_CODE =
      smart_calculator("cos(1 + cos(cos(3 + 4 * 5) + 10) / 2)", 0, result);

  ck_assert_str_eq(result, "0.8773672");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS3) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(x)", 1.5, result);

  ck_assert_str_eq(result, "0.0707372");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS4) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(125 + 90328 / sin(185))", 0, result);

  ck_assert_str_eq(result, "0.9990858");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS5) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("tan(9009142.324)", 0, result);

  ck_assert_str_eq(result, "0.2161690");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS6) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("atan(3892.1247032)", 0, result);

  ck_assert_str_eq(result, "1.5705394");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS7) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("log(3941.1348983123)", 0, result);

  ck_assert_str_eq(result, "3.5956213");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS8) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("sqrt(930124.1324903)", 0, result);

  ck_assert_str_eq(result, "964.4294336");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS9) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("ln(2089349.12740)", 0, result);

  ck_assert_str_eq(result, "14.5523632");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS10) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("-cos(1)", 0, result);

  ck_assert_str_eq(result, "-0.5403023");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS11) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("acos(0.92304912)", 0, result);

  ck_assert_str_eq(result, "0.3948635");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS12) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("asin(0.998329140)", 0, result);

  ck_assert_str_eq(result, "1.5129800");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS13) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(-)", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS14) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(-1)", 0, result);

  ck_assert_str_eq(result, "0.5403023");
  ck_assert_int_eq(RESULT_CODE, SUCCESS);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS15) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(*)", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS16) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(*/+-)", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST
START_TEST(SMART_CALCULATOR_FUNCTIONS17) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(cos(1.1.2))", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST

START_TEST(SMART_CALCULATOR_FUNCTIONS18) {
  char result[512] = {0};
  int RESULT_CODE = smart_calculator("cos(2x)", 0, result);

  ck_assert_str_eq(result, "ERROR");
  ck_assert_int_eq(RESULT_CODE, FAILURE);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int a;
  suite_add_tcase(s1, tc);
  tcase_add_test(tc, DEPOSIT_CALCULATOR1);
  tcase_add_test(tc, DEPOSIT_CALCULATOR2);
  tcase_add_test(tc, DEPOSIT_CALCULATOR3);

  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY1);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY2);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY3);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY4);
  tcase_add_test(tc, CREDIT_CALCULATOR_ANNUITY5);

  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED1);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED2);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED3);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED4);
  tcase_add_test(tc, CREDIT_CALCULATOR_DIFFERENTIATED5);

  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS1);   // 2 + 3 / 4
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS2);   // -3 - 4
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS3);   // 5
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS4);   // (2 + 3 / 4)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS5);   // 2 - -3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS6);   // +2 + 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS7);   // -(1 - 152)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS8);   // -1 * -1 * (-1 * -1)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS9);   // -1 * -1 * -1
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS10);  // -1 * (10 - -15)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS11);  // 1 - 3 * -1 + 2 / -2^3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS12);
  // (1 - 5) + (2 * (3 - 5) + (2 * (4 / 8)))
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS13);  // 9124.234 + 3849.1239
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS14);  // .1 / .1
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS15);  // 1 / 0
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS16);  // 0 / 0
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS17);
  // -.9 / -0.3 + (((((128 /16) * 2) + 3) - 4) / 8)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS18);  // 1 - (-4)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS19);  // 5 mod 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS20);  // 442 mod 35 * 28
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS21);  // 442 mod 35 ^ 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS22);
  // 2893.124 mod 129.324 mod 1.32
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS23);  // +
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS24);  // -
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS25);  // *
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS26);  // mod
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS27);  // mod 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS28);  // * 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS29);  // 3 *
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS30);  // - 3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS31);  // 1.1.2 / 2.1
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS32);  // x  &  x == 2.5
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS33);  // x + x  & x == 2.5
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS34);  // x / x  & x == 2.5
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS35);  // 45 * (*28 + 31)
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS36);  // -2^2
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS37);  // 2^2^3
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS38);  // 3,5 * 2,8
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS39);  // 3----
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS40);  // **
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS41);  // -^*
  tcase_add_test(tc, SMART_CALCULATOR_NUMBERS42);  // ^*

  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS1);  // cos(1)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS2);
  // cos(1 + cos(cos(3 + 4 * 5) + 10) / 2)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS3);  // cos(x) x = 1.5
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS4);
  // cos(125 + 90328 / sin(185))
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS5);   // tan(9009142.324)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS6);   // atan(3892.1247032)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS7);   // log(3941.1348983123)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS8);   // sqrt(930124.1324903)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS9);   // ln(2089349.12740)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS10);  // -cos(1)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS11);  // acos(0.92304912)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS12);  // asin(0.998329140)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS13);  // cos(-)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS14);  // cos(-1)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS15);  // cos(*)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS16);  // cos(*/+-)
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS17);  // cos(cos(1.1.2))
  tcase_add_test(tc, SMART_CALCULATOR_FUNCTIONS18);  // cos(2x)

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  a = srunner_ntests_failed(sr);
  srunner_free(sr);
  return a == 0 ? 0 : 1;
}
