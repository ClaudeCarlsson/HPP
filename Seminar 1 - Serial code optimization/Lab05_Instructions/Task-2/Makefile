all: bounds_s short-circuit_s bounds short-circuit

short-circuit: short-circuit.c
	gcc -O2 short-circuit.c -o short-circuit

bounds: bounds.c
	gcc -O2 bounds.c -o bounds

short-circuit_s: short-circuit.c
	gcc -O2 -fverbose-asm short-circuit.c -S short-circuit.s

bounds_s: bounds.c
	gcc -O2 -fverbose-asm bounds.c -S bounds.s

clean:
	rm -rf short-circuit bounds *.s