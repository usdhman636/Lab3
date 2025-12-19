#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

// -------------------- Insertion Sort --------------------
void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = *(arr + i);
        int j = i - 1;

        while (j >= 0 && *(arr + j) > key) {
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
    }
}

// -------------------- Merge Function --------------------
void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Allocate temporary arrays dynamically
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        *(L + i) = *(arr + left + i);
    for (int j = 0; j < n2; j++)
        *(R + j) = *(arr + mid + 1 + j);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (*(L + i) <= *(R + j)) {
            *(arr + k) = *(L + i);
            i++;
        } else {
            *(arr + k) = *(R + j);
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = *(L + i);
        i++;
        k++;
    }

    while (j < n2) {
        *(arr + k) = *(R + j);
        j++;
        k++;
    }

    free(L);
    free(R);
}

// -------------------- Merge Sort --------------------
void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
