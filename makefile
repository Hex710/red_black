parametrosCompilacao=-Wall #-Wshadow
nomePrograma=myrb

all: $(nomePrograma)

$(nomePrograma): myrb.o rb.o
	gcc -o $(nomePrograma) myrb.o rb.o -lm $(parametrosCompilacao)

myrb.o: myrb.c
	gcc -c myrb.c $(parametrosCompilacao)

rb.o: rb.h rb.c
	gcc -c rb.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)