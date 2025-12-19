#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "timer.h"
#include "sort.h"

double measure_insertion(const int *arr, int n) {
    int *tmp = malloc(n * sizeof(int));
    if (!tmp) {
        return -1.0;
    }

    memcpy(tmp, arr, n * sizeof(int));

    clock_t start = clock();
    insertion_sort(tmp, n);
    clock_t end = clock();

    free(tmp);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_merge(const int *arr, int n) {
    int *tmp = malloc(n * sizeof(int));
    if (!tmp) {
        return -1.0;
    }

    memcpy(tmp, arr, n * sizeof(int));

    clock_t start = clock();
    merge_sort(tmp, 0, n - 1);
    clock_t end = clock();

    free(tmp);

    return (double)(end - start) / CLOCKS_PER_SEC;
}
