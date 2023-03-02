CFLAGS=-O3 -ffast-math -march=native -fopenmp
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm -fopenmp

galsim: galsim.o graphics.o
	gcc -o galsim galsim.o graphics.o $(LDFLAGS)

graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c


galsim.o: galsim.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c


clean:
	rm -f galsim *.o result.gal