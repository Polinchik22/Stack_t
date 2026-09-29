#ifndef STACK_T
#define STACK_T

#include <assert.h>
#include <stdlib.h>

// const int poison = srand(time(NULL));

#define STACK_DEBUG_ON

#ifdef STACK_DEBUG_ON
#define ON_DEBUG (...) Stack_info = {__VA_ARGS__}
#else
#define ON_DEBUG (...)
#endif


#define StackCtor (...) StackCtor (__FILE__,      \
                                   __FUNCTION__,  \
                                   __LINE__,      \
                                   __VA_ARGS__)

#define POISON(stack_elem_t) _Generic((stack_elem_t) \
    int: srand(time(NULL)) \
    double: NaN       \
    float: NaN \
    char: NULL
    default: NULL \
    \\ TODO спросить че прописывать
)

struct Stack_info {
    const char* stack_name;
    const char* file_name;
    const char* function_name;
    int         line_number;
}

struct Stack_t {
    ON_DEBUG();
    double* data;
    int size;
    int capacity;
}


int StackCtor (Stack_t* stack,
               int      capacity);

int StackPush (Stack_t*       stack,
               stack_elem_t   value);

int StackDtor (Stack_t* stack);

#endif
