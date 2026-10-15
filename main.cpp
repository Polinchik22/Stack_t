#define STACK_ELEM_T_DEFINED
typedef double stack_elem_t;

#define STACK_DEBUG_ON


#include "Stack_t.h"


#define StackCtor(stack_name, stack, capacity) StackCtor (__FILE__,      \
                                                        __FUNCTION__,  \
                                                        __LINE__,      \
                                                        stack_name, \
                                                        stack, \
                                                        capacity)


int main() {
    srand(time(NULL));

    Stack_t test_stack = {};
    // What_error test_stack_errors = ALL_IS_OK;
    StackCtor("test_stack", &test_stack, 5);


    StackPush(&test_stack, 6.5);
    StackPush(&test_stack, 5.5);
    double x1 = StackPop(&test_stack);
    printf("%f \n", x1);

    x1 = StackPop(&test_stack);
    printf("%f \n", x1);

    Printing_separator_file("Errors", "----", 10);

}
