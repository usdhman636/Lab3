#ifndef STACK_H
#define STACK_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

// Initialize stack
int stack_init(Stack *s);

// Check if stack is empty
int stack_is_empty(Stack *s);

// Push value onto stack
void stack_push(Stack *s, int value);

// Pop value from stack
int stack_pop(Stack *s);

// Get top value of stack without popping
int stack_top(Stack *s);

// Free all memory used by stack
void stack_free(Stack *s);

#endif
