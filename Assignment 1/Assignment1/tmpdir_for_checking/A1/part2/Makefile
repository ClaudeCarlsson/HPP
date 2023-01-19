stuff.o: stuff.h stuff.c
	gcc -c stuff.c
themainprog.o: stuff.h themainprog.c
	gcc -c themainprog.c
pyramid: stuff.o themainprog.o
	gcc -o pyramid stuff.o themainprog.o
clean:
	rm -f pyramid stuff.o themainprog.o
