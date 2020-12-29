#include"Number.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void ninit(number *a){
	a->h = a->t = NULL;
	a->decimal = 0;
}
int isalargerthanb(Number *a, Number *b){		/*It checks if a is larger than b*/
	int l1, l2;
	l1 = strlen(a->str);
	l2 = strlen(b->str);
	if((l1-(a->decimal)) > (l2-(b->decimal)))
		return 1;
	if((l1-(a->decimal)) < (l2-(b->decimal)))
		return 0;
	if((l1-(a->decimal)) == (l2-(b->decimal))){
		if(strcmp(a->str, b->str) < 0){
			return 0;
		}
		else if(strcmp(a->str, b->str) > 0)
			return 1;
		else if(strcmp(a->str, b->str) == 0)
			return -1;
	}
	return 1;
}
void append(number *a, char ch){			/*It appends charachter ch to the number a*/
	node *tmp = (node *)malloc(sizeof(node));
	tmp->digit = ch;
	tmp->prev = a->t;
	tmp->next = NULL;
	if(((a->h) == NULL) &&((a->t) == NULL)){
		a->t = a->h = tmp;
	}
	else{
		a->t->next = tmp;
		a->t = tmp;
	}
}
int length(number *a){					/*It returns the length of number a stored as linked list*/
	node *tmp;
	int count = 0;
	tmp = a->h;
	while(tmp){
		count++;
		tmp = tmp->next;
	}
	return count;
}
int decimalposition(number *a){				/*Returns the position of decimal of number a*/
	if((a->h)->digit == '.'){
		return (length(a) - 1);
	}
	int i = 0;
	node *tmp;
	tmp = a->t;
	if(a->h->digit == '.')
		return (length(a) - 1);
	if(a->t->digit == '.')
		return (length(a));
	while(tmp){
		if(tmp->digit == '.')
			break;
		i++;
		tmp = tmp->prev;
	}
	if(!tmp)
		return 0;
	return i;
}
void removedecimal(Number *a){				/*Removes . from the string stored in structutre Number*/
	int pos = strlen(a->str) - (a->decimal + 1);
	int length = strlen(a->str);
	int i = 0;
	if(pos == 0){
		for(i = 0; i < length-1; i++)
			a->str[i] = a->str[i+1];
		a->str[i] = '\0';
		return;
	}
	else if(pos == (length - 1)){
		a->str[pos] = '\0';
		return;
	}
	else{
		for(i = pos; i < length - 1; i++)
			a->str[i] = a->str[i+1];
		a->str[i] = '\0';
		return;
	}
}	
Number convert(number *a){				/*It converts the data type of a from number to Number*/
	Number b;
	int count = 0, pos;
	node *tmp;
	tmp = a->h;
	b.str = (char *)malloc(sizeof(char)*length(a));
	while(tmp){
		b.str[count] = tmp->digit;
		count++;
		tmp = tmp->next;
	}
	pos = decimalposition(a);
	if(pos == length(a)){
		b.decimal = 0;
		removedecimal(&b);
		return b;
	}
	b.decimal = pos;
	if(!b.decimal)
		return b;
	else
		removedecimal(&b);
	return b;
}
void addzeroestoright(Number *a, int pos){		/*Zeroes are added to the right*/
	int i = strlen(a->str);
	while(pos > 0){
		a->str[i] = '0';
		pos--;
		i++;
		a->decimal++;
	}
	return;
}
Number add(Number *a, Number *b){			/*Returns the sum of two numbers*/
	Number c;
	int l1, l2, i, j, k, carry = 0, s, flag = 0;
	if(isnegative(a) && isnegative(b)){
		flag = 1;
		removenegative(a);
		removenegative(b);
	}
	if(isnegative(a) && !isnegative(b)){
		removenegative(a);
		c = sub(b, a);
		addminus(a);
		return c;
	}
	if(!isnegative(a) && isnegative(b)){
		removenegative(b);
		c = sub(a, b);
		addminus(b);
		return c;
	}
	c.decimal = (a->decimal >= b->decimal) ? a->decimal : b->decimal;
	if(c.decimal == a->decimal)
		addzeroestoright(b, c.decimal - b->decimal);
	else 
		addzeroestoright(a, c.decimal - a->decimal);
	l1 = strlen(a->str);
	l2 = strlen(b->str);
	k = (l1 >= l2) ? l1 : l2; 
	c.str = (char *)malloc(sizeof(char)*k);
	c.str[k] = '\0';
	k = k - 1;
	i = l1 - 1;
	j = l2 - 1;
	while(i >= 0 && j >= 0){
		s = (a->str[i]-48) + (b->str[j]-48) + carry;
		c.str[k] = s%10 + 48;
		carry = s/10;
		i--;
		j--;
		k--;
	}
	if(i >= 0){
		while(i >= 0){
			s = a->str[i]-48+carry;
			c.str[k] = s%10 + 48;
			carry = s/10;
			i--;
			k--;
		}
	}
	else if(j >= 0){
		while(j >= 0){
			s = b->str[j] - 48 + carry;
			c.str[k]  = s%10 + 48;
			carry = s/10;
			j--;
			k--;
		}
	}
	if(carry > 0){
		for(i = strlen(c.str); i >= 0; i-- ){
			c.str[i+1] = c.str[i];
		}
		c.str[0] = carry + 48;
	}
	if(flag == 1){
		addminus(a);
		addminus(b);
		addminus(&c);
	}
	return c;
}
int isnegative(Number *a){			/*Checks whether the given Number a is negative*/
	if(a->str[0] == '-')
		return 1;
	else 
		return 0;
}
void removenegative(Number *a){			/*Removes the the '-' sign from starting of the string*/
	int i, l;
	l = strlen(a->str);
	for(i = 0; i < l; i++)
		a->str[i] = a->str[i+1];
	a->str[i] = '\0';
}
void addminus(Number *a){			/*Adds minus to the start of the string*/
	int i, l = 0;
	Number *b;
	b = (Number *)malloc(sizeof(Number));
	l = strlen(a->str);
	b->str = (char *)malloc(sizeof(char)*l*2);
	b->decimal = a->decimal;
	for(i = 0 ; i <= l; i++)
		b->str[i+1] = a->str[i];
	b->str[0] = '-';
	a->str = b->str;
	
}
void printno(Number *a){			/*Prints the number*/
	int k, j = strlen(a->str), i;
	if(a->decimal > j){
		printf(".");
		k = a->decimal - j;
		while(k > 0){
			printf("0");
			k--;
		}
		for(i = 0; i < j; i++){
			if(i == (strlen(a->str)-(a->decimal)))
				printf(".");
			printf("%c", a->str[i]);
		}
	}
	for(i = 0; i < j; i++){
		if(i == (strlen(a->str)-(a->decimal)))
			printf(".");
		printf("%c", a->str[i]);
	}
	printf("\n");
	return;
}
Number sub(Number *a, Number *b){		/*Substracts b from a*/
	Number *d;
	Number e;
	int i, j, carry = 0, k, l1, l2, c, s, count1 = 0, count2 = 0;
	e.decimal = (a->decimal >= b->decimal) ? a->decimal : b->decimal;
	if(isnegative(a) && isnegative(b)){
		removenegative(a);
		removenegative(b);
		e = sub(b, a);
		addminus(a);
		addminus(b);
		return e;
	}
	if(isnegative(a) && !isnegative(b)){
		removenegative(a);
		e = add(a, b);
		addminus(a);
		addminus(&e);
		return e;
	}
	if(!isnegative(a) && isnegative(b)){
		removenegative(b);
		e = add(a, b);
		addminus(b);
		return e;
	}
	if(e.decimal == a->decimal)
		addzeroestoright(b, e.decimal - b->decimal);
	else 
		addzeroestoright(a, e.decimal - a->decimal); 			
	c = isalargerthanb(a, b);
	if(c == -1){
		e.str = "0";
		e.decimal = 0;
		return e;
	}
	if(c == 0){
		d = a;
		a = b;
		b = d;
	}
	l1 = strlen(a->str);
	l2 = strlen(b->str);
	for(i = 0; i < l1; i++){
		if(a->str[i] == '0')
		count1++;
	}
	for(i = 0; i < l2; i++){
		if(b->str[i] == '0')
		count2++;
	}
	if((count1 == l1)&& (count2 == l2)){
		e.str = "0";
		e.decimal = 0;
		return e;
	}
	if(count1 == l1 ){
		addminus(b);
		e.str = b->str;
		e.decimal = b->decimal;
		if(c == 0){
			if(isnegative(&e)){
				removenegative(&e);
				return e;
			}
			else{
				addminus(&e);
				return e;
			}
		}
		else
			return e;
	}
	k = (l1 >= l2) ? l1 : l2;
	e.str = (char *)malloc(sizeof(char)*(k + 1));
	e.str[k] = '\0';
	k = k-1;
	i = l1-1;
	j = l2-1;
	while(i >= 0 && j >= 0){
		s = ((a->str[i])-48) - ((b->str[j])-48) - carry;
		if (s < 0){ 
			s = s + 10; 
			carry = 1; 
		} 
		else
			carry = 0; 
		e.str[k] = s + 48;
		i--;
		j--;
		k--;
	}
	if(i >= 0){
		while(i >= 0){
			s = ((a->str[i])-48)-carry;
			if(s < 0){
				s = s + 10;
				carry = 1;
			}
			else 
				carry = 0;
			e.str[k] = s + 48;
			i--;
			k--;
		}
	}
	if(c == 0){
			//printno(a);
			//printno(b);
			//printno(&e);
			
				addminus(&e);
				return e;
			}
		
		else
			return e;
}
Number mult(Number *a, Number *b){			/*Returns the product of a and b*/
	int l = strlen(a->str)+strlen(b->str);
	Number c, *z;
	char *d = (char *)malloc(sizeof(int) *l);
	char *mul = (char *)malloc(sizeof(char) * l);
	int *temp = (int *)malloc(sizeof(int) * l);
    	int la,lb;
    	int i,j,k=0,x=0,y,count1,count2;
    	long int r=0;
    	long sum = 0;
    	la=strlen(a->str)-1;
        lb=strlen(b->str)-1;
   	c.str = (char *)malloc(sizeof(char)*l);	
	c.decimal = a->decimal + b->decimal;
	if(b->str == "1" && b->decimal == 0){
		z->str = b->str;
		z->decimal = b->decimal;
		b->str = a->str;
		b->decimal = a->decimal;
		a->str = z->str;
		a->decimal = z->decimal;
	}
	if(isnegative(a) && isnegative(b)){
		removenegative(a);
		removenegative(b);
		c = mult(a, b);
		addminus(a);
		addminus(b);
		return c;
	}
	if(isnegative(a) && !isnegative(b)){
		removenegative(a);
		c = mult(a, b);
		addminus(a);
		addminus(&c);
		return c;
	}
	if(!isnegative(a) && isnegative(b)){
		removenegative(b);
		c = mult(a, b);
		addminus(b);
		addminus(&c);
		return c;
	}
	for(i = 0; i < la; i++){
		if(a->str[i] == '0')
		count1++;
	}
	for(i = 0; i < lb; i++){
		if(b->str[i] == '0')
		count2++;
	}
	if((count1 == la) || (count2 == lb)){
		c.str = "0";
		c.decimal = 0;
		return c;
	}

    	for(i=lb;i>=0;i--){
         	r=0;
         	for(j=la;j>=0;j--){
             		temp[k++] = ((b->str[i] - 48)*(a->str[j] - 48) + r)%10;
             		r = ((b->str[i]-48)*(a->str[j]-48)+r)/10;
         	}
         	temp[k++] = r;
         	x++;
         	for(y = 0; y < x; y++){
             		temp[k++] = 0;
         	}
    	}
   
   	k=0;
    	r=0;
    	for(i=0; i < la+lb+2; i++){
         	sum =0;
         	y=0;
         	for(j = 1; j <= lb+1; j++){
             		if(i <= la+j){
                	sum = sum + temp[y+i];
             		}
             	y += j + la + 1;
         	}
         	d[k++] = (sum+r) %10;
         	r = (sum+r)/10;
    	}
    	d[k] = r;
    	j=0;
    	for(i=k-1;i>=0;i--){
        	mul[j++]=d[i] + 48;
    	}
    	mul[j]='\0';
    	strcpy(c.str, mul);
	return c;
}

