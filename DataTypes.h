#pragma once

#include "Macro.h"
enum DataType { NUMBER, OPERATOR };

union Data
{
	int number;
	char oper;
};

typedef union Data Data, * PData;
typedef enum DataType DataType;