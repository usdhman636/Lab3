#include <stdlib.h>
#include "stack.h"

#define INITIAL_CAPACITY 10

int stack_init(Stack *s, int capacity) {
    s->capacity = capacity;
    s->top = 0;

    s->data = malloc(s->capacity * sizeof(int));
    if (!s->data) {
        return 0; // failure
    }
    return 1; // success
}

void stack_free(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->capacity = 0;
    s->top = 0;
}

int stack_push(Stack *s, int value) {
    if (s->top >= s->capacity) {
        s->capacity *= 2;
        int *tmp = realloc(s->data, s->capacity * sizeof(int));
        if (!tmp) return 0;
        s->data = tmp;
    }

    *(s->data + s->top) = value;
    s->top++;
    return 1;
}

int stack_pop(Stack *s, int *value) {
    if (s->top == 0) return 0;

    s->top--;
    *value = *(s->data + s->top);
    return 1;
}

int stack_is_empty(Stack *s) {
    return s->top == 0;
}
