#include "smartcalc.h"

int smart_calculator(char *string, long double x, char *outputResult) {
  int res = SUCCESS;
  glass_t *output = init_stack();
  char input[256] = {0};
  char *str = input;
  double result = 0;
  delete_spaces(string, input);
  if (empty_string(str) || wrong_brackets(str) || wrong_signs(str) ||
      !wrong_x(str)) {
    res = FAILURE;
    delete_stack(&output);
    strcpy(outputResult, "ERROR");
  } else {
    output = polish_notation(input, x, output, &res);
    if (res == SUCCESS) {
      res = calculation(output, &result);
      if (isnan(result)) {
        strcpy(outputResult, "NAN");
      } else if (isinf(result)) {
        strcpy(outputResult, "INF");
      } else if (res == FAILURE) {
        strcpy(outputResult, "ERROR");
      } else {
        sprintf(outputResult, "%.7lf", result);
      }
    } else {
      delete_stack(&output);
      strcpy(outputResult, "ERROR");
    }
  }
  return res;
}

void credit_calculator(long double creditAmount, int period,
                       long double percent, int type, long double *payment,
                       long double *overpayment, long double *totalPayment,
                       long double *max, long double *min) {
  if (type == ANNUITY) {
    long double rate = percent / (long double)1200;
    long double x = rate * pow(rate + 1, (long double)period) /
                    (pow(rate + 1, (long double)period) - 1);
    *payment = x * creditAmount;
    *totalPayment = *payment * (long double)period;
    *overpayment = *totalPayment - creditAmount;
  } else if (type == DIFFERENTIATED) {
    long double rate = creditAmount / (long double)period;
    *max = rate + creditAmount * percent * 30.42 / 36524.25;
    *min = rate + rate * percent * 30.42 / 36524.25;
    *payment = (*max + *min) / 2;
    *totalPayment = *payment * (long double)period;
    *overpayment = *totalPayment - creditAmount;
  }
}

void deposit_calculator(long double depositAmount, int period,
                        long double percent, long double tax, int frequency,
                        int capitalization, long double *payment,
                        long double *invoiceSum, long double *taxSum) {
  long double refinance = 7.5;
  long double payref = 0;
  int capitalizationPeriod = 0;
  if (frequency != 0) {
    capitalizationPeriod = period / frequency;
  } else {
    capitalization = 0;
  }
  if (capitalization == 0) {
    *payment = (depositAmount * (percent / 100) * (long double)period) / 365.0;
    payref = (depositAmount * (refinance / 100) * (long double)period) / 365.0;
    *invoiceSum = depositAmount;
  } else {
    *payment = depositAmount *
                   pow(1.0 + (percent / 100) * (long double)frequency / 365.0,
                       (long double)capitalizationPeriod) -
               depositAmount;
    payref = depositAmount *
                   pow(1.0 + (refinance / 100) * (long double)frequency / 365.0,
                       (long double)capitalizationPeriod) -
               depositAmount;
    *invoiceSum = depositAmount + *payment;
  }
  if (percent > refinance) {
    *taxSum = (*payment - payref) * ((tax) / 100);
  }
}

// переводит выражение в польскую нотацию
glass_t *polish_notation(char *string, long double x, glass_t *output,
                         int *res) {
  *res = SUCCESS;
  glass_t *stack = init_stack();
  char *str = string;
  int function_type = -1;
  for (int i = 0; *res == SUCCESS && *str; i++) {
    if (digit(str, i)) {
      add_number_to_stack(&output, &str, x);
    } else if (function(str, &function_type)) {
      *res = add_function_to_stack(&output, &str, x, function_type);
    } else if (*str == '(') {
      add_bracket_to_stack(&stack, &str);
    } else if (_find_operation(*str) || _find_mod(str)) {
      add_operation_to_stack(&stack, &output, &str);
    } else if (*str == ')') {
      moves_operation_to_output(&stack, &output, &str);
    } else {
      *res = FAILURE;
    }
  }
  if (*res == SUCCESS) moves_last_to_output(&stack, &output);
  delete_stack(&stack);
  return output;
}

