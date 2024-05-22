all: lista

run:
	./lista

lista: main.o lista.o
	gcc -g -o lista main.o lista.o

main.o: main.c lista.h
	gcc -g -o main.o main.c -c

lista.o: lista.c lista.h
	gcc -g -o lista.o lista.c -c

clean:
	rm -rf *.o

zip:
	zip -r lista.zip Makefile ./*c ./*h
