#include <stdio.h>
#include <locale.h>
#include <stdbool.h>


typedef struct 
{
    float elements[3][3];
    bool identiti;
} Matrix3x3;


Matrix3x3 CreateMatrix(float const elements[3][3])
{
    Matrix3x3 matrix;
    matrix.identiti = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix.elements[i][j] = elements[i][j];
            if ((i == j && elements[i][j] != 1) || (i != j & elements[i][j] != 0))
            {
                matrix.identiti = false;
            }
        }
    }
    return matrix;
}


Matrix3x3 SumMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2)
{
    Matrix3x3 new_matrix;
    new_matrix.identiti = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            new_matrix.elements[i][j] = matrix1.elements[i][j] + matrix2.elements[i][j];

            if ((i == j && new_matrix.elements[i][j] != 1) || (i != j && new_matrix.elements[i][j] != 0))
            {
                new_matrix.identiti = false;
            }
        }
    }
    return new_matrix;
}


Matrix3x3 MulMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2)
{
    Matrix3x3 new_matrix;
    new_matrix.identiti = true;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                new_matrix.elements[i][j] += matrix1.elements[i][k] * matrix2.elements[k][j];
            }

            if ((i == j && new_matrix.elements[i][j] != 1) || (i != j && new_matrix.elements[i][j] != 0))
            {
                new_matrix.identiti = false;
            }
        }
    }
    return new_matrix;
}


void MulScal(Matrix3x3* matrix, float a)
{
    matrix->identiti = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix->elements[i][j] = matrix->elements[i][j] * a;

            if ((i == j && matrix->elements[i][j] != 1) || (i != j && matrix->elements[i][j] != 0))
            {
                matrix->identiti = false;
            }
        }
    }
}


void Transpose(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                float temp = matrix->elements[i][j];
                matrix->elements[i][j] = matrix->elements[j][i];
                matrix->elements[j][i] = temp;
            }
        }
    }
}


float DetMatrix(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
    float det;
    det = matrix->elements[0][0] * (matrix->elements[1][1] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][1]) -
        matrix->elements[0][1] * (matrix->elements[1][0] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][0]) +
        matrix->elements[0][2] * (matrix->elements[1][0] * matrix->elements[2][1] - matrix->elements[1][1] * matrix->elements[2][0]);

    return det;
    }

    else
        return 1;
}


void InvMatrix(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
        float det = DetMatrix(matrix);

        if (det == 0)
        {
            printf("Error: Nul Det");
            return;
        }

        float cofactors[3][3] = 
        {{
            (matrix->elements[1][1] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][1]),
            -(matrix->elements[1][0] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][0]),
            (matrix->elements[1][0] * matrix->elements[2][1] - matrix->elements[1][1] * matrix->elements[2][0]) 
        },

        {
            -(matrix->elements[0][1] * matrix->elements[2][2] - matrix->elements[0][2] * matrix->elements[2][1]), 
            (matrix->elements[0][0] * matrix->elements[2][2] - matrix->elements[0][2] * matrix->elements[2][0]),
            -(matrix->elements[0][0] * matrix->elements[2][1] - matrix->elements[0][1] * matrix->elements[2][0])
        },

        {
            (matrix->elements[0][1] * matrix->elements[1][2] - matrix->elements[0][2] * matrix->elements[1][1]), 
            -(matrix->elements[0][0] * matrix->elements[1][2] - matrix->elements[0][2] * matrix->elements[1][0]),
            (matrix->elements[0][0] * matrix->elements[1][1] - matrix->elements[0][1] * matrix->elements[1][0])  
        }};
        
        Matrix3x3 cof = CreateMatrix(cofactors);


        Transpose(&cof);
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix->elements[i][j] = cof.elements[i][j] / det;
            }
        }

    }
}


void PrintMatrix(const Matrix3x3* matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.1f ", matrix->elements[i][j]);
        }
        printf("\n");
    }
    if (matrix->identiti)
        printf("single");
    else
        printf("not single");
}


