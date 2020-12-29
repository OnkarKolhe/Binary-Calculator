all: project
project: cstack.o stack.o Number.o gettoken.o 
	gcc cstack.o stack.o Number.o gettoken.o -o project
cstack.o: cstack.c cstack.h 
	gcc -c cstack.c
stack.o: stack.c stack.h Number.h
	gcc -c stack.c
gettoken.o: gettoken.c Number.h
	gcc -c gettoken.c
Number.o: Number.c Number.h
	gcc -c Number.c
clean: 
	rm *.o
