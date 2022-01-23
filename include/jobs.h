#ifndef CAMSHELL_JOBS_H
#define CAMSHELL_JOBS_H

#include <unistd.h>
#include <stdbool.h>
#include "consts.h"
#include "command.h"

typedef enum {
    JOB_STATE_BG,
    JOB_STATE_FG,
    JOB_STATE_INVALID,
} job_state;

typedef struct {
    char command[BUFFER_SIZE];
    pid_t pid;
    size_t jid;
    job_state state;
} job;

job *jobs_add(pid_t pid, command *cmd);

void jobs_remove(pid_t pid);

void jobs_print();

job *jobs_get_fg_job();

const char *job_get_command(job *j);

pid_t job_get_pid(job *j);

size_t job_get_jid(job *j);

job_state job_get_state(job *j);

bool job_is_valid(job *j);

#endif // CAMSHELL_JOBS_H