void InputElements(float elements[3][3])
{
     printf("Введите матрицу:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
    printf("\n");
}


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    printf("1 – Создание матрицы\n"
    "2 – Сумма 2 матриц\n"
    "3 – Произведение 2 матриц\n"
    "4 – Умножение матрицы на скаляр\n" 
    "5 – Транспонирование матрицы\n"
    "6 – Найти определитель матрицы\n"
    "7 – Определить обратную матрицу\n"
    "8 – Выход\n\n");

    int num;
    while (true)
    {
        printf("\nВыберите функцию: ");
        scanf("%d", &num);

        switch (num)
        {
            case 1:
            {
                float elements[3][3];
                InputElements(elements);
                Matrix3x3 matrix = CreateMatrix(elements);
                printf("Ваша матрица:\n");
                PrintMatrix(&matrix);
                break;
            }

            case 2:
            {
                float elements1[3][3];
                float elements2[3][3];

                InputElements(elements1);
                InputElements(elements2);

                Matrix3x3 matrix1 = CreateMatrix(elements1);
                Matrix3x3 matrix2 = CreateMatrix(elements2);

                printf("\n");
                printf("Ваша матрица 1:\n");
                PrintMatrix(&matrix1);
                printf("\n");
                printf("\n");
                printf("Ваша матрица 2:\n");
                PrintMatrix(&matrix2);
                
                Matrix3x3 new_matrix = SumMatrix(matrix1, matrix2);
                printf("\n\nСумма 2 матриц:\n");
                PrintMatrix(&new_matrix);
                break;
            }
            case 3:
            {
                float elements1[3][3];
                float elements2[3][3];

                InputElements(elements1);
                InputElements(elements2);

                Matrix3x3 matrix1 = CreateMatrix(elements1);
                Matrix3x3 matrix2 = CreateMatrix(elements2);

                printf("\n");
                printf("Ваша матрица 1:\n");
                PrintMatrix(&matrix1);
                printf("\n");
                printf("\n");
                printf("Ваша матрица 2:\n");
                PrintMatrix(&matrix2); 

                Matrix3x3 new_matrix = MulMatrix(matrix1, matrix2);
                printf("\n\nПроизведение 2 матриц:\n");
                PrintMatrix(&new_matrix);
                break;
            }

            case 4:
            {
                float elements[3][3];
                InputElements(elements);
                Matrix3x3 matrix = CreateMatrix(elements);
                printf("\n");

                printf("Ваша матрица:\n");
                PrintMatrix(&matrix);
                printf("\n");
        
                float a;
                printf("\nВведите a: ");
                scanf("%f", &a);
                printf("\n");

                MulScal(&matrix, a);
                printf("Матрица, умноженная на скаляр:\n");
                PrintMatrix(&matrix);
                break;
            }
            
            case 5:
            {
                float elements[3][3];
                InputElements(elements);
                Matrix3x3 matrix = CreateMatrix(elements);
                printf("\n");

                printf("Ваша матрица:\n");
                PrintMatrix(&matrix);
                printf("\n");

                Transpose(&matrix);
                printf("\nТранспонированная матрица:\n");
                PrintMatrix(&matrix);
                break;
            }

            case 6:
            {
                float elements[3][3];
                InputElements(elements);
                Matrix3x3 matrix = CreateMatrix(elements);
                printf("\n");

                printf("Ваша матрица:\n");
                PrintMatrix(&matrix);
                printf("\n");

                float det = DetMatrix(&matrix);
                printf("\nОпределитель матрицы: %f", det);
                break;
            }

            case 7:
            {
                float elements[3][3];
                InputElements(elements);
                Matrix3x3 matrix = CreateMatrix(elements);
                printf("\n");

                printf("Ваша матрица:\n");
                PrintMatrix(&matrix);
                printf("\n");

                InvMatrix(&matrix);
                printf("\nОбратная матрица:\n");
                PrintMatrix(&matrix);
                break;
            }

            case 8:
                printf("Выход из программы.\n");
                return 0;
            
            default:
                printf("Неверный выбор. Повторите попытку.\n");
        }
    }
}