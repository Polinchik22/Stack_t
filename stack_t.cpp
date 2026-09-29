#include "Stack_t.h"

int StackCtor (const char* file_name,
               const char* function_name,
               int         line_number,
               const char* Stack_t* stack,
               int         capacity) {

    assert(stack);
    // TODO все занулено?

    stack->data = (stack_elem_t*) calloc(stack->size, sizeof(stack_elem_t));
    stack->Stack_info = {.stack_name    = #stack,
                         .file_name     = file_name,
                         .function_name = function_name,
                         .line_number   = line_number};

    return
    }


int StackPush (Stack_t*       stack,
               stack_elem_t   value) {
    assert(stack);

    //TODO resize
    stack[stack->size++] = value;

    }


stack_elem_t StackPop (Stack_t* stack) {
    assert(stack);

    return stack[stack->size--];
}


int StackDtor (Stack_t* stack) {

}
