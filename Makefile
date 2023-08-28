main: main.c regex.c regex.h
	clang -c main.c
	clang -c regex.c
	clang main.o regex.o -o main
