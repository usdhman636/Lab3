#include <time.h>
#include "timer.h"
#include "sort.h"

static Stack copy_stack(Stack *s) {
    Stack tmp, copy;
    stack_init(&tmp);
    stack_init(&copy);

    for (Node *n = s->top; n; n = n->next)
        stack_push(&tmp, n->data);

    while (!stack_is_empty(&tmp))
        stack_push_node(&copy, stack_pop_node(&tmp));

    return copy;
}

double measure_insertion(Stack *s) {
    Stack c = copy_stack(s);
    clock_t start = clock();
    insertion_sort_stack(&c);
    clock_t end = clock();
    stack_free(&c);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_merge(Stack *s) {
    Stack c = copy_stack(s);
    clock_t start = clock();
    merge_sort_stack(&c);
    clock_t end = clock();
    stack_free(&c);
    return (double)(end - start) / CLOCKS_PER_SEC;
}