Number divide(Number *a, Number *b){			/*Returns the division of a and b*/
	Number c, d, e, result, x;
	int l1, l2, l = 0, i, comp = 1, count1 = 0, count2 = 0;
	c = *a;
	d = *b;
	l1 = strlen(a->str);
	l2 = strlen(b->str);
	l = l1 + l2;
	result.str = (char *)malloc(sizeof(char)*2*l);
	if(isnegative(a) && isnegative(b)){
		removenegative(a);
		removenegative(b);
		result = divide(a, b);
		addminus(a);
		addminus(b);
		return result;
	}
	if(isnegative(a) && !isnegative(b)){
		removenegative(a);
		result = divide(a, b);
		addminus(a);
		addminus(&result);
		return result;
	}
	if(!isnegative(a) && isnegative(b)){
		removenegative(b);
		result = divide(a, b);
		addminus(b);
		addminus(&result);
		return result;
	}
	for(i = 0; i < l1; i++){
		if(a->str[i] == '0')
		count1++;
	}
	for(i = 0; i < l2; i++){
		if(b->str[i] == '0')
		count2++;
	}
	if((count1 != l1)&& (count2 == l2)){
		printf("Invalid expression\n");
		exit(0);
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	if((count1 == l1)&& (count2 != l2)){
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	if((count1 == l1)&& (count2 == l2)){
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	result.decimal = 0;
	result.str = (char *)malloc(sizeof(char)*l);
	if(b->str == "1"){
		result = c;
		return result;
	}
	if(c.decimal < d.decimal){
		addzeroestoright(&c, d.decimal - c.decimal);
	}
	l1 = strlen(c.str);
	l2 = strlen(d.str);
	if(l1 < l2){
		addzeroestoright(&c, l2 - l1 + 1);
	}
	addzeroestoright(&c, precision);
	addzeroeswithoutdecimal(&c, precision);
	l1 = strlen(c.str);
	l2 = strlen(d.str);
	l = l1 + l2;
	e = c;
	x.decimal = 0;
	x.str = "1";
	while(1){
		removezero(&e);
		removezero(&d);
		comp = isalargerthanb(&e, &d);
		if(comp != 1 ){
			break;
		}
		e = sub(&e, &d);
		result = add(&result, &x);
	}
	if(comp == -1)
		result = add(&result, &x);
	result.decimal = result.decimal + precision;
	return result;			
}
void removezero(Number *a){			/*Removes the extra zeroes at the starting of the string*/
	int ij = 0;
	int l;
	l = strlen(a->str);
	while(a->str[0] == '0'){
		l = strlen(a->str);
		while(ij < l){
			a->str[ij] = a->str[ij+1];
			ij++;
		}
		ij = 0;
	}
	return;
}
void addzeroeswithoutdecimal(Number *c, int b){		/*Add b zeroes to end of string in numbers without increasing the decimal place*/
	int i = strlen(c->str);
	while(b > 0){
		c->str[i] = '0';
		b--;
		i++;
	}
	return;
}
Number mod(Number *a, Number *b){			/*Returns the modulus of a by b*/
	Number c, d, e, result, x;
	int l1, l2, l = 0, comp = 1, flag = 0, i, count1 = 0, count2 = 0;
	c = *a;
	d = *b;
	l1 = strlen(a->str);
	l2 = strlen(b->str);
	l = l1 + l2;
	result.decimal = 0;
	result.str = (char *)malloc(sizeof(char)*l);
	for(i = 0; i < l1; i++){
		if(a->str[i] == '0')
		count1++;
	}
	for(i = 0; i < l2; i++){
		if(b->str[i] == '0')
		count2++;
	}
	if((count1 != l1)&& (count2 == l2)){
		printf("Invalid expression\n");
		exit(0);
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	if((count1 == l1)&& (count2 != l2)){
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	if((count1 == l1)&& (count2 == l2)){
		result.str = "0";
		result.decimal = 0;
		return result;
	}
	if(isnegative(a) && isnegative(b)){
		removenegative(a);
		removenegative(b);
		flag = 1;
	}
	else if(!isnegative(a) && isnegative(b)){
		removenegative(b);
		flag = 2;
	}
	else if(isnegative(a) && !isnegative(b)){
		removenegative(a);
		flag = 3;
	}
	l1 = strlen(c.str);
	l2 = strlen(d.str);
	l = l1 + l2;
	e = c;
	x.decimal = 0;
	x.str = "1";
	while(1){
		removezero(&e);
		removezero(&d);
		comp = isalargerthanb(&e, &d);
		if(comp != 1 ){
			break;
		}
		e = sub(&e, &d);
		result = add(&result, &x);
	}
	if(comp == -1){
		result.decimal = 0;
		result.str = "0";
	}
	else{
		result = e;
	}
	if(flag == 1 || flag == 3){
		addminus(&result);
	}
	return result;			
}
char* stringconvert(Number* val){			/*It converts the number val into charachter string x*/
	int a, b, i, j;
	char *x = (char *)malloc(sizeof(char)*1024);
	a = strlen(val->str);
	b = val->decimal;
	b = a - b;
	for(i = 0; i < a && i < b; i++){
		x[i] = val->str[i];
	}
	if(i == b && i < a){
		x[i++] = '.';
		while(i < a)
		x[i++] = val->str[i++];
	}
	return x;
}
