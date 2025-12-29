#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_init(Stack *s) {
    s->top = NULL;
    return 0;
}

int stack_is_empty(Stack *s) {
    return (s->top == NULL);
}

void stack_push(Stack *s, int value) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = s->top;
    s->top = n;
}

int stack_pop(Stack *s) {
    if (stack_is_empty(s)) return 0;
    Node *tmp = s->top;
    int val = tmp->data;
    s->top = tmp->next;
    free(tmp);
    return val;
}

int stack_top(Stack *s) {
    if (stack_is_empty(s)) return 0;
    return s->top->data;
}

void stack_free(Stack *s) {
    while (!stack_is_empty(s)) {
        stack_pop(s);
    }
}
