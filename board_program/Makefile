all: main.o
	gcc -o sym.out main.c -lpthread -lWiringpi
main.o: main.c
	gcc -c main.c

clean: 
	rm *.out
