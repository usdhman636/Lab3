#ifndef STACK_H
#define STACK_H

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

int stack_init(Stack *s, int capacity);
void stack_free(Stack *s);
int stack_push(Stack *s, int value);
int stack_pop(Stack *s, int *value);
int stack_is_empty(Stack *s);

#endif
