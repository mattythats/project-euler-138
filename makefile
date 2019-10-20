all: 138 138-seq

138: 138.c
	mpicc -o 138 138.c -lm

138-seq: 138-seq.c
	gcc -o 138-seq 138-seq.c -lm