#pragma once

#include "Stack.h"

int to_postfix(PStack oper_list, char* expression, char* postfix);
int resolve(PStack oper_list, char* postfix, PData result);
int compare_operations(char questionable_oper, PStack in_stack_oper); //1 - oper has more prior than oper in st, 0 - less, -1 - error
int calculating_operands(int first_num, int second_num, char operation, int* answer); // 1 - ошибка, 0 - все ок.
int input_validate(char* input_data, int* bad_index);
int improved_input_validate(char* expression, int* bad_index);