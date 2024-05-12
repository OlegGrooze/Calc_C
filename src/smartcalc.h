#ifndef SRC_SMARTCALC_H_
#define SRC_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define ANNUITY 1
#define DIFFERENTIATED 2

#define PLUS_OP +

typedef enum {
  NUMBER = 0,
  PLUS = 1,
  MINUS = 2,
  MULT = 3,
  DIV = 4,
  POWER = 5,
  MOD = 6,
  COS = 11,
  SIN = 12,
  TAN = 13,
  ACOS = 14,
  ASIN = 15,
  ATAN = 16,
  SQRT = 17,
  LN = 18,
  LOG = 19,
  BRACKET = 20,
} type_t;

typedef struct glass_t {
  long double value;
  int priority;
  type_t type;
  struct glass_t *next;
} glass_t;

//  Parser.c
int _find_x(char c);
int _find_unary_sign(char c);
int _find_digit(char c);
int _find_dot_or_comma(char c);
int _find_other_symbol(char c);
int _find_operation(char c);
int _find_function(char c);
int _find_mod(char *string);
int unary_operation(char *string, int position);
int digit(char *string, int position);
int function(char *string, int *function_type);
int enum_operation(char operation);
int priority_operation(char operation);
int empty_string(char *string);
int wrong_brackets(char *string);
int wrong_signs(char *string);
int wrong_x(char *string);
void delete_spaces(char *string, char *dest);
void add_number_to_stack(glass_t **num_stack, char **number, long double x);
int add_function_to_stack(glass_t **num_stack, char **function, long double x,
                          int function_type);
void add_operation_to_stack(glass_t **stack, glass_t **output, char **string);
void add_bracket_to_stack(glass_t **stack, char **string);

//  Stack.c

void push(glass_t **head, double digit, int priority, type_t type);
void pop(glass_t **head);
// void pop_digit(glass_t **head, double *digit);
glass_t peek(glass_t **head);
size_t get_size_stack(const glass_t *head);
glass_t *init_stack();
void delete_stack(glass_t **stack);

//  SmartCalc_v1.c

int smart_calculator(char *string, long double x, char *outputResult);
void credit_calculator(long double creditAmount, int period,
                       long double percent, int type, long double *payment,
                       long double *overpayment, long double *totalPayment,
                       long double *max, long double *min);
void deposit_calculator(long double depositAmount, int period,
                        long double percent, long double tax, int frequency,
                        int capitalization, long double *payment,
                        long double *invoiceSum, long double *taxSum);
glass_t *polish_notation(char *string, long double x, glass_t *output,
                         int *res);
int calculation(glass_t *output, double *result);
void calc_function(double x, type_t type, double *result);
void calc_operation(double operand1, double operand2, type_t type,
                    double *result);
void moves_number_to_output(glass_t **temp, glass_t **output);
void moves_operation_to_temp(glass_t **output, glass_t **temp);
void moves_operation_to_output(glass_t **stack, glass_t **output,
                               char **string);
void moves_last_to_output(glass_t **stack, glass_t **output);
void solves_for_two_number(glass_t **output, glass_t **temp);
void solves_for_functions(glass_t **output);

#endif  // SRC_SMARTCALC_H_
