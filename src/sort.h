#ifndef SORT_H
#define SORT_H

#include "stack.h"

void insertion_sort_stack(Stack *s);
//void merge_sort_stack(Stack *s);
void split_stack(Stack *src, Stack *a, Stack *b);
Stack merge_stacks(Stack *a, Stack *b);
void merge_sort_stack(Stack *s);

#endif
