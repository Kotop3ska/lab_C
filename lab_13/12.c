#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "12.h"


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
