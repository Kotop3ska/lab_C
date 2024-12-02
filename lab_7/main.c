#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void InputArray1(int* const arr, const int size_arr, const int left, const int right)
{
    srand(time(0));
    for (int i = 0; i < size_arr; i++) {
        arr[i] = left + rand() % (right - left + 1);
    }
}
void InputArray2(int* const arr1, int* const arr2, const int size_arr)
{
    for (int i = 0; i < size_arr; i++)
    {
        arr2[i] = arr1[i] * arr1[i];
    }
}
void print_array(int* arr, int size_arr) {
    for (int i = 0; i < size_arr; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_arr(int* const arr, int const size_arr)
{
    for (int i = 0; i < size_arr - 1; i++)
    {
        for (int j = 0; j < size_arr - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int *A = NULL;
    int *B = NULL;
    int size_arr, left, right;
    do {
        printf("Input size array A: ");
        scanf("%d", &size_arr);
    } while (size_arr <= 0);

    do {
        printf("Generating range entry (left right): \n");
        scanf("%d %d", &left, &right);
    } while (left >= right);

    A = malloc(sizeof(int) * size_arr);
    InputArray1(A, size_arr, left, right);
    printf("Array A: ");
    print_array(A, size_arr);
    B = malloc(sizeof(int) * size_arr);
    InputArray2(A, B, size_arr);
    free(A);
    sort_arr(B, size_arr);
    printf("Array B: ");
    print_array(B, size_arr);
    
    return 0;
}
