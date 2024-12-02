#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Генерация массива случайных чисел в указанном диапазоне
void GenArray(int** const arr, int left, int right, int num_row) {
    srand(time(0));
    for (int i = 0; i < num_row; i++) {
        for (int j = 1; j <= arr[i][0]; j++) { // Индексация с 1
            arr[i][j] = left + rand() % (right - left + 1);
        }
    }
}

// Вывод массива
void Output(int** arr, int num_row) {
    for (int i = 0; i < num_row; i++) {
        for (int j = 1; j <= arr[i][0]; j++) { // Индексация с 1
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Удаление элементов из массива
int* DelArr(int* const row, int n, int k, int left, int right) {
    int *src = row + k + n; // Указатель на начало оставшейся части
    int *dest = row + k;    // Указатель на место, куда сдвигаем
    int *end = row + row[0] + 1; // Указатель на конец массива 
    while (src < end) {
        *dest++ = *src++;
    }

    int new_size = row[0] - n;
    row[0] = new_size;
    int* new_p = realloc(row, (new_size + 1) * sizeof(int));
    return new_p;
}

// Вставка случайного элемента в массив
int* Insert(int* const row, int ind, int k, int left, int right) {
    int new_size = row[0] + 1;

    // Расширяем память
    int* new_p = realloc(row, (new_size + 1) * sizeof(int));
    if (!new_p) {
        printf("Error: Memory allocation failed\n");
        return row;
    }

    // Сдвиг элементов вправо начиная с индекса `ind`
    int* src = new_p + new_p[0]; // Указатель на конец текущего массива
    int* dest = src + 1;       // Указатель на новую позицию
    while (src >= new_p + ind) {
        *dest-- = *src--;
    }

    // Вставляем случайный элемент на позицию `ind`
    int random_value = left + rand() % (right - left + 1);
    new_p[ind] = random_value;

    // Обновляем размер массива в первой ячейке
    new_p[0] = new_size;
    return new_p;
}

// Перестановка четных и нечетных элементов
int* Rearrenge(int* const row, int n, int k, int left, int right) {
    int start = 1;            // Указатель на первый элемент данных
    int end = row[0];         // Указатель на последний элемент данных

    while (start < end) {
        // Если элемент с начала уже четный, пропускаем
        if (row[start] % 2 == 0) {
            start++;
        }
        // Если элемент с конца уже нечетный, пропускаем
        else if (row[end] % 2 != 0) {
            end--;
        }
        // Если найден нечетный элемент в начале и четный в конце — меняем их
        else {
            int temp = row[start];
            row[start] = row[end];
            row[end] = temp;

            start++;
            end--;
        }
    }

    return row;
}


// Обнуление последнего четного элемента
int* LastNull(int* const row, int n, int k, int left, int right) {
    int* ptr = row + row[0]; // Указатель на последний элемент массива
    while (ptr > row) {      // Пока не дойдем до элемента row[1]
        if (*ptr % 2 == 0) { // Если значение четное
            *ptr = 0;        // Обнуляем
            return row;      // Возвращаем массив
        }
        ptr--; // Переход к предыдущему элементу
    }
    return row; // Если четных элементов нет, возвращаем массив без изменений
}

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
