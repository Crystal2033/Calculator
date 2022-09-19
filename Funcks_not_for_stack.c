#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Funcks_not_for_stack.h"
//5-12*(3-2/2*4-3*(2-2))
int to_postfix(PStack oper_list, char* expression, char* postfix)
{
	int i = 0, j = 0;
	Data expr, temp_data;
	int compare_checker = -1;
	int flag_fail_closed_bracket = 0;
	while (expression[i] != '\0')
	{
		if (i == 0 && expression[i] == '-')
		{
			postfix[j++] = expression[i++];
			continue;
		}

		if (isdigit(expression[i]))
		{
			while (isdigit(expression[i]))
			{
				postfix[j++] = expression[i++];
			}
			postfix[j++] = ' ';
		}

		if (expression[i] == '\0')
		{
			break;
		}

		expr.oper = expression[i];

		if (expr.oper == '(')
		{
			push(oper_list, expr);

			if (expression[i + 1] == '-' || expression[i + 1] == '+')
			{
				postfix[j++] = expression[i + 1];
			}
			i++;
			continue;
		}

		if (expr.oper == ')')
		{
			while (!pop(oper_list, &temp_data))
			{
				if (temp_data.oper == '(')
				{
					flag_fail_closed_bracket = 1;
					break;
				}
				postfix[j++] = temp_data.oper;
				postfix[j++] = ' ';
			}
			if (flag_fail_closed_bracket != 1)
			{
				return 1;
			}
			flag_fail_closed_bracket = 0;
		}

		if ((expr.oper != '(') && (expr.oper != ')') && expression[i - 1] != '(')
		{
			compare_checker = compare_operations(expr.oper, oper_list);

			while (!isEmpty(oper_list) && compare_checker)
			{
				pop(oper_list, &temp_data);
				postfix[j++] = temp_data.oper;
				postfix[j++] = ' ';

				if (!isEmpty(oper_list))
				{
					compare_checker = compare_operations(expr.oper, oper_list);
				}
			}
			push(oper_list, expr);
		}
		i++;
	}

	while (!pop(oper_list, &temp_data))
	{
		if (temp_data.oper == '(')
		{
			printf("Value of opened brackets is not equal to value of closed brackets.\n");
			continue;
		}
		postfix[j++] = temp_data.oper;
		postfix[j++] = ' ';
	}

	postfix[j] = '\0';
	temp_data.oper = NULL;
	return 0;
}

int resolve(PStack oper_list, char* postfix, PData result)
{
	int flag = 0;
	int i = 0;
	Data expr, temp_data;
	char* end_ptr = NULL;
	int first_operand = INT_MAX, second_operand = INT_MAX;
	char operation;
	int answer;
	while (postfix[i])
	{
		if (isdigit(postfix[i]))
		{
			expr.number = (int)strtod(&postfix[i], &end_ptr);
			push(oper_list, expr);
			i += end_ptr - (postfix + i);
			continue;
		}

		if (ispunct(postfix[i]))
		{

			if (ispunct(postfix[i]) && isdigit(postfix[i + 1]) && postfix[i] == '-')
			{
				expr.number = (int)strtod(&postfix[i], &end_ptr);
				push(oper_list, expr);
				i += end_ptr - (postfix + i);
				continue;
			}

			operation = postfix[i];

			if (!pop(oper_list, &temp_data))
			{
				second_operand = temp_data.number;
			}
			else
			{
				//printf("Error, can`t pop number from stack!\n");
				return 2;
			}

			if (!pop(oper_list, &temp_data))
			{
				first_operand = temp_data.number;
			}
			else
			{
				//printf("Error, can`t pop number from stack!\n");
				return 2;
			}

			if (!calculating_operands(first_operand, second_operand, operation, &answer))
			{
				result->number = answer;
				push(oper_list, *result);
			}
			else
			{
				return 1;
			};
		}
		i++;
	}
	pop(oper_list, result);
	return 0;
}

