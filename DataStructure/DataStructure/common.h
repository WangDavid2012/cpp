#pragma once

#include <stdlib.h>
#include <stdio.h>


typedef struct _NODE 
{
	int data;
	struct _NODE *pNext;
}*PNODE, NODE;

//typedef enum { false = 0, true = !0 } bool;