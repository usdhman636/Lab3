#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include "io.h"
#include "stack.h"
#include "sort.h"
#include "timer.h"

void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int read_input(Stack *s) {
    int val;
    printf("Введите числа через пробел (Ctrl+D чтобы закончить):\n");
    while (scanf("%d", &val) == 1) {
        stack_push(s, val);
    }
    clear_input_buffer();
    return 0;
}

int read_file(const char *filename, Stack *s) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Не удалось открыть файл %s\n", filename);
        return -1;
    }
    int val;
    while (fscanf(f, "%d", &val) == 1) {
        stack_push(s, val);
    }
    fclose(f);
    return 0;
}

void save_stack(const char *filename, Stack *s) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    Stack tmp;
    stack_init(&tmp);

    while (!stack_is_empty(s)) {
        int val = stack_pop(s);
        fprintf(f, "%d ", val);
        stack_push(&tmp, val);
    }

    while (!stack_is_empty(&tmp)) {
        stack_push(s, stack_pop(&tmp));
    }

    fclose(f);
}

int IO(int argc, char *argv[]) {

    //SetConsoleOutputCP(CP_UTF8);

    Stack s;
    stack_init(&s);

    if (argc == 1) read_input(&s);
    else{
	 read_file(argv[1], &s);
	    printf("предыдущий стек:\n");
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
	    fclose(file_pointer);
	}

    if (stack_is_empty(&s)) {
        printf("Данные не предоставлены.\n");
        return 0;
    }

    printf("\nмассив в стеке:\n");
    Stack tmp;
    stack_init(&tmp);
    while (!stack_is_empty(&s)) {
        int val = stack_pop(&s);
        printf("%d ", val);
        stack_push(&tmp, val);
    }
    while (!stack_is_empty(&tmp)) stack_push(&s, stack_pop(&tmp));
    printf("\n");

    // Save unsorted
    save_stack("unsorted.txt", &s);

    // Timing
    double t_ins = measure_insertion(&s);
    double t_mer = measure_merge(&s);

    // Sort and save sorted
    Stack sorted;
    stack_init(&sorted);
    while (!stack_is_empty(&s)) stack_push(&sorted, stack_pop(&s));

    insertion_sort_stack(&sorted);
    save_stack("sorted.txt", &sorted);

    printf("\nОтсортированный массив:\n");
    Stack tmp2;
    stack_init(&tmp2);
    while (!stack_is_empty(&sorted)) {
        int val = stack_pop(&sorted);
        printf("%d ", val);
        stack_push(&tmp2, val);
    }
    while (!stack_is_empty(&tmp2)) stack_push(&sorted, stack_pop(&tmp2));
    printf("\n\n");

    printf("Время сортировки вставки: %.6f s\n", t_ins);
    printf("Время сортировки слиянием: %.6f s\n", t_mer);

    // Repeat if no argv
    if (argc == 1) {
        printf("\nПовторить? (y/n): ");
        char c;
        scanf(" %c", &c);
        clear_input_buffer();
        if (c == 'y' || c == 'Y') return IO(argc, argv);
    }

    stack_free(&s);
    stack_free(&sorted);

    return 0;
}
