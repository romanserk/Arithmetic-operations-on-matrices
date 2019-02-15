main.out: mymat.c mat.h mat.o
	gcc -Wall -pedantic -ansi -g mymat.c mat.o -o mymat.out
mat.o: mat.c
	gcc -Wall -pedantic -ansi -g mat.c -c
