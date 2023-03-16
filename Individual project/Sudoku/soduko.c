#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void print_board(int **board, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool validate(int **board, int row, int col, int candidate, int N, int N_sqrt)
{

    // Search for duplicate numbers in the rows and columns

    for (int i = 0; i < N; i++)
    {
        if (board[row][i] == candidate || board[i][col] == candidate)
        {
            return false;
        }
    }

    // Search in the box for duplicate numbers
    int box_row = row - (row % N_sqrt);
    int box_col = col - (col % N_sqrt);

    for (int i = 0; i < N_sqrt; i++)
    {
        for (int j = 0; j < N_sqrt; j++)
        {
            if (board[i + box_row][j + box_col] == candidate)
            {
                return false;
            }
        }
    }

    return true;
}

bool solve(int recursion_depth, int row, int col, int **board, int N, int N_sqrt, bool *found_solution)
{
    if (col == N)
    {
        col = 0;
        row++;
        if (row == N)
        {
            #pragma omp critical
            {
                if (!*found_solution)
                {
                    print_board(board, N);
                    *found_solution = true;
                }
            }
            return true;
        }
    }

    if (board[row][col] != 0)
    {
        return solve(recursion_depth + 1, row, col + 1, board, N, N_sqrt, found_solution);
    }

    for (int candidate = 1; candidate <= N; candidate++)
    {
        if (validate(board, row, col, candidate, N, N_sqrt))
        {
            #pragma omp task firstprivate(row, col, candidate) shared(found_solution)
            {
                if (!*found_solution)
                {
                    int **new_board = (int **)malloc(N * sizeof(int *));
                    for (int i = 0; i < N; i++)
                    {
                        new_board[i] = (int *)malloc(N * sizeof(int));
                        memcpy(new_board[i], board[i], N * sizeof(int)); // Copy the contents of the original board to the new
                    }

                    new_board[row][col] = candidate;
                    if (solve(recursion_depth + 1, row, col + 1, new_board, N, N_sqrt, found_solution))
                    {
                        #pragma omp critical
                        {
                            if (!*found_solution)
                            {
                                print_board(new_board, N);
                                *found_solution = true;
                            }
                        }
                    }

                    for (int i = 0; i < N; ++i)
                    {
                        free(new_board[i]);
                    }
                    free(new_board);
                }
            }
        }
    }
#pragma omp taskwait
    return *found_solution;
}

bool get_board_from_file(char *input_file, int **board, int N)
{
    FILE *file = fopen(input_file, "r");
    if (!file)
    {
        printf("Error opening file!\n");
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!fscanf(file, "%d,", &board[i][j]))
            {
                printf("Error reading file!\n");
                return false;
            }
        }
    }
    fclose(file);
    return true;
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Usage: %s <N> <Input File> <Threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int N_sqrt = sqrt(N);
    char *input_file = argv[2];
    int Threads = atoi(argv[3]);

    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        board[i] = (int *)malloc(N * sizeof(int));
        // Initialize board to all zeros
        memset(board[i], 0, N * sizeof(int));
    }

    if (get_board_from_file(input_file, board, N))
    {
        printf("Board successfully loaded! \n");
        print_board(board, N);
    }
    else
    {
        printf("Board could not be loaded! \n");
        return 1;
    }

    omp_set_num_threads(Threads);

    bool found_solution = false;

#pragma omp parallel
    {
#pragma omp single
        solve(0, 0, 0, board, N, N_sqrt, &found_solution);
#pragma omp taskwait
    }

    printf("Solution found!\n");

    for (int i = 0; i < N; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}
