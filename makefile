parametrosCompilacao=-Wall #-Wshadow
nomePrograma=main

all: $(nomePrograma)

$(nomePrograma): main.o bst.o
	gcc -o $(nomePrograma) main.o bst.o -lm $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

bst.o: bst.h bst.c
	gcc -c bst.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)