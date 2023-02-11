all: mutextest

threaded_computation: mutextest.c
	gcc -g -Wall -lpthread mutextest.c  -o mutextest -lm 

clean:
	rm -rf mutextest