all: lista

run:
	./exec

lista: main.o linked_list.o
	gcc -g -o exec main.o linked_list.o

main.o: main.c linked_list.h
	gcc -g -o main.o main.c -c

linked_list.o: linked_list.c linked_list.h
	gcc -g -o linked_list.o linked_list.c -c

clean:
	rm -rf *.o

zip:
	zip -r polinomios.zip Makefile ./*c ./*h
