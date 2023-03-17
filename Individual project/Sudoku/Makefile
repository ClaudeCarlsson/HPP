# Compiler flags
CFLAGS = -O3 -ffast-math -march=native -fopenmp

# Linker flags
LDFLAGS = -lm -fopenmp

# Source files
SRC = sudoku.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = sudoku

all: $(EXEC)

$(EXEC): $(OBJ)
	gcc $(LDFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) solved_board.txt
