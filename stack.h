#include<stdio.h>
#include"Number.h"
#define MAX 128
typedef struct stack{
	Number a[MAX];
	int i;
}stack;
void init(stack *s);
void push(stack *s, Number n);
Number pop(stack *s);
int isempty(stack *s);
int isfull(stack *s);
