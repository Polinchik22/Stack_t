#include "Stack_t.h"

What_error StackCtor (const char* file_name,
               const char* function_name,
               int         line_number,
               const char* stack_name, //Вопрос, можено ли это как то сделать не аргументом который вводят руками
               Stack_t*    stack,
               int         capacity) {

    // TODO все занулено?

    stack->data = (stack_elem_t*) calloc(stack->size, sizeof(stack_elem_t));
    NullingData(stack);
    stack->Stack_info = {.stack_name    = stack_name, //TODO сделать макрос на имя
                         .file_name     = file_name,
                         .function_name = function_name,
                         .line_number   = line_number};



    return stack->stack_errors;
    }


What_error StackPush (Stack_t*       stack,
               stack_elem_t   value) {

    resizing_stack(stack);
    (stack->data)[stack->size++] = value;

    return stack->stack_errors;
    }


stack_elem_t StackPop (Stack_t* stack) {
    return stack->data[stack->size--];
}


int StackDtor (Stack_t* stack) {
    NullingData(stack);
    free(stack->data);
    stack = NULL;
}


void NullingData (Stack_t* stack) {
    for (int ind = 0; ind < stack->capacity; ind++) {
        stack->data[ind] = POISON(stack_elem_t);
    }
    stack->stack_errors = POISON_FOR_ERROR_VALUE;
}


What_error StackOkey (Stack_t* stack) {
    if (!stack) {return NULL_ADDRESS;}

    if (stack->size > stack->capacity) {return SIZE_BIGGER_THEN_CAPACITY;}

    return ALL_IS_OK;
}

void resizing_stack(Stack_t* stack) {
    if (stack->size == stack->capacity) {
        up_capacity(stack);
        //TODO проверки
    } else if (stack->capacity >= THRESHOLD_FOR_DOWN_ALLOCATION  && stack->size * 4 < stack->capacity) {
        down_capacity(stack);
    }
}


void up_capacity(Stack_t* stack) {
    void* temp_pointer = realloc(stack->data, (stack->capacity)*2);
    if (temp_pointer) {
        stack->data = (stack_elem_t*) temp_pointer;
        stack->capacity *= 2;
        NullingData(stack);
    } else {
        stack->stack_errors = REALLOC_TO_UP_PROBLEM;
    }
}


void down_capacity(Stack_t* stack) {
    void* temp_pointer = realloc(stack->data, (stack->capacity) / 2);
    if (temp_pointer) {
        stack->data = (stack_elem_t*)temp_pointer;
        stack->capacity /= 2;
    } else {
        stack->stack_errors = REALLOC_TO_DOWN_PROBLEM;
    }
}



