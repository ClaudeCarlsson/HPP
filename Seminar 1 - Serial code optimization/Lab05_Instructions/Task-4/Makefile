all: lookup math_functions memset strength_reduction timings

lookup: lookup.c
	gcc -O3 lookup.c -o lookup -lm

math_functions: math_functions.c
	gcc -O3 math_functions.c -o math_functions -lm

memset: memset.c
	gcc -O3 memset.c -o memset -lm

strength_reduction: strength_reduction.c
	gcc -O3 strength_reduction.c -o strength_reduction -lm

timings: timings.c
	gcc -O3 timings.c -o timings -lm


clean:
	rm -rf lookup math_functions memset strength_reduction timings