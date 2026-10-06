#ifndef STACK_T
#define STACK_T

#ifndef STACK_ELEM_T_DEFINED
    typedef int stack_elem_t;
#endif

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


const int random_int = rand();
#define POISON(stack_elem_t) (stack_elem_t) random_int


const int THRESHOLD_FOR_DOWN_ALLOCATION = 2000;

#define STACK_DEBUG_ON


enum What_error {
    POISON_FOR_ERROR_VALUE,
    ALL_IS_OK,
    NULL_ADDRESS,
    SIZE_BIGGER_THEN_CAPACITY,
    REALLOC_TO_UP_PROBLEM,
    REALLOC_TO_DOWN_PROBLEM
};


// #ifdef STACK_DEBUG_ON
// #define ON_DEBUG (...) Stack_info = {__VA_ARGS__} //TODO remnaming
// #else
// #define ON_DEBUG (...)
// #endif



//#define StackCtor(stack_name, stack, capacity) StackCtor (__FILE__,      \
//                                                        __FUNCTION__,  \
//                                                        __LINE__,      \
//                                                        stack_name, \
//                                                        stack, \
//                                                        capacity)


struct Stack_info_t {
    const char* stack_name;
    const char* file_name;
    const char* function_name;
    int         line_number;
};

struct Stack_t {
    // ON_DEBUG();
    stack_elem_t* data;
    int size;
    int capacity;
    Stack_info_t Stack_info;
    What_error stack_errors;
};


What_error StackCtor (const char* file_name,
               const char* function_name,
               int         line_number,
               const char* stack_name, //Вопрос, можено ли это как то сделать не аргументом который вводят руками
               Stack_t*    stack,
               int         capacity);


What_error StackPush (Stack_t*       stack,
               stack_elem_t   value);

stack_elem_t StackPop (Stack_t* stack);

int StackDtor (Stack_t* stack);

void NullingData (Stack_t* stack);

What_error StackOkey (Stack_t* stack);

void resizing_stack(Stack_t* stack);

void up_capacity(Stack_t* stack);

void down_capacity(Stack_t* stack);

#endif
