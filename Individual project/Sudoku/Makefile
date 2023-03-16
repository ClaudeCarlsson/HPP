# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -O3 -ffast-math -march=native -fopenmp

# Linker flags
LDFLAGS = -lm -fopenmp

# Source files
SRC = soduko.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = soduko

all: $(EXEC)

$(EXEC): $(OBJ)
	gcc $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
