#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#define MAX_FILENAME_LEN 128


typedef struct 
{
    float elements[3][3];
    bool identiti;
} Matrix3x3;


typedef struct 
{
    int operation;
    float elements1[3][3];
    float elements2[3][3];
    Matrix3x3 m1;
    Matrix3x3 m2;
    float scal;
    float det;
    Matrix3x3 result_m;
} OperationRecord;



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

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new_matrix.elements[i][j] = 0.0f;
        }
    }

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
    for (int i = 0; i < 3; i++)
    {
        scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
    }
    printf("\n");
}



void writeFile()
{
    char filename[MAX_FILENAME_LEN];
    printf("Введите имя файла для записи данных: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    int choice;
    OperationRecord record;

    printf("1 – Создание матрицы\n"
    "2 – Сумма 2 матриц\n"
    "3 – Произведение 2 матриц\n"
    "4 – Умножение матрицы на скаляр\n" 
    "5 – Транспонирование матрицы\n"
    "6 – Найти определитель матрицы\n"
    "7 – Определить обратную матрицу\n"
    "8 – Завершить запись\n\n");

    while (true)
    {
        printf("\nВведите номер операции: ");
        scanf("%d", &choice);

        if (choice == 8)
        {
            break;
        }

        record.operation = choice;

        switch (choice)
        {
        case 1:
            printf("\nВведите матрицу:\n");
            InputElements(record.elements1);
            record.m1 = CreateMatrix(record.elements1);
            break;

        case 2:
        case 3:
            printf("\nВведите матрицу 1:\n");
            InputElements(record.elements1);
            record.m1 = CreateMatrix(record.elements1);

            printf("\nВведите матрицу 2:\n");
            InputElements(record.elements2);
            record.m2 = CreateMatrix(record.elements2);
            break;

        case 4:
            printf("\nВведите матрицу:\n");
            InputElements(record.elements1);
            record.m1 = CreateMatrix(record.elements1);
            printf("Введите скаляр: ");
            scanf("%f", &record.scal);
            break;

        case 5:
        case 6:
        case 7:
            printf("\nВведите матрицу:\n");
            InputElements(record.elements1);
            record.m1 = CreateMatrix(record.elements1);
            break;

        default:
            printf("Неверный выбор. Повторите попытку.\n");
            continue;
        }
        fwrite(&record, sizeof(OperationRecord), 1, file);
    }
    fclose(file);
    printf("Данные записаны в файл %s\n", filename);
}


void processFile()
{
    char inputFile[MAX_FILENAME_LEN], outputFile[MAX_FILENAME_LEN];
    printf("Введите имя файла с данными: ");
    scanf("%s", inputFile);
    printf("Введите имя файла для записи результатов: ");
    scanf("%s", outputFile);

    FILE *in = fopen(inputFile, "rb");
    FILE *out = fopen(outputFile, "wb");

    if (!in || !out)
    {
        printf("Ошибка открытия файла.\n");
        return;
    }

    OperationRecord record;
    while (fread(&record, sizeof(OperationRecord), 1, in) == 1)
    {
        switch (record.operation)
        {
            case 1:
            {
                record.result_m = record.m1;
            }
            break;

            case 2:
            {
                record.result_m = SumMatrix(record.m1, record.m2);
            }
            break;

            case 3:
            {
                record.result_m = MulMatrix(record.m1, record.m2);
            }
            break;
            
            case 4:
            {
                MulScal(&record.m1, record.scal);
                record.result_m = record.m1;
            }
            break;
            
            case 5:
            {
                Transpose(&record.m1);
                record.result_m = record.m1;
            }
            break;
            
            case 6:
            {
                record.det = DetMatrix(&record.m1);
            }
            break;

            case 7:
            {
                InvMatrix(&record.m1);
                record.result_m = record.m1;
            }
             break;

        }
        fwrite(&record, sizeof(OperationRecord), 1, out);
    }
    fclose(in);
    fclose(out);
    printf("Результаты записаны в файл %s\n", outputFile);
}


void readResultsFile()
{
    char filename[MAX_FILENAME_LEN];
    printf("Введите имя файла с результатами: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Ошибка открытия файла.\n");
        return;
    }

    OperationRecord record;

    while (fread(&record, sizeof(OperationRecord), 1, file) == 1)
    {
        printf("\nОперация: %d\n", record.operation);

        switch (record.operation)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 7:
                printf("\nПолученная матрица:\n");
                PrintMatrix(&record.result_m);
                break;

            case 6:
                printf("\nОпределитель матрицы: %f\n", record.det);   
        }
    }
    fclose(file);
}


int main()
{
    int mode;
    while (1)
    {
        printf("\nВыберите режим работы:\n");
        printf("1. Запись данных\n");
        printf("2. Обработка данных\n");
        printf("3. Чтение результатов\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &mode);

        switch (mode)
        {
        case 1:
            writeFile();
            break;
        case 2:
            processFile();
            break;
        case 3:
            readResultsFile();
            break;
        case 0:
            printf("Выход из программы.\n");
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
