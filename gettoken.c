#define MAX 128
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include "cstack.h"

int getmyline(char *l);
Number infixeval(char *l);
int bracket(char *mainl);
Number takenumber(char *l, int *p);
char takecharachter(char *l, int *p);
int priority(char ch);
char top(cstack *ts);

int main() {
	char line[MAX];
	Number x;
	while(getmyline(line)) {
		x = infixeval(line);
		printno(&x);
	}
	return 0;
}
	
int getmyline(char *l) {
	char ch = '\0';
	int i = 0;
	while(ch != '\n') {
		ch = getchar();
		l[i++] = ch;
	}
	l[i - 1] = '\0';
	if(l[0] == '\0')
		return 0;
	else 
		return 1;
}	

int bracket(char *mainl) {
	char sub1[MAX], sub2[MAX], bracketline[MAX], sub[MAX];
	int flag = 0, i = 0, j = 0, inflag = 0, a, b, k, y, l;
	Number val;
	while(mainl[i] != '\0') {
		if(mainl[i] == '(')
			flag++;
		i++;	
	}
	if(flag == 0)
		return 0;
	i = 0;
	while(mainl[i] != '(') {
		sub1[i] = mainl[i];
		i++;
	}
	sub1[i++] = '\0';
	while(inflag != -1 && mainl[i] != '\0') {
		if(mainl[i] == '(')
			inflag++;
		bracketline[j++] = mainl[i++];
		if(mainl[i] == ')')
			inflag--; 
	}
	bracketline[j] = '\0';
	j = 0;
	i++;
	while(mainl[i] != '\0')
		sub2[j++] = mainl[i++];
	sub2[j] = '\0';
	val = infixeval(bracketline);
	strcpy(sub, stringconvert(&val));
	l = strlen(sub);	
	strcat(sub1, bracketline);
	strcat(sub1, sub2);
	strcpy(mainl, sub1);
	return 1;	
}

Number infixeval(char *l) {
	int i = 0;
	Number j, j1;
	char k, k1;
	stack s, temp;
	cstack cs, ctemp;
	init(&s);
	cinit(&cs);
	init(&temp);
	cinit(&ctemp);
	while(bracket(l));		/*bracket is called repeatedly untill no more are remaining*/
	while(l[i] != '\0') {
		j = takenumber(l, &i);
		k = takecharachter(l, &i); /*All the numbers and charachters are pushed into their stack till newline is encountered*/
		push(&s, j);
		cpush(&cs, k);
	}
	if(top(&cs) == 'e')
		cpop(&cs);
	while(!cisempty(&cs)) {
		k = cpop(&cs);
		k1 = top(&cs);
		if(priority(k) > priority(k1)) {
			j = pop(&s);
			j1 = pop(&s);
			switch(k) {
				case '+' :
					j = add(&j, &j1);
					break;
				case '-' : 
					j = sub(&j1, &j);
					break;
				case '*' :
					j = mult(&j, &j1);
					break;
				case '/' :
					j = divide(&j1, &j);
					break;
				case '%' : 
					j = mod(&j1, &j);
					break;
				default : 			
					break;
			}
			push(&s, j);
			while(!isempty(&temp)) {
				j = pop(&temp);
				push(&s, j);
			}
			while(!cisempty(&ctemp)) {
				k = cpop(&ctemp);
				cpush(&cs, k);
			}
		}
		else {
			cpush(&ctemp, k);
			j = pop(&s);
			push(&temp, j);
		}
	}	
	j = pop(&s);
	if(isempty(&s))
		return j;
				
}

char top(cstack *ts) {				/*It return the charachter at the top of given stack*/
	char top = '\0';
	if(!cisempty(ts)) {
		top = cpop(ts);
		cpush(ts, top);
	}	
	return top;
}

int priority(char ch) {				/*It has the priority of the operators*/
	switch(ch) {
		case '+' : case '-' :
			return 1;
			break;
		case '*' : case '/' :
			return 2;
			break;
		case '%' :
			return 3;	
			break;
		default :
			return -1;
			break;	
	}
	return -1;
}

Number takenumber(char *l, int *p) {		/*It takes the number and appends it to the linked list*/
	Number a;
	number b;
	ninit(&b);
	int i = 0;
	float sign = 1;
	while(l[*p] == ' ')
		*p += 1;
	if(l[*p] == '-') {
		sign = -1;
		*p += 1;
	}	
	while(l[*p] == ' ')
		*p += 1;	
	while((l[*p] <= '9' && l[*p] >= '0') || l[*p] == '.') {	
		append(&b, l[*p]);
		*p += 1;
	} 
	a = convert(&b);			/*It converts data type number to Number*/
	if(sign == -1){
		addminus(&a);
	}
	return a;
}

char takecharachter(char *l, int *p) {
	char ch = '\0';				/*It collect charachter in the given line*/
	while(1) {
		if(l[*p] == '\0')
			return 'e';	
		else if(l[*p] != ' ') {
			ch = l[*p];
			*p += 1;
			break;
		}
		*p += 1;		
	}
	return ch;
}
