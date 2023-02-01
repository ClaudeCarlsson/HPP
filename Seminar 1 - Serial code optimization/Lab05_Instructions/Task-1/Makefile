all: array_loop_s loop_invariants_s string_loop_s array_loop loop_invariants string_loop

array_loop: array_loop.c
	gcc -O2 array_loop.c -o array_loop

loop_invariants: loop_invariants.c
	gcc -O2 loop_invariants.c -o loop_invariants

string_loop: string_loop.c
	gcc -O2 string_loop.c -o string_loop

array_loop_s: array_loop.c
	gcc -O2 -fverbose-asm array_loop.c -S array_loop.s

loop_invariants_s: loop_invariants.c
	gcc -O2 -fverbose-asm loop_invariants.c -S loop_invariants.s

string_loop_s: string_loop.c
	gcc -O2 -fverbose-asm string_loop.c -S string_loop.s
clean:
	rm -rf loop_invariants string_loop array_loop *.s