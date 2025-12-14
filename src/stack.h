#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100000

typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

void stack_init(Stack *s);
void stack_push(Stack *s, int value);
int stack_pop(Stack *s);

#endif
