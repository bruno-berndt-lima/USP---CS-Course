all: sequencia

run:
	./sequencia

sequencia: main.o sequencia.o
	gcc -g -o sequencia main.o sequencia.o

main.o: main.c stack.h
	gcc -g -o main.o main.c -c

sequencia.o: stack.c stack.h
	gcc -g -o sequencia.o stack.c -c

clean:
	rm -rf *.o

zip:
	zip -r sequencia.zip Makefile ./*c ./*h
