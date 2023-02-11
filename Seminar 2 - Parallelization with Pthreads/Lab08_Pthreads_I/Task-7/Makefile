all: threaded_computation

threaded_computation: threaded_computation.c
	gcc -g -Wall -lpthread threaded_computation.c  -o threaded_computation -lm 

clean:
	rm -rf threaded_computation