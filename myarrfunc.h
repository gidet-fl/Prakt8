#ifndef MYARRFUNC_H
#define MYARRFUNC_H

#include <stddef.h>

#define MAX_ARRAY_SIZE 1000

int fill_array(int *arrptr, size_t n);

void print_array(const int *arrptr, size_t n);

// Функция №5: Поиск индексов элементов, значения которых ниже заданного k.
// Записывает индексы в out_indices.
int find_indices_below_k(const int *arrptr, size_t n, int k, size_t *out_indices);

// Функция №20: Подсчет элементов массива со значением выше введенного k.
int count_above_k(const int *arrptr, size_t n, int k);

// Функция №21: Сумма элементов массива со значением ниже введенного k.
// Результат записывается по указателю sum.
int sum_below_k(const int *arrptr, size_t n, int k, long long *sum);

#endif

