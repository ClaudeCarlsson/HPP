all: threaded_computation computation

computation: computation.c
	gcc -g -Wall computation.c -o computation

threaded_computation: threaded_computation.c
	gcc -g -Wall -lpthread threaded_computation.c  -o threaded_computation

clean:
	rm -rf threaded_computation computation