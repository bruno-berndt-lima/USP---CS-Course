all: palavras

run:
	./palavras

palavras: main.o palavras.o
	gcc -g -o palavras main.o palavras.o

main.o: main.c palavras.h
	gcc -g -o main.o main.c -c

palavras.o: palavras.c palavras.h
	gcc -g -o palavras.o palavras.c -c

clean:
	rm -rf *.o

zip:
	zip -r palavras.zip Makefile ./*c ./*h
