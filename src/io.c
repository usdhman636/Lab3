#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "stack.h"
#include "sort.h"
#include "timer.h"


void clearInputBuffer() {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF); }

static void print_stack(Stack *s) {
    for (Node *n = s->top; n; n = n->next)
        printf("%d ", n->data);
    printf("\n");
}

static void save_stack(const char *name, Stack *s) {
    FILE *f = fopen(name, "w");
    if (!f) return;
    for (Node *n = s->top; n; n = n->next)
        fprintf(f, "%d ", n->data);
    fclose(f);
}

static void read_input(Stack *s) {
    int x;
    printf("Введите числа через пробел (Ctrl+D чтобы закончить):\n");
    while (scanf("%d", &x) == 1) {stack_push(s, x);}

	clearInputBuffer();
}

static void read_file(const char *name, Stack *s) {
    FILE *f = fopen(name, "r");
    int x;
    if (!f) return;
    while (fscanf(f, "%d", &x) == 1)
        stack_push(s, x);
    fclose(f);
}

int IO(int argc, char **argv) {
    Stack s;
    stack_init(&s);

    if (argc == 1)
        read_input(&s);
    else{
        read_file(argv[1], &s);
	printf("\nпредыдущий стек\n");
	FILE *file_pointer;
	int number;
	file_pointer = fopen("unsorted.txt", "r");
	if (file_pointer == NULL) {
	printf("Error: Could not open the file unsorted.txt\n");
	 exit(1);
	}
	 while (fscanf(file_pointer, "%d", &number) == 1) {
	printf("%d ", number); 
	 }
	printf("\n");
	fclose(file_pointer);
	}


    if (stack_is_empty(&s)) {
        printf("Нет данных\n");
        return 0;
    }

    save_stack("unsorted.txt", &s);

    double ti = measure_insertion(&s);
    double tm = measure_merge(&s);

    merge_sort_stack(&s);
    save_stack("sorted.txt", &s);

    printf("Отсортированный массив:\n");
    print_stack(&s);
    printf("Время сортировки вставки: %.6f s\n", ti);
    printf("Время сортировки слиянием: %.6f s\n", tm);

    if (argc == 1) {
        printf("Повторить? (y/n): ");
        char c;
        scanf(" %c", &c);
	clearInputBuffer();
        if (c == 'y' || c == 'Y')
            return IO(argc, argv);
    }

    stack_free(&s);
    return 0;
}
