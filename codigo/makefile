tp2: main.o graph.o auxfunc.o
	gcc main.o graph.o auxfunc.o -o tp3 -lm

auxfunc.o: src/auxfunc.c include/auxfunc.h 
	gcc -c src/auxfunc.c -lm

graph.o: src/graph.c include/graph.h
	gcc -c src/graph.c -lm

main.o: main.c
	gcc -c main.c -lm

.PHONY: clean

clean:
	rm main.o auxfunc.o graph.o
