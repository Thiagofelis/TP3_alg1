tp2: main_aval.o graph.o auxfunc.o
	gcc main_aval.o graph.o auxfunc.o -o tp3_aval_t2 -lm

auxfunc.o: src/auxfunc.c include/auxfunc.h
	gcc -c src/auxfunc.c -lm

graph.o: src/graph.c include/graph.h
	gcc -c src/graph.c -lm

main.o: main_aval.c
	gcc -c main_aval.c -lm

.PHONY: clean

clean:
	rm main_aval.o auxfunc.o graph.o

debug: main_aval.o graph.o auxfunc.o
	gcc -g main_aval.o graph.o auxfunc.o -o tp3_debug -lm
