all: other-loop simple-loop

other-loop: other-loop.c
	gcc -fopenmp other-loop.c -o other-loop -lm
	
simple-loop: simple-loop.c
	gcc -fopenmp simple-loop.c -o simple-loop -lm

clean:
	rm -rf other-loop simple-loop