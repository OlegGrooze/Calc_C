#include "smartcalc.h"

int _find_x(char c) { return c == 'x' || c == 'X'; }

int _find_unary_sign(char c) { return c == '+' || c == '-'; }

int _find_digit(char c) { return (c >= '0' && c <= '9') || _find_x(c); }

int _find_dot_or_comma(char c) { return c == '.' || c == ','; }

int _find_other_symbol(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\0';
}

int _find_operation(char c) {
  return c == '/' || c == '*' || c == '+' || c == '-' || c == '^';
}

int _find_function(char c) {
  return c == 'c' || c == 's' || c == 't' || c == 'a' || c == 'l';
}

int _find_mod(char *string) {
  return *string == 'm' && *(string + 1) == 'o' && *(string + 2) == 'd';
}

int unary_operation(char *string, int position) {
  int res = FAILURE;
  char previous_symbol = *(string - 1);
  char currently_symbol = *string;
  char next_symbol = *(string + 1);
  if (_find_unary_sign(currently_symbol) && next_symbol == '(') {
    res = FAILURE;
  } else if (position == 0 && _find_unary_sign(currently_symbol) &&
             (_find_digit(next_symbol) || _find_dot_or_comma(next_symbol))) {
    res = SUCCESS;
  } else if (position > 0 && _find_unary_sign(currently_symbol) &&
             !_find_digit(previous_symbol) && previous_symbol != ')') {
    res = SUCCESS;
  }
  return res;
}

int digit(char *string, int position) {
  int res = FAILURE;
  char *str = string;
  int flag_dot = 0;
  if (unary_operation(string, position)) {
    res = SUCCESS;
    str++;
  }
  if (_find_x(*str)) {
    res = SUCCESS;
    str++;
  } else {
    for (; *str && (_find_digit(*str) || _find_dot_or_comma(*str)); str++) {
      if (flag_dot && _find_dot_or_comma(*str)) {
        res = FAILURE;
        break;
      } else if (_find_dot_or_comma(*str)) {
        flag_dot = 1;
      } else {
        res = SUCCESS;
      }
    }
  }
  return res;
}

int function(char *string, int *function_type) {
  int res = FAILURE;
  char *functions[9] = {"cos(",  "sin(",  "tan(", "acos(", "asin(",
                        "atan(", "sqrt(", "ln(",  "log("};
  for (int i = 0; i < 9 && res == FAILURE; i++) {
    char *str = string;
    if (!strncmp(functions[i], str, strlen(functions[i]))) {
      *function_type = i + 11;
      res = SUCCESS;
    }
  }
  return res;
}

// определяет тип операции
int enum_operation(char operation) {
  int type = 0;
  if (operation == '+') {
    type = PLUS;
  } else if (operation == '-') {
    type = MINUS;
  } else if (operation == '*') {
    type = MULT;
  } else if (operation == '/') {
    type = DIV;
  } else if (operation == '^') {
    type = POWER;
  } else if (operation == 'm') {
    type = MOD;
  }
  return type;
}

// определяет приоритет операции
int priority_operation(char operation) {
  int priority = 0;
  if (operation == '+' || operation == '-') {
    priority = 1;
  } else if (operation == '*' || operation == '/') {
    priority = 2;
  } else if (operation == 'm') {
    priority = 3;
  } else if (operation == '^') {
    priority = 4;
  }
  return priority;
}

int empty_string(char *string) {
  int res = SUCCESS;
  char *str = string;
  for (; res != FAILURE && *str; str++) {
    if (!_find_other_symbol(*str)) res = FAILURE;
  }
  return res;
}

int wrong_brackets(char *string) {
  int res = FAILURE;
  char *str = string;
  int first_bracket = 0;
  int second_bracket = 0;
  for (; res != SUCCESS && *str; str++) {
    if (*str == '(') {
      first_bracket++;
    } else if (*str == ')') {
      second_bracket++;
      if (second_bracket > first_bracket) res = SUCCESS;
    }
  }
  if (second_bracket != first_bracket) res = SUCCESS;
  return res;
}

