all: loop 

loop: loop.c
	gcc -fopenmp loop.c -o loop -lm
	
clean:
	rm -rf loop