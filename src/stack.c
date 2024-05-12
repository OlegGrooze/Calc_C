#include "smartcalc.h"

void push(glass_t **head, double digit, int priority, type_t type) {
  glass_t *temp = malloc(sizeof(glass_t));
  if (temp != NULL) {
    temp->value = digit;
    temp->priority = priority;
    temp->type = type;
    temp->next = *head;
    *head = temp;
  }
}

void pop(glass_t **head) {
  glass_t *temp = *head;
  if (*head != NULL) {
    *head = (*head)->next;
    free(temp);
  }
}

glass_t peek(glass_t **head) {
  glass_t *temp = *head;
  if (*head != NULL) {
    temp = *head;
  }
  return *temp;
}

size_t get_size_stack(const glass_t *head) {
  size_t size = 0;
  while (head) {
    size++;
    head = head->next;
  }
  return size;
}

glass_t *init_stack() {
  glass_t *stack;
  stack = malloc(sizeof(glass_t));
  stack->value = -1;
  stack->priority = -1;
  stack->type = -1;
  stack->next = NULL;
  return stack;
}

void delete_stack(glass_t **stack) {
  while (*stack != NULL) {
    pop(stack);
  }
}
