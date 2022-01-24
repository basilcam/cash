#include <cam/sys/signal.h>
#include <cam/sio.h>
#include <sys/wait.h>
#include "signals.h"
#include "jobs.h"

static void forwarding_handler(int signum) {
    signals_block(); // block signals to be async-signal-safe when accessing global variables
    job *job = jobs_get_fg_job();
    signals_unblock();

    if (job == NULL) {
        return;
    }

    cam_kill(-job->pid, signum); // forward signal to fg process group
}

static void print_status(job *j, const char *reason) {
    cam_sio_puts("[");
    cam_sio_putl((long) job_get_jid(j));
    cam_sio_puts("]   ");
    cam_sio_puts(reason);
    cam_sio_puts(job_get_command(j));
    cam_sio_puts("\n");
}

static void sigchld_handler() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
        signals_block();

        job *j = jobs_get_from_pid(pid);
        job_state state = job_get_state(j);

        if (WIFEXITED(status)) {
            if (state == JOB_STATE_BG) {
                print_status(j, "Done            ");
            }
            jobs_remove(j);
        } else if (WIFSIGNALED(status)) {
            print_status(j, "Killed          ");
            jobs_remove(j);
        } else if (WIFSTOPPED(status)) {
            print_status(j, "Stopped         ");
            job_stop(j);
        }

        signals_unblock();
    }
}

void signals_install_handlers() {
    cam_signal(SIGINT, forwarding_handler);
    cam_signal(SIGTSTP, forwarding_handler);
    cam_signal(SIGCHLD, sigchld_handler);
}

void signals_uninstall_handlers() {
    cam_signal(SIGINT, SIG_DFL);
    cam_signal(SIGTSTP, SIG_DFL);
    cam_signal(SIGCHLD, SIG_DFL);
}

void signals_block() {
    sigset_t set;

    cam_sigemptyset(&set);
    cam_sigaddset(&set, SIGINT);
    cam_sigaddset(&set, SIGTSTP);
    cam_sigaddset(&set, SIGCHLD);

    cam_sigprocmask(CAM_SIGHOW_BLOCK, &set, NULL);
}

void signals_unblock() {
    sigset_t set;

    cam_sigemptyset(&set);
    cam_sigaddset(&set, SIGINT);
    cam_sigaddset(&set, SIGTSTP);
    cam_sigaddset(&set, SIGCHLD);

    cam_sigprocmask(CAM_SIGHOW_UNBLOCK, &set, NULL);
}
