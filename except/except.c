#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "except.h"

Except_Frame *except_stack = NULL;

void Except_raise(const Except_T *exception, const char *file, const int line)
{
    Except_Frame *p = except_stack;

    assert(exception);
    if(p == NULL) {
        fprintf(stderr, "Uncaough exception");
        if(exception->reason)
            fprintf(stderr, " %s", exception->reason);
        else
            fprintf(stderr, " at 0x%p", exception);
        if(file && line > 0)
            fprintf(stderr, "aborting...\n");
        fflush(stderr);
        abort();
    }

    p->exception = exception;
    p->file = file;
    p->line = line;

    except_stack = except_stack->prev;
    longjmp(p->env, except_raised);
}
