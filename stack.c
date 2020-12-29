#include"stack.h"
#include<stdio.h>
#include<stdlib.h>

void init(stack *s){
	s->i = 0;
}
void push(stack *s, Number n){
	s->a[s->i++] = n;
}
Number pop(stack *s){
	Number t;
	t = s->a[s->i-1];
	s->i--;
	return t;
}
int isempty(stack *s){
	return s->i == 0;
}
int isfull(stack *s){
	return s->i == MAX;
}
