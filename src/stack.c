#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *s) {
    s->top = NULL;
}

int stack_is_empty(Stack *s) {
    return s->top == NULL;
}

void stack_push(Stack *s, int value) {
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

Node *stack_pop_node(Stack *s) {
    if (!s->top) return NULL;
    Node *n = s->top;
    s->top = n->next;
    n->next = NULL;
    return n;
}

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
