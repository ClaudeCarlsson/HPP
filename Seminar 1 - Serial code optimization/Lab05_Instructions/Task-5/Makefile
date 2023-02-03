all: inlining_example

inlining_example: inlining_example.c
	gcc -o inlining_example inlining_example.c -lm -ffunction-sections

clean:
	rm -rf inlining_example