#ifndef STACK_ELEM_T_DEFINED
    typedef double stack_elem_t;
#endif

#include "Stack_t.h"

#define refreshing_info(stack) stack->Stack_info = {.file_name     = __FILE__, \
                                                    .function_name = __FUNCTION__, \
                                                    .line_number   = __LINE__};

#define STACK_LOGS(stack) refreshing_info(stack); StackOkey (stack)



What_error StackCtor (const char* file_name,
               const char* function_name,
               int         line_number,
               const char* stack_name, //Вопрос, можено ли это как то сделать не аргументом который вводят руками
               Stack_t*    stack,
               int         capacity) {

    // TODO все занулено?

    stack->capacity = capacity;
    stack->size = 0;

    stack->data = (stack_elem_t*) calloc(capacity, sizeof(stack_elem_t));
    assert(stack->data);

    NullingData(stack);

    // printf("%d \n", stack->capacity);
    stack->Stack_info = {.stack_name    = stack_name, //TODO сделать макрос на имя
                         .file_name     = file_name,
                         .function_name = function_name,
                         .line_number   = line_number};


    // StackOkey (stack);
    // StackDump(stack);
    stack->stack_errors = ALL_IS_OK;
    return stack->stack_errors;
    }


What_error StackPush (Stack_t*       stack,
                      stack_elem_t   value) {
    refreshing_info(stack);

    resizing_stack(stack);
    (stack->data)[stack->size++] = value;

    refreshing_info(stack);
    StackDump(stack);

    StackOkey (stack);
    return stack->stack_errors;
    }


stack_elem_t StackPop (Stack_t* stack) {
    refreshing_info(stack);
    StackOkey (stack);

    StackDump(stack);

    stack->size--;
    return stack->data[stack->size];
}


void StackDtor (Stack_t* stack) {
    assert(stack);

    refreshing_info(stack);
    StackOkey (stack);


    NullingData(stack);
    free(stack->data);

    stack->stack_errors = DESTROYED_STACK;
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;

    stack = NULL;

}


void NullingData (Stack_t* stack) {
    refreshing_info(stack);
    StackOkey (stack);

    for (int ind = 0; ind < stack->capacity; ind++) {
        stack->data[ind] = POISON(stack_elem_t);
    }

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

        return SIZE_BIGGER_THEN_CAPACITY;
    }

    // refreshing_info(stack);

    return ALL_IS_OK;
}

void resizing_stack(Stack_t* stack) {
    refreshing_info(stack);
    StackOkey (stack);

    if (stack->size == stack->capacity) {
        up_capacity(stack);
        //TODO проверки
    } else if (stack->capacity >= THRESHOLD_FOR_DOWN_ALLOCATION  && stack->size * 4 < stack->capacity) {
        down_capacity(stack);
    }

    refreshing_info(stack);
    StackOkey (stack);
}


void up_capacity(Stack_t* stack) {
    refreshing_info(stack);
    StackOkey (stack);

    void* temp_pointer = realloc(stack->data, (stack->capacity)*2);
    if (temp_pointer) {
        stack->data = (stack_elem_t*) temp_pointer;
        stack->capacity *= 2;
        NullingData(stack);
    } else {
        stack->stack_errors = REALLOC_TO_UP_PROBLEM;
    }

    refreshing_info(stack);
    StackOkey (stack);
}


void down_capacity(Stack_t* stack) {
    refreshing_info(stack);
    StackOkey (stack);


    void* temp_pointer = realloc(stack->data, (stack->capacity) / 2);
    if (temp_pointer) {
        stack->data = (stack_elem_t*)temp_pointer;
        stack->capacity /= 2;
    } else {
        stack->stack_errors = REALLOC_TO_DOWN_PROBLEM;
    }

    refreshing_info(stack);
    StackOkey (stack);
}
// static

void StackDump(Stack_t* stack) {
    FILE* errors_file = fopen("Errors", "a");

    fprintf(errors_file, "В стеке %s, в фаиле: %s, в функции: %s, на строчке: %d \n",
            stack->Stack_info.stack_name, stack->Stack_info.file_name, stack->Stack_info.function_name, stack->Stack_info.line_number);


    switch(stack->stack_errors) {
        case(POISON_FOR_ERROR_VALUE):
            fprintf(errors_file, "Обращение к зануленному элементу\n");
            break;

        case (ALL_IS_OK):
            fprintf(errors_file, "Ошибок нет\n");
            break;

        case (NULL_ADDRESS):
            fprintf(errors_file, "Работа с нулевым адресом \n");
            break;

        case (SIZE_BIGGER_THEN_CAPACITY):
            fprintf(errors_file, "Элементов больше че мвыделенно памяти \n");
            break;

        case (REALLOC_TO_UP_PROBLEM):
            fprintf(errors_file, "Ошибка во время увеличения размеров стека \n");
            break;

        case (REALLOC_TO_DOWN_PROBLEM):
            fprintf(errors_file, "Ошибка во время уменьшения размера стека \n");
            break;

        default:
            fprintf(errors_file, "Неизвестное значение в поле ошибки стека: %d", stack->stack_errors);
            break;
    }

    Printing_stack(stack);


    fclose(errors_file);

}

void Printing_stack(Stack_t* stack) {
    FILE* errors_file = fopen("Errors", "a");

    fprintf(errors_file, "\n");

    if (stack->stack_errors == NULL_ADDRESS) {
        fprintf(errors_file, "Нельзя вывести стек - ошибка указателя \n\n");
    } else {
        fprintf(errors_file, "Сейчас в стеке size = %d, capacity = %d лежат элементы:\n", stack->size, stack->capacity);
        for (int i = 0; i < stack->size; i++) {
            fprintf(errors_file, "%f ", (stack->data)[i]);
        }
        fprintf(errors_file, "\n\n");
    }

    fclose(errors_file);
}


void Printing_separator_file(const char* file_name, const char* separator, int len_of_separation_line) {
    FILE* out_file = fopen(file_name, "a");


    fprintf(out_file, "\n");
    for (int i = 0; i < len_of_separation_line; i++) {
        fprintf(out_file, "%s", separator);
    }
    fprintf(out_file, "\n\n");

    fclose(out_file);
}

//TODO как ебаный нахуй сделать так чтобы при перезепуске праграммы фаил сначала зачищался а потом записывался
