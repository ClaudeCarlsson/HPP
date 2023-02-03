CC = gcc
LD = gcc
CFLAGS = -O3 -ffast-math -fopt-info-vec -march=native
LDFLAGS = 
RM = /bin/rm -f
OBJS = matvec.o 
EXECUTABLE = matvec

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

matvec.o: matvec.c
	$(CC) $(CFLAGS) -c matvec.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
