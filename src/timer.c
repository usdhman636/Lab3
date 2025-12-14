#include "timer.h"
#include "sort.h"
#include <time.h>
#include <string.h>

double measure_insertion(int arr[], int n) {
    int copy[n];
    memcpy(copy, arr, sizeof(int) * n);

    clock_t start = clock();
    insertion_sort(copy, n);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double measure_merge(int arr[], int n) {
    int copy[n];
    memcpy(copy, arr, sizeof(int) * n);

    clock_t start = clock();
    merge_sort(copy, 0, n - 1);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}
