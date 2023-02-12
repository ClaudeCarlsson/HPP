all: wait_test

threaded_computation: wait_test.c
	gcc -g -Wall -lpthread wait_test.c  -o wait_test -lm 

clean:
	rm -rf wait_test