int wrong_signs(char *string) {
  int res = FAILURE;
  char *str = string;
  for (; res != SUCCESS && *str; str++) {
    if (*str == '(' &&
        (*(str + 1) == '*' || *(str + 1) == '/' || *(str + 1) == '^')) {
      res = SUCCESS;
    }
  }
  return res;
}

int wrong_x(char *string) {
  int res = SUCCESS;
  char *str = string;
  for (; res != FAILURE && *str; str++) {
    if (((*str >= '0' && *str <= '9') &&
         (*(str + 1) == 'x' || *(str + 1) == 'X')) ||
        ((*str == 'x' || *str == 'X') &&
         (*(str + 1) >= '0' && *(str + 1) <= '9'))) {
      res = FAILURE;
    }
    if ((*str == '*' || *str == '+' || *str == '/' || *str == '^' ||
         *str == '-') &&
        *(str + 1) == '^') {
      res = FAILURE;
    }
    if (*str == '^' &&
        (*(str + 1) == '*' || *(str + 1) == '/' || *(str + 1) == '^')) {
      res = FAILURE;
    }
    if ((*str == '-' && (*(str + 1) == '-' && *(str + 2) == '-')) ||
        (*str == '+' && (*(str + 1) == '+' && *(str + 2) == '+'))) {
      res = FAILURE;
    }
    if ((*str == '/' && *(str + 1) == '/') ||
        (*str == '*' && *(str + 1) == '*')) {
      res = FAILURE;
    }
  }
  return res;
}

void delete_spaces(char *string, char *dest) {
  char *str = string;
  for (int i = 0; *str; str++) {
    if (*str != ' ') {
      dest[i] = *str;
      i++;
    }
  }
}

// добавляет число в стек
void add_number_to_stack(glass_t **num_stack, char **number, long double x) {
  int flag = 0;
  int sign = 1;
  if (_find_unary_sign(**number)) {
    if (**number == '-') sign = -1;
    (*number)++;
  }
  if (_find_x(**number)) {
    (*number)++;
    push(num_stack, x * sign, 0, NUMBER);
  } else {
    char temp[256] = {0};
    for (int i = 0;
         **number && (_find_digit(**number) || _find_dot_or_comma(**number)) &&
         !(flag && _find_dot_or_comma(**number));
         (*number)++, i++) {
      if (_find_dot_or_comma(**number) && !flag) {
        flag = 1;
        if (**number == ',') **number = '.';
      }
      temp[i] = **number;
    }
    push(num_stack, atof(temp) * sign, 0, NUMBER);
  }
}

// добавляет функцию в стек
int add_function_to_stack(glass_t **num_stack, char **function, long double x,
                          int function_type) {
  int res = SUCCESS;
  char temp[256] = {0};
  char result[512] = {0};
  while (**function != '(') (*function)++;
  (*function)++;
  for (int i = 0, bracket = 1; bracket != 0; (*function)++) {
    if (**function == '(') {
      bracket++;
    } else if (**function == ')') {
      bracket--;
    }
    if (bracket != 0) {
      temp[i] = **function;
      i++;
    }
  }
  smart_calculator(temp, x, result);
  if (digit(result, 0) == SUCCESS) {
    push(num_stack, atof(result), 0, function_type);
  } else {
    res = FAILURE;
  }
  return res;
}

// добавляет операцию в стек
void add_operation_to_stack(glass_t **stack, glass_t **output, char **string) {
  char previous = **string;
  (*string)--;
  char temp = **string;
  (*string)++;
  (*string)++;
  if (previous == '-' && **string == '(' && !_find_digit(temp)) {
    push(output, -1, 0, NUMBER);
    previous = '*';
  } else if (previous == '-' && _find_function(**string)) {
    push(output, 0, 0, NUMBER);
    previous = '-';
  }
  while (priority_operation(previous) <= (*stack)->priority) {
    push(output, (*stack)->value, (*stack)->priority, (*stack)->type);
    pop(stack);
  }
  push(stack, 0, priority_operation(previous), enum_operation(previous));
  if (previous == 'm') (*string) += 2;
}

// добавляет скобку в стек
void add_bracket_to_stack(glass_t **stack, char **string) {
  push(stack, 0, 0, BRACKET);
  (*string)++;
}
