all: arvore

run:
	./arvore

arvore: main.o binary_tree.o
	gcc -g -o arvore main.o binary_tree.o

main.o: main.c binary_tree.h
	gcc -g -o main.o main.c -c

arvore.o: binary_tree.c binary_tree.h
	gcc -g -o binary_tree.o binary_tree -c

clean:
	rm -rf *.o

zip:
	zip -r arvore.zip Makefile ./*c ./*h
