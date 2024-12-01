void GenArray(arr_type** const arr, int const left, int const right, int const num_row)
{
    srand(time(NULL));
    int i;
    int j;
    for (i = 0; i < num_row; i++)
    {
        for (j = 1; j <= LEN(arr[i]); j++)
        {
            ELEM(arr[i], j) = left + rand() % (right - left + 1);
        }
    }
}


void Output(arr_type** const arr, int A) {
    for (int i = 0; i < A; i++)
    {
        for (int j = 1; j <= LEN(arr[i]); j++)
        {
            printf(string_type " ", ELEM(arr[i], j));
        }
        printf("\n");
    }
    printf("\n");
}


// Удаление элементов из массива
arr_type* DelArr(arr_type* const row, int n, int k, int left, int right) {
    int i = k;
    int j = k + n;
    while (j <= LEN(row)) {
        ELEM(row, i++) = ELEM(row, j++);
    }

    int new_size = LEN(row) - n;
    LEN(row) = new_size;
    arr_type* new_p = realloc(row, (new_size + 1) * sizeof(int));
    return new_p;
}

// Вставка случайного элемента в массив
arr_type* Insert(arr_type* const row, int ind, int k, int left, int right) {
    int new_size = LEN(row) + 1;

    // Расширяем память
    arr_type* new_p = realloc(row, (new_size + 1) * sizeof(int));
    if (!new_p) {
        printf("Error: Memory allocation failed\n");
        return row;
    }

    // Сдвиг элементов вправо начиная с индекса `ind`
    int i = LEN(new_p);
    int j = i + 1;
    while (i >= ind) {
        ELEM(row, j--) = ELEM(row, i--);
    }

    // Вставляем случайный элемент на позицию `ind`
    int random_value = left + rand() % (right - left + 1);
    ELEM(row, ind) = random_value;

    // Обновляем размер массива в первой ячейке
    LEN(new_p) = new_size;
    return new_p;
}

// Перестановка четных и нечетных элементов
arr_type* Rearrenge(arr_type* const row, int n, int k, int left, int right) 
{
    #ifdef Reverse
    int start = 1;            // Указатель на первый элемент данных
    int end = LEN(row);         // Указатель на последний элемент данных

    while (start < end) {
        // Если элемент с начала уже четный, пропускаем
        if (ELEM(row, start) % 2 != 0) {
            start++;
        }
        // Если элемент с конца уже нечетный, пропускаем
        else if (ELEM(row, end) % 2 == 0) {
            end--;
        }
        // Если найден нечетный элемент в начале и четный в конце — меняем их
        else {
            int temp = ELEM(row, start);
            ELEM(row, start) = ELEM(row, end);
            ELEM(row, end) = temp;

            start++;
            end--;
        }
    }
    #else
    int start = 1;            // Указатель на первый элемент данных
    int end = LEN(row);         // Указатель на последний элемент данных

    while (start < end) {
        // Если элемент с начала уже четный, пропускаем
        if (ELEM(row, start) % 2 == 0) {
            start++;
        }
        // Если элемент с конца уже нечетный, пропускаем
        else if (ELEM(row, end) % 2 != 0) {
            end--;
        }
        // Если найден нечетный элемент в начале и четный в конце — меняем их
        else {
            int temp = ELEM(row, start);
            ELEM(row, start) = ELEM(row, end);
            ELEM(row, end) = temp;

            start++;
            end--;
        }
    }
    #endif
    return row;
}


// Обнуление последнего четного элемента
arr_type* LastNull(arr_type* const row, int n, int k, int left, int right) {
    #ifdef FirstNull
    int i = 1;
    while (i < LEN(row)) {      // Пока не дойдем до элемента row[1]
        if (ELEM(row, i) % 2 == 0) { // Если значение четное
            ELEM(row, i) = 0;        // Обнуляем
            break;     // Возвращаем массив
        }
        i++; // Переход к предыдущему элементу
    }

    #else
    int i = LEN(row);
    while (i > 0) {      // Пока не дойдем до элемента row[1]
        if (ELEM(row, i) % 2 == 0) { // Если значение четное
            ELEM(row, i) = 0;        // Обнуляем
            break;      // Возвращаем массив
        }
        i--; // Переход к предыдущему элементу
    }
    #endif
    return row; // Если четных элементов нет, возвращаем массив без изменений
}
