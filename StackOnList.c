#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "StackList.h"
#include "Macro.h"

#ifdef LIST

int init(PStack stack, DataType rel_data) // 0 - success; others - own errors
{
	stack->top = NULL;
	stack->dataType = rel_data;
	return 0;
}

int push(PStack stack, union Data toPush) // 0 - success; others - own errors
{
	PNode node = NULL;
	if (isEmpty(stack))
	{
		node = (PNode)malloc(sizeof(NODE));

		if (!node)
		{
			return -1;
		}
		stack->top = node;
		node->data = toPush;
		node->next = NULL;
		return 0;
	}
	else
	{
		node = (PNode)malloc(sizeof(NODE));
		if (!node)
		{
			return -1;
		}
		node->data = toPush;
		node->next = stack->top;
		stack->top = node;
		return 0;
	}

}

int pop(PStack stack, PData destination) // 0 - success; others - own errors
{
	if (isEmpty(stack))
	{
		return 1;
	}

	PNode temp = NULL;
	temp = stack->top;
	stack->top = stack->top->next;
	temp->next = NULL;
	*destination = temp->data;
	free(temp);
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
		*destination = stack->top->data;
	}
	return 1;
}
int isEmpty(const PStack stack) // 0 - empty; 1 - not empty; others - own errors;
{
	if (stack->top == NULL)
	{
		return 1;
	}
	return 0;
}
int clear(PStack stack) // 0 - success; others - own errors
{
	if (isEmpty(stack))
	{
		stack->top = NULL;
		return 0;
	}
	else
	{
		PNode temp;
		while (stack->top->next != NULL)
		{
			temp = stack->top;
			stack->top = temp->next;
			free(temp);
		}
		return 0;
	}
}

#endif