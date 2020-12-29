#include "cstack.h"
#include <stdlib.h>
int cisempty(cstack *s){
	return *s == NULL;
}
int cisfull(cstack *s){
	return 1;
}
void cinit(cstack *s){
  	*s = NULL;
}

void cpush(cstack *s, char c){
  	cnode *tmp = (cnode *)malloc(sizeof(cnode));
  	tmp->ch = c;	
  	tmp->cnext = *s;
  	*s = tmp;
}

char cpop(cstack *s){
  	char temp;
  	cnode *tmp;
  	temp = (*s)->ch;
  	tmp = *s;
  	(*s) = (*s)->cnext;
  	free(tmp);
  	return temp;	
}
