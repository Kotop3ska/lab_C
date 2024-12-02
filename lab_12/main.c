#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_LENGTH 50
#define INTERNSHIP 0x01
#define FULL_RATE 0x02
#define DISMISSAL 0x04
#define ROMOTION 0x08
#define EMPLOYEE_OF_THE_YEAR 0x10

typedef enum 
{
    PROGRAMMER,
    SECURITY,
    DRIVER,
} JobTitleType;


typedef struct
{
    char Name[MAX_LENGTH];
    int Salary;
    char Specialization[MAX_LENGTH];
} ProgrammerInfo;


typedef struct
{
    char Name[MAX_LENGTH];
    int Salary;
    char DuringWork[MAX_LENGTH];
} SecurityInfo;


typedef struct
{
    char Name[MAX_LENGTH];
    int Salary;
    char CarModel[MAX_LENGTH];
} DriverInfo;


typedef union
{
    ProgrammerInfo programmer;
    SecurityInfo security;
    DriverInfo driver;
} JobDetails;


typedef struct 
{
    JobTitleType type;
    JobDetails details;
    unsigned char flags;
} Job;


Job *CreateJob(JobTitleType type, unsigned char flags, JobDetails details)
{
    Job *NewJob = (Job *)malloc(sizeof(Job));
    if (NewJob)
    {
        NewJob->type = type;
        NewJob->flags = flags;
        NewJob->details = details;
    }
    return NewJob;
}


Job **AddJob(Job **jobs, int *count, Job *NewJob)
{
    jobs = (Job**)realloc(jobs, (*count + 1) * sizeof(Job *));
    if (jobs)
    {
        jobs[*count] = NewJob;
        (*count)++;
    }
    return jobs;
}


Job **DelJob(Job **jobs, int *count, int index)
{
    if (index >= 0 && index < *count)
    {
        free(jobs[index]);
        for (int i = index; i < *count - 1; i++)
        {
            jobs[i] = jobs[i + 1];
        }
        (*count)--;
        jobs = (Job**)realloc(jobs, (*count) * sizeof(Job *));
    }
    return jobs;
}


void UpdateJob(Job *job, JobTitleType new_type, unsigned char new_flags, JobDetails new_details)
{
    job->type = new_type;
    job->flags = new_flags;
    job->details = new_details;
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
            printf("Имя: %S\n", job->details.security.Name);
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
        printf("Событие %d:\n", i + 1);
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

int main()
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
                return 0;
            
            default:
                printf("Неверный выбор. Повторите попытку.\n");
        }
    }

}
