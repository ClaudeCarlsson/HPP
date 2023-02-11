all: threadtest

threaded_computation: threadtest.c
	gcc -g -Wall -lpthread threadtest.c  -o threadtest -lm 

clean:
	rm -rf threadtest