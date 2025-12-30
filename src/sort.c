#include <stdlib.h>
#include "sort.h"

/* -------- INSERTION SORT (node-based) -------- */
void insertion_sort_stack(Stack *s) {
    Stack sorted;
    stack_init(&sorted);

    while (!stack_is_empty(s)) {
        Node *curr = stack_pop_node(s);

        while (!stack_is_empty(&sorted) &&
               sorted.top->data > curr->data) {
            stack_push_node(s, stack_pop_node(&sorted));
        }

        stack_push_node(&sorted, curr);
    }

    while (!stack_is_empty(&sorted)) {
        stack_push_node(s, stack_pop_node(&sorted));
    }
}

/* -------- MERGE SORT (node-based) -------- */

static Node *merge(Node *a, Node *b) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
        tail->next = NULL;
    }

    tail->next = (a) ? a : b;
    return dummy.next;
}

static Node *split(Node *head) {
    Node *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *mid = slow->next;
    slow->next = NULL;
    return mid;
}

static Node *merge_sort_nodes(Node *head) {
    if (!head || !head->next) return head;

    Node *mid = split(head);
    head = merge_sort_nodes(head);
    mid = merge_sort_nodes(mid);
    return merge(head, mid);
}

void merge_sort_stack(Stack *s) {
    s->top = merge_sort_nodes(s->top);
}
