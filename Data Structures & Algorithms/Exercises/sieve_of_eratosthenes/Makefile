all: crivo

run:
	./crivo

crivo: main.o crivo.o
	gcc -g -o crivo main.o crivo.o

main.o: main.c crivo.h
	gcc -g -o main.o main.c -c

crivo.o: crivo.c crivo.h
	gcc -g -o crivo.o crivo.c -c

clean:
	rm -rf *.o

zip:
	zip -r crivo.zip Makefile ./*c ./*h
