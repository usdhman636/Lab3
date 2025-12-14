#include "stack.h"

void stack_init(Stack *s) {
    s->top = -1;
}

void stack_push(Stack *s, int value) {
    if (s->top < MAX_STACK - 1) {
        s->data[++s->top] = value;
    }
}

int stack_pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[s->top--];
    }
    return 0;
}
