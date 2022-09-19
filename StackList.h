#pragma once
#include "DataTypes.h"
#ifdef LIST


struct StackNode
{
	union Data data;
	struct StackNode* next;
};

typedef struct StackNode NODE, *PNode;

struct StackBasedOnList
{
	DataType dataType;
	PNode top;
};

typedef struct StackBasedOnList Stack, *PStack;
#endif