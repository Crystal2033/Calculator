#pragma once

#include "DataTypes.h"
#ifndef LIST


struct StackBasedOnArray
{
	DataType dataType;
	PData data;
	PData topIndex_ptr; // or pointer to the top element/next to the top element
	int stackSize;
};

typedef struct StackBasedOnArray Stack, * PStack;
#endif