#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *s) {
    s->top = NULL;
}

int stack_is_empty(Stack *s) {
    return s->top == NULL;
}

// Pushes a new value onto the top of the stack by
// creating a new node
void stack_push(Stack *s, int value) {
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

// Pops the top node from the stack and returns 
//it without freeing it.
Node *stack_pop_node(Stack *s) {
    if (!s->top) return NULL;
    Node *n = s->top;
    s->top = n->next;
    n->next = NULL;
    return n;
}

// Pushes an existing node onto the top of the 
//stack without creating a new node.
void stack_push_node(Stack *s, Node *n) {
    if (!n) return;
    n->next = s->top;
    s->top = n;
}

void stack_free(Stack *s) {
    while (!stack_is_empty(s)) {
        free(stack_pop_node(s));
    }
}
