all: main.o
main.o: main.c constants.h types.h 
	gcc main.c chat.c -lpthread -lrt -o main.o


