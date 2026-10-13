#ifndef STACK_ELEM_T_DEFINED
    typedef double stack_elem_t;
#endif

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

    StackOkey (stack);
    return stack->stack_errors;
    }


stack_elem_t StackPop (Stack_t* stack) {
    StackOkey (stack);

    return stack->data[stack->size--];

        StackOkey (stack);

}


void StackDtor (Stack_t* stack) {
    StackOkey (stack);


    NullingData(stack);
    free(stack->data);
    stack = NULL;

    StackOkey (stack);
}


void NullingData (Stack_t* stack) {
    StackOkey (stack);

    for (int ind = 0; ind < stack->capacity; ind++) {
        stack->data[ind] = POISON(stack_elem_t);
    }
    stack->stack_errors = POISON_FOR_ERROR_VALUE;

    StackOkey (stack);
}


What_error StackOkey (Stack_t* stack) {

    if (!stack) {
        stack->stack_errors = NULL_ADDRESS;
        StackDump(stack);

        return NULL_ADDRESS;
    }

    if (stack->size > stack->capacity) {
        stack->stack_errors = SIZE_BIGGER_THEN_CAPACITY;
        StackDump(stack);

        return SIZE_BIGGER_THEN_CAPACITY;}

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


void StackDump(Stack_t* stack) {
    FILE* errors_file = fopen("Errors", "a");

    switch(stack->stack_errors) {
        case(POISON_FOR_ERROR_VALUE):
            fprintf(errors_file, "Обращение к зануленному элементу");
            break;
        case (ALL_IS_OK):
            fprintf(errors_file, "Ошибок нет");
            break;
        case (NULL_ADDRESS):
            fprintf(errors_file, "Работа с нулевым адресом");
            break;
        case (SIZE_BIGGER_THEN_CAPACITY):
            fprintf(errors_file, "Элементов больше че мвыделенно памяти");
            break;
        case (REALLOC_TO_UP_PROBLEM):
            fprintf(errors_file, "Ошибка во время увеличения размеров стека");
            break;
        case (REALLOC_TO_DOWN_PROBLEM):
            fprintf(errors_file, "Ошибка во время уменьшения размера стека");
            break;
        default:
            fprintf(errors_file, "Неизвестное значение в поле ошибки стека: %d", stack->stack_errors);

    }

    fprintf(errors_file, "В стеке %s, в фаиле: %s, в функции: %s, на строчке: %d \n",
            stack->Stack_info.stack_name, stack->Stack_info.file_name, stack->Stack_info.function_name, stack->Stack_info.line_number);
}
