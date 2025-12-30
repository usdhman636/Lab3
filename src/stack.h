#ifndef STACK_H
#define STACK_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void stack_init(Stack *s);
int stack_is_empty(Stack *s);
void stack_push(Stack *s, int value);
Node *stack_pop_node(Stack *s);
void stack_push_node(Stack *s, Node *n);
void stack_free(Stack *s);

#endif
