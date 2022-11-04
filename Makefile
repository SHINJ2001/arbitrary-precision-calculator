all: dll.o bc.o main.o

dll.o: dll.c dll.h
	cc -c dll.c

bc.o: bc.c bc.h
	cc -c bc.c

main.o: 
