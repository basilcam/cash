#include <cam/sys/signal.h>
#include <cam/sio.h>
#include <sys/wait.h>
#include "signals.h"
#include "jobs.h"

static void signals_forwarding_handler(int signum) {
    signals_block(); // block signals to be async-signal-safe when accessing global variables
    job *job = jobs_get_fg_job();
    signals_unblock();

    if (job == NULL) {
        return;
    }

    cam_kill(-job->pid, signum); // forward signal to fg process group
}

static void signals_sigchld_handler() {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) { // terminated normally
            signals_block();
            jobs_remove(pid);
            signals_unblock();
        } else if (WIFSIGNALED(status)) { // terminated due to signal, print info
            signals_block();
            job *j = jobs_get_from_pid(pid);
            cam_sio_puts("[");
            cam_sio_putl((long) job_get_jid(j));
            cam_sio_puts("]   Killed            ");
            cam_sio_puts(job_get_command(j));
            cam_sio_puts("\n");
        }
    }
}

void signals_install_handlers() {
    cam_signal(SIGINT, signals_forwarding_handler);
    cam_signal(SIGTSTP, signals_forwarding_handler);
    cam_signal(SIGCHLD, signals_sigchld_handler);
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
