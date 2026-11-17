#include <stdio.h>
#include <stdlib.h>
#include "myarrfunc.h"

int read_int(const char *prompt, int *value) {
    printf("%s", prompt);
    while (scanf("%d", value) != 1) {
        if (feof(stdin)) return 0;
        printf("Некорректный ввод. Повторите попытку: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 1;
}

void print_menu(void) {
    printf("\na   Задать размер массива\n");
    printf("b   Заполнить массив\n");
    printf("c   Представление массива (значения, адреса)\n");
    printf("d   Индексы элементов, значения которых ниже заданного k\n");
    printf("e   Количество элементов массива по значению выше введенного k\n");
    printf("f   Сумма элементов массива по значению ниже введенного k\n");
    printf("g   Выход\n");
    printf("Выберите пункт: ");
}

int main(void) {
    int *arr = NULL;
    size_t n = 0;
    int is_filled = 0;
    char choice;

    while (1) {
        print_menu();

        int res = scanf(" %c", &choice);
        
        if (res == EOF) {
            printf("\nПолучен сигнал конца файла. Завершение работы.\n");
            break;
        }

        int c;
        int extra_chars = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            extra_chars = 1;
        }

        if (extra_chars) {
            printf("Ошибка: введите ровно один символ пункта меню.\n");
            continue;
        }

        switch (choice) {
            case 'a': {
                int temp_n;
                char prompt[64];
                snprintf(prompt, sizeof(prompt), "Введите размер массива (1 - %d): ", MAX_ARRAY_SIZE);
                
                if (!read_int(prompt, &temp_n)) {
                    printf("\nВыход по EOF.\n");
                    free(arr);
                    return 0;
                }
                if (temp_n <= 0 || temp_n > MAX_ARRAY_SIZE) {
                    printf("Ошибка: размер массива должен быть от 1 до %d.\n", MAX_ARRAY_SIZE);
                    break;
                }

                int *new_arr = (int *)realloc(arr, (size_t)temp_n * sizeof(int));
                if (new_arr == NULL) {
                    printf("Ошибка выделения памяти!\n");
                    break;
                }
                arr = new_arr;
                n = (size_t)temp_n;
                is_filled = 0;
                printf("Размер массива установлен: %zu\n", n);
                break;
            }

            case 'b': {
                if (arr == NULL || n == 0) {
                    printf("Сначала задайте размер массива (пункт 'a').\n");
                    break;
                }
                if (fill_array(arr, n) == -1) {
                    printf("\nВвод прерван (получен сигнал EOF или ошибка). Завершение работы.\n");
                    free(arr);
                    return 0;
                }
                is_filled = 1;
                printf("Массив успешно заполнен.\n");
                break;
            }

            case 'c': {
                if (!is_filled) {
                    printf("Массив не создан или не заполнен (выполните пункты 'a' и 'b').\n");
                    break;
                }
                print_array(arr, n);
                break;
            }

            case 'd': { // Функция №5
                if (!is_filled) {
                    printf("Сначала создайте и заполните массив.\n");
                    break;
                }
                int k;
                if (!read_int("Введите пороговое значение k: ", &k)) {
                    free(arr);
                    return 0;
                }

                size_t *indices = (size_t *)malloc(n * sizeof(size_t));
                if (indices == NULL) {
                    printf("Ошибка выделения памяти.\n");
                    break;
                }

                int count = find_indices_below_k(arr, n, k, indices);
                if (count == -1) {
                    printf("Элементы со значением ниже %d не найдены.\n", k);
                } else {
                    printf("Индексы элементов ниже %d: ", k);
                    for (int i = 0; i < count; i++) {
                        printf("%zu ", *(indices + i));
                    }
                    printf("\n");
                }
                free(indices);
                break;
            }

            case 'e': { // Функция №20
                if (!is_filled) {
                    printf("Сначала создайте и заполните массив.\n");
                    break;
                }
                int k;
                if (!read_int("Введите пороговое значение k: ", &k)) {
                    free(arr);
                    return 0;
                }

                int count = count_above_k(arr, n, k);
                if (count == -1) {
                    printf("Ошибка при обработке массива.\n");
                } else if (count == 0) {
                    printf("Элементы со значением выше %d не найдены (количество: 0).\n", k);
                } else {
                    printf("Количество элементов выше %d: %d\n", k, count);
                }
                break;
            }

            case 'f': { // Функция №21
                if (!is_filled) {
                    printf("Сначала создайте и заполните массив.\n");
                    break;
                }
                int k;
                if (!read_int("Введите пороговое значение k: ", &k)) {
                    free(arr);
                    return 0;
                }

                long long sum = 0;
                if (sum_below_k(arr, n, k, &sum) == -1) {
                    printf("Элементы со значением ниже %d не найдены (сумма не вычислена).\n", k);
                } else {
                    printf("Сумма элементов ниже %d: %lld\n", k, sum);
                }
                break;
            }

            case 'g':
                printf("Завершение работы программы.\n");
                free(arr);
                return 0;

            default:
                printf("Неизвестный пункт меню '%c'. Выберите букву от 'a' до 'g'.\n", choice);
                break;
        }
    }

    free(arr);
    return 0;
}

