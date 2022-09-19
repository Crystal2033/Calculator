
#include"Macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Funcks_not_for_stack.h"
#include <locale.h>


int main(void)
{
	printf("Hello, my name is Paul Kulikov, group M80-111B-20"
		" and its my program, which can calculate mathematical expression.\n");
	char expression[BUFSIZ];
	char postfix[BUFSIZ];
	int bad_index = -1;
	int status_code;
	Data result;

	int i = 0, j = 0;
	PStack stack;
	Data expr, temp_data;
	int compare_checker = -1;
	char* end_ptr;	

#ifdef LIST

	while (1)
	{
		stack = (PStack)malloc(sizeof(Stack));
		if (!stack)
		{
			return -1;
		}

		if (init(stack, OPERATOR))
		{
			return -1;
		}
					
		printf("Input mathematical expression:\n>> ");
		fgets(expression, BUFSIZ, stdin);

		for (int i = 0; i < strlen(expression); i++)
		{
			if (isalpha(expression[i]))
			{
				expression[i] = tolower(expression[i]);
			}
		}
		
		if (strcmp(expression, "quit\n") == 0)
		{
			printf("This is over. Bye, bye!\n");
			clear(stack);
			return 1;
		}

		if (strcmp(expression, "author\n") == 0)
		{
			printf("My name is Kulikov Paul Sergeevich, group M80-111B-20, and i`m studying in FIIT MAI.\n");
			clear(stack);
			continue;
		}
		
		status_code = input_validate(expression, &bad_index);

		switch (status_code)
		{
		case 1:
		{
			printf("There is no expression. You have input nothing.\n");
			break;
		}
		case 2:
		{
			printf("Your expression can`t consists of characters.\n");
			printf("Mistake is on the [%d] index.\n", bad_index);
			break;
		}
		case 3:
		{
			printf("'+', '-', '*', '/', '(', ')'. You can use only these operations.\n");
			printf("Mistake is on the [%d] index.\n", bad_index);
			break;
		}
		case 4:
		{
			printf("Value of opened brackets is not equal to value of closed brackets.\n");
			break;
		}
		case 0:
		{
			break;
		}
		}
		if (status_code != 0)
		{
			continue;
		}
		
		status_code = improved_input_validate(expression, &bad_index);

		if (status_code != 0)
		{
			printf("Mistake is on the [%d] index.\n", bad_index);
		}
		else
		{
			status_code = to_postfix(stack, expression, postfix);
			if (status_code)
			{
				printf("For closed bracket haven`t been found pair bracket. Stack pop error.\n");
				clear(stack);
				free(stack);
				end_ptr = NULL;
				bad_index = -1;
				result.number = 0;
				expr.oper = ' ';
				expr.number = 0;
				j = 0;
				i = 0;
				compare_checker = -1;
				continue;
			}
			//printf("Postfix: %s\n", postfix);

			i = 0;
			if (init(stack, NUMBER))
			{
				return -1;
			}

			status_code = resolve(stack, postfix, &result);
			if (!status_code)
			{
				
				printf("Answer: %d\n", result.number);
			}
			else
			{
				printf("Division by zero error. Please, try again.\n");
			}
		}
		
		clear(stack);
		free(stack);
		end_ptr = NULL;
		bad_index = -1;
		result.number = 0;
		expr.oper = ' ';
		expr.number = 0;
		j = 0;
		i = 0;
		compare_checker = -1;
	}
#endif
#ifndef LIST
	
	while (1)
	{
		stack = (PStack)malloc(sizeof(Stack));
		if (!stack)
		{
			return -1;
		}

		init(stack, OPERATOR);

		//stack->data = (PData)malloc(sizeof(Data) * (stack->stackSize)); //stack_size изначально равен 8.
		if (!stack->data)
		{
			//clear(stack);
			free(stack);
			continue;
		}
		else
		{
			stack->topIndex_ptr = stack->data;
		}

		//printf("adress from main start: %p\n", stack->data);

		printf("Input mathematical expression:\n>> ");
		fgets(expression, BUFSIZ, stdin);

		for (int i = 0; i < strlen(expression); i++)
		{
			if (isalpha(expression[i]))
			{
				expression[i] = tolower(expression[i]);
			}
		}

		if (strcmp(expression, "quit\n") == 0)
		{
			printf("This is over. Bye, bye!\n");
			clear(stack);
			free(stack);
			return 1;
		}

		if (strcmp(expression, "author\n") == 0)
		{
			printf("My name is Kulikov Paul Sergeevich, group M80-111B-20, and i`m studying in FIIT MAI.\n");
			clear(stack);
			free(stack);
			continue;
		}

		status_code = input_validate(expression, &bad_index);

		switch (status_code)
		{
		case 1:
		{
			printf("There is no expression. You have input nothing.\n");
			break;
		}
		case 2:
		{
			printf("Your expression can`t consists of characters.\n");
			printf("Mistake is on the [%d] index.\n", bad_index);
			break;
		}
		case 3:
		{
			printf("'+', '-', '*', '/', '(', ')'. You can use only these operations.\n");
			printf("Mistake is on the [%d] index.\n", bad_index);
			break;
		}
		case 4:
		{
			printf("Value of opened brackets is not equal to value of closed brackets.\n");
			break;
		}
		case 0:
		{
			break;
		}
		}
		if (status_code != 0)
		{
			clear(stack);
			free(stack);
			continue;
		}

		status_code = improved_input_validate(expression, &bad_index);

		if (status_code != 0)
		{
			printf("Mistake is on the [%d] index.\n", bad_index);
			clear(stack);
			//free(stack->data);
			free(stack);
			continue;
		}

		//printf("Expr:  %s\n", expression);

		status_code = to_postfix(stack, expression, postfix);
		if (status_code)
		{
			printf("For closed bracket haven`t been found pair bracket. Stack pop error.\n");
			clear(stack);
			free(stack);
			continue;
		}

		//printf("postfix:  %s\n", postfix);

		status_code = resolve(stack, postfix, &result);
		if (!status_code)
		{
			printf("Answer: %d\n", result.number);
		}
		else
		{
			printf("Division by zero error. Please, try again.\n");
		}

		//printf("adress from main: %p\n", stack->data);
		clear(stack);
		free(stack);
	}
#endif
	return 0;
}