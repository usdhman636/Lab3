#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

// ---------- Insertion Sort ----------
void insertion_sort_stack(Stack *s) {
    Stack sorted;
    stack_init(&sorted);

    while (!stack_is_empty(s)) {
        int val = stack_pop(s);
        while (!stack_is_empty(&sorted) && stack_top(&sorted) > val) {
            stack_push(s, stack_pop(&sorted));
        }
        stack_push(&sorted, val);
    }

    while (!stack_is_empty(&sorted)) {
        stack_push(s, stack_pop(&sorted));
    }

    stack_free(&sorted);
}

// ---------- Merge Sort ----------
static Stack merge_stacks(Stack *left, Stack *right) {
    Stack result;
    stack_init(&result);
    Stack tmp;
    stack_init(&tmp);

    while (!stack_is_empty(left) || !stack_is_empty(right)) {
        if (stack_is_empty(left)) stack_push(&tmp, stack_pop(right));
        else if (stack_is_empty(right)) stack_push(&tmp, stack_pop(left));
        else if (stack_top(left) <= stack_top(right)) stack_push(&tmp, stack_pop(left));
        else stack_push(&tmp, stack_pop(right));
    }

    while (!stack_is_empty(&tmp)) {
        stack_push(&result, stack_pop(&tmp));
    }

    stack_free(&tmp);
    return result;
}

void merge_sort_stack(Stack *s) {
    if (s->top == NULL || s->top->next == NULL) return;

    Stack left, right;
    stack_init(&left);
    stack_init(&right);

    int toggle = 0;
    while (!stack_is_empty(s)) {
        if (toggle == 0) stack_push(&left, stack_pop(s));
        else stack_push(&right, stack_pop(s));
        toggle = 1 - toggle;
    }

    merge_sort_stack(&left);
    merge_sort_stack(&right);

    Stack merged = merge_stacks(&left, &right);

    while (!stack_is_empty(&merged)) {
        stack_push(s, stack_pop(&merged));
    }

    stack_free(&left);
    stack_free(&right);
    stack_free(&merged);
}