int calculation(glass_t *output, double *result) {
  int res = SUCCESS;
  glass_t *temp = init_stack();
  if (get_size_stack(output) == 2 ||
      (get_size_stack(output) == 3 && output->type >= PLUS &&
       output->type <= MOD)) {
    if (output->type >= COS && output->type <= LOG) {
      solves_for_functions(&output);
    } else if (output->type >= PLUS && output->type <= MOD) {
      res = FAILURE;
    }
  } else {
    while (get_size_stack(output) > 2 || get_size_stack(temp) > 1) {
      if (output->type >= PLUS && output->type <= MOD) {
        moves_operation_to_temp(&output, &temp);
      } else if (output->type >= COS && output->type <= LOG) {
        solves_for_functions(&output);
      } else if ((get_size_stack(output) <= 2 && get_size_stack(temp) > 1) ||
                 (output->type == NUMBER && temp->type == NUMBER)) {
        moves_number_to_output(&temp, &output);
      } else if (output->type == NUMBER) {
        solves_for_two_number(&output, &temp);
      }
    }
  }
  *result = output->value;
  delete_stack(&temp);
  delete_stack(&output);
  return res;
}

void calc_function(double x, type_t type, double *result) {
  if (type == COS) {
    *result = cos(x);
  } else if (type == SIN) {
    *result = sin(x);
  } else if (type == TAN) {
    *result = tan(x);
  } else if (type == ACOS) {
    *result = acos(x);
  } else if (type == ASIN) {
    *result = asin(x);
  } else if (type == ATAN) {
    *result = atan(x);
  } else if (type == SQRT) {
    *result = sqrt(x);
  } else if (type == LN) {
    *result = log(x);
  } else if (type == LOG) {
    *result = log10(x);
  }
}

void calc_operation(double operand1, double operand2, type_t type,
                    double *result) {
  if (type == PLUS) {
    *result = operand1 + operand2;
  } else if (type == MINUS) {
    *result = operand1 - operand2;
  } else if (type == MULT) {
    *result = operand1 * operand2;
  } else if (type == DIV) {
    *result = operand1 / operand2;
  } else if (type == POWER) {
    *result = pow(operand1, operand2);
  } else if (type == MOD) {
    *result = fmod(operand1, operand2);
  }
}

// перемещает числа обратно в выходной стек
void moves_number_to_output(glass_t **temp, glass_t **output) {
  while ((*temp)->type == NUMBER) {
    push(output, (*temp)->value, 0, (*temp)->type);
    pop(temp);
  }
}

// перемещает операторы во временный стек
void moves_operation_to_temp(glass_t **output, glass_t **temp) {
  while ((*output)->type >= PLUS && (*output)->type <= MOD) {
    push(temp, 0, 0, (*output)->type);
    pop(output);
  }
}

// перемещение операторов из стека в вывод
void moves_operation_to_output(glass_t **stack, glass_t **output,
                               char **string) {
  glass_t temp = peek(stack);
  while (temp.type != BRACKET) {
    push(output, temp.value, temp.priority, temp.type);
    pop(stack);
    temp = peek(stack);
  }
  pop(stack);
  (*string)++;
}

// перемещение оставшегося из стека в выходной
void moves_last_to_output(glass_t **stack, glass_t **output) {
  while (*stack != NULL && (*stack)->priority != -1) {
    push(output, 0, (*stack)->priority, (*stack)->type);
    pop(stack);
  }
}

// решение после добавления двух операндов
void solves_for_two_number(glass_t **output, glass_t **temp) {
  double operand1 = (*output)->value;
  double operand2 = 0;
  double rawResult = 0;
  pop(output);
  if ((*output)->type >= PLUS && (*output)->type <= MOD) {
    push(temp, operand1, 0, NUMBER);
    while ((*output)->type >= PLUS && (*output)->type <= MOD) {
      push(temp, 0, 0, (*output)->type);
      pop(output);
    }
  } else if (((*output)->type >= COS && (*output)->type <= LOG) ||
             (*output)->type == NUMBER) {
    if ((*output)->type >= COS && (*output)->type <= LOG) {
      calc_function((*output)->value, (*output)->type, &rawResult);
      pop(output);
      operand2 = rawResult;
    } else if ((*output)->type == NUMBER) {
      operand2 = (*output)->value;
      pop(output);
    }
    calc_operation(operand2, operand1, (*temp)->type, &rawResult);
    pop(temp);
    push(output, rawResult, 0, NUMBER);
  }
}

// решение для функций
void solves_for_functions(glass_t **output) {
  double res = 0;
  calc_function((*output)->value, (*output)->type, &res);
  pop(output);
  push(output, res, 0, NUMBER);
}
