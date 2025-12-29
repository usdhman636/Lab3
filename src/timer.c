#include <time.h>
#include "timer.h"
#include "sort.h"
#include "stack.h"

double measure_insertion(Stack *s) {
    Stack copy;
    stack_init(&copy);

    // Copy stack
    Stack tmp;
    stack_init(&tmp);
    while (!stack_is_empty(s)) {
        int val = stack_pop(s);
        stack_push(&tmp, val);
        stack_push(&copy, val);
    }
    while (!stack_is_empty(&tmp)) stack_push(s, stack_pop(&tmp));

    clock_t start = clock();
    insertion_sort_stack(&copy);
    clock_t end = clock();

    stack_free(&copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_merge(Stack *s) {
    Stack copy;
    stack_init(&copy);

    Stack tmp;
    stack_init(&tmp);
    while (!stack_is_empty(s)) {
        int val = stack_pop(s);
        stack_push(&tmp, val);
        stack_push(&copy, val);
    }
    while (!stack_is_empty(&tmp)) stack_push(s, stack_pop(&tmp));

    clock_t start = clock();
    merge_sort_stack(&copy);
    clock_t end = clock();

    stack_free(&copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}
