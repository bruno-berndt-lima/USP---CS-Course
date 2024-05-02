all: fila

run:
	./fila

fila: main.o fila.o
	gcc -g -o fila main.o fila.o

main.o: main.c fila.h
	gcc -g -o main.o main.c -c

fila.o: fila.c fila.h
	gcc -g -o fila.o fila.c -c

clean:
	rm -rf *.o

zip:
	zip -r fila.zip Makefile ./*c ./*h
