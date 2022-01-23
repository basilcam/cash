#ifndef CAMSHELL_BUILTIN_H
#define CAMSHELL_BUILTIN_H

#include <stdlib.h>

typedef enum {
    BUILTIN_NONE,
    BUILTIN_EXIT,
    BUILTIN_JOBS,
    BUILTIN_FG,
    BUILTIN_BG,
    BUILTIN_CD
} builtin;

void builtin_handle(builtin builtin);

#endif // CAMSHELL_BUILTIN_H
