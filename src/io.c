#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
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


void stack_reverse(Stack *s) {
    Stack tmp;
    stack_init(&tmp);

    while (!stack_is_empty(s)) {
        stack_push_node(&tmp, stack_pop_node(s));
    }

    s->top = tmp.top;
}


int IO(int argc, char **argv) {
   // SetConsoleOutputCP(CP_UTF8);
   // SetConsoleCP(CP_UTF8);
    Stack s;
    stack_init(&s);

    if (argc == 1)
        read_input(&s);
    else{
           char *txtFile = NULL;
           int found = 0;  // 0 = false, 1 = true
        
        for (int i = 1; i < argc; i++) {
            size_t len = strlen(argv[i]);
            if (len >= 4 && strcmp(argv[i] + len - 4, ".txt") == 0) {
                txtFile = argv[i];
                found = 1;
                break;
            }
        }
            
        if (found) {
            read_file(txtFile, &s);
        } else {
            // No .txt file found
            read_file(argv[1], &s);
          }
    
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

    Stack tmp_reverse = copy_stack(&s);
    stack_reverse(&tmp_reverse);
    save_stack("unsorted.txt", &tmp_reverse);

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

    stack_free(&tmp_reverse);
    stack_free(&s);
    return 0;
}
