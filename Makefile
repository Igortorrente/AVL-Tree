all: AVL.o main.o
	gcc -std=c11 -o Exe AVL.o main.o -Wall -pedantic

AVL.o: AVL.c
	gcc -std=c11 -o AVL.o -c AVL.c -Wall -pedantic 

main.o: main.c
	gcc -std=c11 -o main.o -c main.c -Wall -pedantic 

run:
	./Exe
	
clear:
	rm Exe
	rm *.o