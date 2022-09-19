#pragma once
#include "DataTypes.h"
#ifdef LIST
	#include "StackList.h"
#endif
#ifndef LIST
	#include "StackArray.h"
#endif

int init(PStack stack, DataType rel_data); // 0 - success; others - own errors
int push(PStack stack, union Data toPush); // 0 - success; others - own errors
int pop(PStack stack, PData destination); // 0 - success; others - own errors
int top(const PStack stack, PData destination); // 0 - success; others - own errors
int isEmpty(const PStack stack); // 0 - empty; 1 - empty; others - own errors;
int clear(PStack stack); // 0 - success; others - own errors