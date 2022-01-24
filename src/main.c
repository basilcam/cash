#include <stdio.h>
#include <stdlib.h>
#include <cam/sys/io.h>
#include "consts.h"
#include "evaluate.h"
#include "signals.h"
#include "jobs.h"

int main() {
    char buffer[BUFFER_SIZE];

    signals_install_handlers();
    jobs_init();

    while (1) {
        printf("> ");
        fflush(stdout);

        cam_fgets(buffer, BUFFER_SIZE, stdin);

        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        }

        evaluate(buffer);
    }
}
