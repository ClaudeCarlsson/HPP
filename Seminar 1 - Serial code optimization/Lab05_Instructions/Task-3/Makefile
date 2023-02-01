all: denorms norms task3 small

denorms: denorms.c
	gcc -O2 denorms.c -o denorms

task3: task3.c
	gcc -O2 task3.c -o task3

norms: norms.c
	gcc -O2 norms.c -o norms

small: small.c
	gcc -O2 small.c -o small -lm


clean:
	rm -rf denorms norms task3 small