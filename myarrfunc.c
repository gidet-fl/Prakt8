#include "myarrfunc.h"
#include <stdio.h>

int fill_array(int *arrptr, size_t n) {
    if (arrptr == NULL || n == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < n; i++) {
        printf("Элемент [%zu]: ", i);
        while (scanf("%d", arrptr + i) != 1) {
            if (feof(stdin)) {
                return -1;
            }
            printf("Ошибка ввода. Введите целое число для элемента [%zu]: ", i);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}

void print_array(const int *arrptr, size_t n) {
    if (arrptr == NULL || n == 0) return;

    printf("\nИндекс | Значение   | Адрес в памяти\n");
    printf("----------------------------------------\n");
    for (size_t i = 0; i < n; i++) {
        printf("%-6zu | %-10d | %p\n", i, *(arrptr + i), (void *)(arrptr + i));
    }
    printf("\n");
}

int find_indices_below_k(const int *arrptr, size_t n, int k, size_t *out_indices) {
    if (arrptr == NULL || out_indices == NULL || n == 0) {
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(arrptr + i) < k) {
            *(out_indices + count) = i;
            count++;
        }
    }

    return (count > 0) ? count : -1;
}

int count_above_k(const int *arrptr, size_t n, int k) {
    if (arrptr == NULL || n == 0) {
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(arrptr + i) > k) {
            count++;
        }
    }

    return count;
}

int sum_below_k(const int *arrptr, size_t n, int k, long long *sum) {
    if (arrptr == NULL || sum == NULL || n == 0) {
        return -1;
    }

    *sum = 0;
    int found = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(arrptr + i) < k) {
            *sum += *(arrptr + i);
            found = 1;
        }
    }

    return found ? 0 : -1;
}

