all: arvore

run:
	./arvore

arvore: main.o treap.o
	gcc -g -o arvore main.o treap.o

main.o: main.c treap.h
	gcc -g -o main.o main.c -c

arvore.o: treap.c treap.h
	gcc -g -o treap.o treap -c

clean:
	rm -rf *.o

zip:
	zip -r arvore.zip Makefile ./*c ./*h
