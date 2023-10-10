CFLAGS = -g -lm -Wall
main: main.c
	gcc -o main $(CFLAGS) main.c
