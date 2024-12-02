#ifndef LAB12_H
#define LAB12_H

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


Job *CreateJob(JobTitleType type, unsigned char flags, JobDetails details);
Job **AddJob(Job **jobs, int *count, Job *NewJob);
Job **DelJob(Job **jobs, int *count, int index);
void UpdateJob(Job *job, JobTitleType new_type, unsigned char new_flags, JobDetails new_details);
#endif