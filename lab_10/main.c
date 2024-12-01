#define arr_type int
#define string_type "%d"
#define ELEM(arr, i) arr[i]
#define LEN(arr) arr[0]
//#define FirstNull
//#define Reverse

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "funcs.inc"

int main() {
    int num_row, num_col;
    do{
        printf("Input size of an array: ");
        scanf("%d %d", &num_row, &num_col);
    } while (num_row <= 0 || num_col <= 0);

    int left, right;
    do {
        printf("Input range for random values: ");
        scanf("%d %d", &left, &right);
    }while (left >= right);

    // Создаем массив указателей на строки
    int** arr = (int**)malloc(num_row * sizeof(int*));
    if (!arr) {
        printf("can`t allocate memory\n");
        return 1;
    }

    // Объявляем массив указателей на функции
    int* (*funcs[])(int* const, int, int, int, int) = {LastNull, DelArr, Insert, Rearrenge};
    int* (*func)(int* const, int, int, int, int) = NULL;

    for (int i = 0; i < num_row; i++) {
        arr[i] = (int*)malloc((num_col + 1) * sizeof(int));
        if (!arr[i]) {
            printf("can`t allocate memory\n");
            return 1;
        }
        arr[i][0] = num_col; // Сохраняем размер массива в первом элементе
    }

    // Заполняем массив случайными значениями
    GenArray(arr, left, right, num_row);
    printf("Array after filling\n");
    Output(arr, num_row);

    int n = 0, k = 0;
    for (int i = 0; i < num_row; i++) {
        func = funcs[(i + 1) % 4];
        if ((i + 1) % 4 == 1) { // Для DelArr
            do {
                printf("Input n, k =  ");
                scanf("%d %d", &n, &k);
            } while (n + k > arr[i][0] + 1 || n <= 0 || k < 1);
        } else if ((i + 1) % 4 == 2) { // Для Insert
            do {
                printf("Input index for insert = ");
                scanf("%d", &n);
            } while (n < 1 || n > arr[i][0]);
        }

        // Применяем функцию
        arr[i] = func(arr[i], n, k, left, right);
        if (!arr[i]) {
            printf("can`t allocate memory\n");
            return 1;
        }

        printf("\nArray after function %d\n", (i % 4) + 1);
        Output(arr, num_row);
    }

    // Освобождаем память
    for (int i = 0; i < num_row; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
