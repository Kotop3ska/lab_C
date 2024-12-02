#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "11.h"
#include "12.h"


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

void lab11()
{
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
            {
                printf("Выход из программы.\n");
                exit(0);
            }
            
            default:
                printf("Неверный выбор. Повторите попытку.\n");
        }
    }
}


void PrintJob(Job *job)
{
    printf("Должность сотрудника: ");
    switch (job->type)
    {
        case PROGRAMMER:
            printf("программист\n");
            printf("Имя: %s\n", job->details.programmer.Name);
            printf("Зарплата: %d\n", job->details.programmer.Salary);
            printf("Специализация: %s\n", job->details.programmer.Specialization);
            break;

        case DRIVER:
            printf("Водитель\n");
            printf("Имя: %s\n", job->details.driver.Name);
            printf("Зарплата: %d\n", job->details.driver.Salary);
            printf("Марка машины: %s\n", job->details.driver.CarModel);
            break;
        
        case SECURITY:
            printf("Охранник\n");
            printf("Имя: %s\n", job->details.security.Name);
            printf("Зарплата: %d\n", job->details.security.Salary);
            printf("Время работы: %s\n", job->details.security.DuringWork);
            break;
    }

    printf("Состояния: ");
    if (job->flags & INTERNSHIP)
        printf("проходит стажировку ");
    if (job->flags & FULL_RATE)
        printf("на полной ставке ");
    if (job->flags & DISMISSAL)
        printf("увольняется ");
    if (job->flags & ROMOTION)
        printf("ждет повышения ");
    if (job->flags & EMPLOYEE_OF_THE_YEAR)
        printf("сотрудник года ");
    printf("\n");
}


void PrintAllJobs(Job **jobs, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Сотрудник %d:\n", i + 1);
        PrintJob(jobs[i]);
        printf("\n");
    }
}


void PrintJobByFlags(Job **jobs, int count, unsigned char flagMask)
{
    for (int i = 0; i < count; i++)
    {
        if ((jobs[i]->flags & flagMask) == flagMask)
        {
            PrintJob(jobs[i]);
            printf("\n");
        }
    }
}


void InputString(char *str)
{
    getchar();
    fgets(str, MAX_LENGTH, stdin);
    str[strcspn(str, "\n")] = 0;
}


void InputJobDetails(JobDetails *details, JobTitleType type)
{
    switch (type)
    {
    case PROGRAMMER:
        printf("Введите имя сотрудника: ");
        InputString(details->programmer.Name);
        printf("Введите зарплату: ");
        scanf("%d", &details->programmer.Salary);
        printf("Введите специализацию: ");
        InputString(details->programmer.Specialization);
        break;
    
    case DRIVER:
        printf("Введите имя сотрудника: ");
        InputString(details->driver.Name);
        printf("Введите зарплату: ");
        scanf("%d", &details->driver.Salary);
        printf("Введите марку машины: ");
        InputString(details->driver.CarModel);
        break;

    case SECURITY:
        printf("Введите имя сотрудника: ");
        InputString(details->security.Name);
        printf("Введите зарплату: ");
        scanf("%d", &details->security.Salary);
        printf("Введите время работы: ");
        InputString(details->security.DuringWork);
        break;
    }
}


void lab12()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int count = 0;
    Job **jobs= NULL;
    int choice;
    Job *new_job;
    JobDetails details;
    unsigned char flags;
    int job_index;

    printf("Выберите функцию\n");
    printf("1. Создать сотрудника\n");
    printf("2. Удалить сотрудника из массива\n");
    printf("3. Обновить сотрудника\n");
    printf("4. Вывести всех сотрудников\n");
    printf("5. Вывести сотрудников по заданной комбинации флагов\n");
    printf("6. Выход\n");

    while (true)
    {   
        printf("\n");
        printf("Введите номер операции: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                printf("Выберите должность сотрудника (0 - Программист, 1 - Охранник, 2 - Водитель): ");
                int type;
                scanf("%d", &type);
                
                if (type < 0 || type > 2)
                {
                    printf("Неверная должнось.\n");
                    break;
                }

                printf("Введите флаги состояния сотрудника (введите значение в формате 0x..): ");
                scanf("%hhx", &flags);

                InputJobDetails(&details, (JobTitleType)type);
                new_job = CreateJob((JobTitleType)type, flags, details);
                jobs = AddJob(jobs, &count, new_job);
                printf("Сотрудник создан и добавлен в массив.\n");
                break;

            case 2:
                if (count == 0)
                {
                    printf("Нет сотрудников для обновления.\n");
                    break;
                }

                printf("Введите индекс сотрудника для удаления (1-%d): ", count);
                scanf("%d", &job_index);
                job_index--;

                if (job_index >= 0 && job_index < count)
                {
                    jobs = DelJob(jobs, &count, job_index);
                    printf("Сотрудника удален.\n");
                }
                else
                {
                    printf("Неверный индекс");
                }
                break;

            case 3:
                if (count == 0)
                {
                    printf("Нет сотрудников для обновления.\n");
                    break;
                }

                printf("Введите индекс сотрудника для обновления (1-%d): ", count);
                scanf("%d", &job_index);
                job_index--;

                if (job_index >= 0 && job_index < count)
                {
                    printf("Введите новые данные для сотрудника.\n");
                    printf("Выберите должность сотрудника (0 - Программист, 1 - Водитель, 2 - Охранник): ");
                    scanf("%d", &type);
                

                    if (type < 0 || type > 2)
                    {
                        printf("Неверная должность.\n");
                        break;
                    }

                    printf("Введите новые флаги состояния сотрудника (введите значение в формате 0x..): ");
                    scanf("%hhx", &flags);

                    InputJobDetails(&details, (JobTitleType)type);

                    UpdateJob(jobs[job_index], (JobTitleType)type, flags, details);
                    printf("Сотрудник обновлен.\n");
                }

                else
                {
                    printf("Неверный индекс.\n");
                }
                break;

            case 4:
                printf("Все сотрудники:\n");
                PrintAllJobs(jobs, count);
                break;

            case 5:
                printf("Введите маску флагов для фильтрации сотрудников: ");
                scanf("%hhx", &flags);
                printf("Сотрудники с указанной комбинацией флагов:\n");
                PrintJobByFlags(jobs, count, flags);
                break;

            case 6:
                printf("Выход из программы.\n");
                for (int i = 0; i < count; i++)
                {
                    free(jobs[i]);
                }
                free(jobs);
                exit(0);
            
            default:
                printf("Неверный выбор. Повторите попытку.\n");
        }
    }

}


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int choice;

    while (true)
    {
        printf("Выберите лабораторную работу:\n"
        "1. Лабораторная работа 11\n"
        "2. Лабораторная работа 12\n"
        "3. Выход\n");
        printf("\n");
        printf("Введите номер: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                lab11();
                break;
            case 2:
                lab12();
                break;
            case 3:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Некорректный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }
}