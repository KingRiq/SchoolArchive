main: mystring.h main.c strings.o
	clang -Wall main.c strings.o -o main
strings.o: mystring.h strings.c
	clang -Wall strings.c -o strings.o -c
