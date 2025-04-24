all: lista

run:
	./lista

lista: main.o lista.o funcs.o
	gcc -g -o lista main.o lista.o funcs.o

main.o: main.c doubly_linked_list.h funcs.h
	gcc -g -o main.o main.c -c

lista.o: doubly_linked_list.c doubly_linked_list.h
	gcc -g -o lista.o doubly_linked_list.c -c

funcs.o: funcs.c funcs.h
	gcc -g -o funcs.o funcs.c -c

clean:
	rm -rf *.o

zip:
	zip -r grandes_numeros.zip Makefile ./*c ./*h