int compare_operations(char questionable_oper, const PStack stack)
{
	int priority_qu_char = 0, priority_is_st_char = 0;
	Data operation;
	if (isEmpty(stack))
	{
		return 1;
	}

	switch (questionable_oper)
	{
	case ')':
	{
		priority_qu_char = 1;
		break;
	}
	case '(':
	{
		priority_qu_char = 2;
		break;
	}
	case '+':
	{
		priority_qu_char = 3;
		break;
	}
	case '-':
	{
		priority_qu_char = 3;
		break;
	}
	case '*':
	{
		priority_qu_char = 4;
		break;
	}
	case '/':
	{
		priority_qu_char = 4;
		break;
	}
	}
	top(stack, &operation);

	switch (operation.oper)
	{
	case ')':
	{
		priority_is_st_char = 1;
		break;
	}
	case '(':
	{
		priority_is_st_char = 2;
		break;
	}
	case '+':
	{
		priority_is_st_char = 3;
		break;
	}
	case '-':
	{
		priority_is_st_char = 3;
		break;
	}
	case '*':
	{
		priority_is_st_char = 4;
		break;
	}
	case '/':
	{
		priority_is_st_char = 4;
		break;
	}
	}

	if (priority_qu_char <= priority_is_st_char)
	{
		return 1;
	}
	else
		return 0;
}

int calculating_operands(int first_num, int second_num, char operation, int* answer)
{
	if (operation == '/' && second_num == 0)
	{
		//printf("Impossible to solve: zero division error.\n");
		return 1;
	}

	switch (operation)
	{
	case '+':
	{
		*answer = first_num + second_num;
		break;
	}
	case '-':
	{
		*answer = first_num - second_num;
		break;
	}
	case '*':
	{
		*answer = first_num * second_num;
		break;
	}
	case '/':
	{
		*answer = first_num / second_num;
		break;
	}
	}
	return 0;
}

int input_validate(char* input_data, int* bad_index)
{
	int value_of_open_brackets = 0, value_of_close_brackets = 0;
	int len = strlen(input_data) - 1;
	char correct_punct[7] = { '+', '-', '*', '/', '(', ')',  '\0' };
	int j = 0, k = 0, i = 0;

	if (len == 0)
	{
		return 1;
	}

	while (i < len)
	{
		if (isdigit(input_data[i]))
		{
			input_data[j++] = input_data[i++];
			continue;
		}

		if (input_data[i] == '(')
		{
			input_data[j++] = input_data[i++];
			value_of_open_brackets++;
			continue;
		}
		else if (input_data[i] == ')')
		{
			input_data[j++] = input_data[i++];
			value_of_close_brackets++;
			continue;
		}

		if (isalpha(input_data[i]))
		{

			*(bad_index) = i;
			return 2;
		}


		if (isspace(input_data[i]))
		{
			k = i;
			if (!isspace(input_data[k + 1]))
			{
				input_data[j++] = input_data[i++];
				continue;
			}

			while (isspace(input_data[k]) && isspace(input_data[k + 1]))
			{
				k++;
			}
			i = k;
			continue;
		}

		if (!strchr(correct_punct, input_data[i]))
		{
			if (isspace(input_data[i]))
			{
				continue;
			}

			*(bad_index) = i;
			return 3;

		}
		else
		{
			input_data[j++] = input_data[i++];
			continue;
		}

	}
	if (value_of_open_brackets != value_of_close_brackets)
	{
		return 4;
	}
	input_data[j] = '\0';
	return 0;
}

int improved_input_validate(char* expression, int* bad_index)
{
	char correct_punct[7] = { '+', '-', '*', '/', '(', ')',  '\0' };
	char without_brackets[5] = { '+', '-', '*', '/', '\0' };
	char without_minus[4] = { '+', '*', '/', '\0' };
	int len = strlen(expression);
	int j = 0;

	for (int i = 0; i < len; i++)
	{
		if (isdigit(expression[i]))
		{
			expression[j++] = expression[i];
			continue;
		}

		if (expression[i] == '(')
		{
			expression[j++] = expression[i];
			continue;
		}

		else if (expression[i] == ')')
		{
			expression[j++] = expression[i];
			continue;
		}

		if (i < len)
		{
			if (strchr(without_brackets, expression[i]) && strchr(without_brackets, expression[i + 1]))
			{
				*(bad_index) = i;
				return 2;
			}
		}

		if (i < len && i > 0)
		{
			if (isspace(expression[i]) && isdigit(expression[i - 1]) && isdigit(expression[i + 1]))
			{
				*(bad_index) = i;
				return 2;
			}

			if (isspace(expression[i]) && strchr(without_brackets, expression[i - 1]) && strchr(without_brackets, expression[i + 1]))
			{
				*(bad_index) = i;
				return 2;
			}
		}

		if (!isspace(expression[i]))
		{
			expression[j++] = expression[i];
		}

	}

	expression[j] = '\0';
	return 0;
}
