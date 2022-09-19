#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StackArray.h"
#include "Macro.h"

#ifndef LIST

int init(PStack stack, DataType rel_data) // 0 - success; others - own errors
{
	int stack_size = 2;

	stack->data = (PData)malloc(sizeof(Data) * stack_size);
	stack->stackSize = stack_size;
	stack->topIndex_ptr = stack->data;
	stack->dataType = rel_data;
	return 0;
}
//5+(-5*(12-6/3+15*7*(-5+12/4*2/2-(7+1))))
//5+(-5*(12-6/3+15*7*(-5+12/4*2/2-(7+1))))*(5+(-5*(12-6/3+15*7*(-5+12/4*2/2-(7+1)))))


int push(PStack stack, union Data toPush) // 0 - success; others - own errors
{
	PData tmp;
	if (!stack) return -1;
	if (!stack->data) return -1;
	if (stack->topIndex_ptr == stack->data + stack->stackSize - 1)
	{
		 // на случай потери данных под указателем stack->data
		tmp = (PData)realloc(stack->data, sizeof(Data)*(stack->stackSize*2)); //на случай переноса в другую ячейку памяти.
		if (tmp)
		{
			stack->data = tmp;
			stack->topIndex_ptr = stack->data + stack->stackSize - 1;
			stack->stackSize *= 2;
		}
		else return -1;
	}

	//else if (stack->topIndex_ptr == stack->data + (stack->stackSize / 2) - 1 && stack->stackSize > 2)
	//{
	//	stack->stackSize /= 2;
	//	tmp = (PData)realloc(stack->data, sizeof(Data) * stack->stackSize);
	//	if (tmp)
	//	{
	//		stack->data = tmp;
	//		stack->topIndex_ptr = stack->data + stack->stackSize - 1;
	//		//stack->stackSize /= 2;
	//	}
	//	else
	//	{
	//		stack->stackSize *= 2;
	//		return -1;
	//	}

	//}
	*(stack->topIndex_ptr) = toPush;
	stack->topIndex_ptr++;
	
}

int pop(PStack stack, PData destination) // 0 - success; others - own errors
{
	if (isEmpty(stack))
	{
		return 1;
	}

	stack->topIndex_ptr--;
	*destination = *stack->topIndex_ptr;
	stack->topIndex_ptr->number = 0;

	return 0;
}

int top(const PStack stack, PData destination) // 0 - success; others - own errors
{
	if (isEmpty(stack))
	{
		return 0;
	}
	else
	{
		stack->topIndex_ptr--;
		*destination = *stack->topIndex_ptr;
		stack->topIndex_ptr++;
	}
	return 1;
}
int isEmpty(const PStack stack) // 0 - empty; 1 - not empty; others - own errors;
{
	if (stack->topIndex_ptr == stack->data)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int clear(PStack stack)// 0 - success; others - own errors
{
	if (isEmpty(stack))
	{
		free(stack->data);
	}
	return 0;
}
#endif