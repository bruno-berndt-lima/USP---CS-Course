all: lista

run:
	./exec

lista: main.o skip_list.o funcs.o
	gcc -g -o exec main.o skip_list.o funcs.o

main.o: main.c skip_lists.h funcs.h
	gcc -g -o main.o main.c -c

skip_list.o: skip_lists.c skip_lists.h
	gcc -g -o skip_list.o skip_lists.c -c

funcs.o: funcs.c funcs.h
	gcc -g -o funcs.o funcs.c -c

clean:
	rm -rf *.o

zip:
	zip -r dicionario.zip Makefile ./*c ./*h
