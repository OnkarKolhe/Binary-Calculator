#define precision 1
typedef struct node{
	char digit;
	struct node *next, *prev;
}node;
typedef struct number{
	node *h, *t;
	int decimal;
}number;
typedef struct Number{
	char *str;
	int decimal;
}Number;
void addminus(Number *a);
void ninit(number *a);
void append(number *a, char ch);
Number convert(number *a);
int decimalposition(number *a);
void removedecimal(Number *a);
Number add(Number *a, Number *b);
void printno(Number *a);
int isnegative(Number *a);
void removenegative(Number *a);
int isalargerthanb(Number *a, Number *b);
Number sub(Number *a, Number *b);
Number mult(Number *a, Number *b);
Number divide(Number *a, Number *b);
void removezero(Number *a);
void addzeroeswithoutdecimal(Number *a, int b);
Number mod(Number *a, Number*b);
char* stringconvert(Number *a);
