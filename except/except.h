#ifndef EXCEPT_H
#define EXCEPT_H
#include <setjmp.h>

enum
{
    except_entered = 0,
    except_raised,
    except_handled,
    except_finalized
};

typedef struct except_t
{
    const char *reason;
} Except_T;

typedef struct Except_frame Except_Frame;
struct Except_frame {
    Except_Frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const Except_T *exception;
};

extern Except_Frame *except_stack;
void Except_raise(const Except_T *exception, const char *file, int line);

#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)

#define RERAISE Excpet_raise(except_frame.exception, \
        except_frame.file, except_frame.line)

#define RETURN switch (except_stack = except_stack->prev, 0) default: return

#define TRY do {    \
    volatile int except_flag;   \
    Except_Frame except_frame;  \
    except_frame.prev = except_stack;   \
    except_stack = &except_frame;   \
    except_flag = setjmp(except_frame.env); \
    if(except_flag == except_entered) {

#define EXCEPT(e)   \
        if(except_flag == except_entered) except_stack = except_stack->prev;  \
    } else if(except_frame.exception == &(e)) { \
        except_flag = except_handled;

#define ELSE    \
        if(except_flag == except_entered) except_stack = except_stack->prev;  \
    } else {    \
        except_flag = except_handled;

#define FINALLY     \
        if(except_flag == except_entered) except_stack = except_stack->prev; \
    } { \
        if(except_flag == except_entered)   \
            except_flag = except_finalized;

#define END_TRY     \
        if(except_flag == except_entered) except_stack = except_stack->prev;  \
    } if(except_flag == except_raised) RERAISE; \
} while(0)

#endif
