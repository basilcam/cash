#include <stdio.h>
#include <stdlib.h>
#include <cam/sys/io.h>
#include "consts.h"
#include "evaluate.h"

int main() {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("> ");
        
        cam_fgets(buffer, BUFFER_SIZE, stdin);

        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        }

        evaluate(buffer);
    }
}
