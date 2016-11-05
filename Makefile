all: AVL.o main.o
	gcc -std=c11 -o lab06 AVL.o Heap.o main.o -Werror -Wall -pedantic

AVL.o: AVL.c
	gcc -std=c11 -o AVL.o -c AVL.c -Werror -Wall -pedantic

main.o: main.c
	gcc -std=c11 -o main.o -c main.c -Werror -Wall -pedantic

run:
	./lab06
	
clean:
	rm *.o
	rm lab06
