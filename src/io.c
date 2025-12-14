#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "stack.h"
#include "sort.h"
#include "timer.h"

#define MAX_INPUT 10000

/* ---------- CLEAR INPUT BUFFER ---------- */
void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/* ---------- SAVE ARRAY ---------- */
void save_array(const char *filename, const int *arr, int n) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d ", arr[i]);
    }

    fclose(f);
}

/* ---------- READ FROM STDIN ---------- */
int read_input(int *arr) {
    int n = 0;
    printf("Введите числа, разделенные пробелом. (Ctrl+D чтобы завершить):\n");

    while (n < MAX_INPUT && scanf("%d", &arr[n]) == 1) {
        n++;
    }

    clear_input_buffer(); 

    return n;
}

/* ---------- READ FROM FILE ---------- */
int read_file(const char *filename, int *arr) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("открытие файла не удалось");
        return -1;
    }

    int n = 0;
    while (n < MAX_INPUT && fscanf(f, "%d", &arr[n]) == 1) {
        n++;
    }

    fclose(f);
    return n;
}

/* ---------- MAIN I/O FUNCTION ---------- */
int IO(int argc, char *argv[]) {

    int arr[MAX_INPUT];
    int n = 0;

    /* ---------- INPUT ---------- */
    if (argc == 1) {
        n = read_input(arr);
    } else {
        n = read_file("unsorted.txt", arr);
        printf("\nпредыдущий массив:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");

        n = read_file("sorted.txt", arr);
        printf("предыдущий отсортированный массив:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");

        n = read_file(argv[1], arr);
        if (n < 0) return 1;
    }

    if (n == 0) {
        printf("Данные не предоставлены.\n");
        return 0;
    }

    /* ---------- SAVE ORIGINAL ---------- */
    save_array("unsorted.txt", arr, n);

    /* ---------- STACK ---------- */
    Stack s;
    stack_init(&s);
    for (int i = 0; i < n; i++) {
        stack_push(&s, arr[i]);
    }

    /* ---------- TIMING ---------- */
    double t_ins = measure_insertion(arr, n);
    double t_mer = measure_merge(arr, n);

    /* ---------- SORTED ARRAY ---------- */
    int sorted[MAX_INPUT];
    memcpy(sorted, arr, sizeof(int) * n);
    insertion_sort(sorted, n);
    save_array("sorted.txt", sorted, n);

    /* ---------- OUTPUT ---------- */
    if (argc == 1) {
        printf("\nотсортированные числа:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", sorted[i]);
        }
        printf("\n\n");

        printf("Время сортировки вставки: %.6f s\n", t_ins);
        printf("Время сортировки при слиянии: %.6f s\n", t_mer);

        /* ---------- REPEAT ---------- */
        printf("\nповторить?? (y/n): ");
        //clear_input_buffer();
        char c;
        scanf("%c", &c);
        clear_input_buffer();
        if (c == 'y' || c == 'Y') {
            return IO(argc, argv);
        }
    } else {
        printf("отсортированный массив из файла:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", sorted[i]);
        }
        printf("\nколичество элементов[%d]\nвремя вставки составляет [%.6f] Время слияния составляет [%.6f]\n",
               n, t_ins, t_mer);
    }

    return 0;

}
