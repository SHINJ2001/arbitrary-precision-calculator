all: dll.o bc.o main.o
	cc dll.o bc.o main.o -o bc

dll.o: dll.c dll.h
	cc -c dll.c

bc.o: bc.c bc.h
	cc -c bc.c

main.o: main.c
	cc -c main.c

clean:
	rm *.o
