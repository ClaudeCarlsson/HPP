#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

found_solution = false;

void print_board(int N, int board[N][N])
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

bool validate(int row, int col, int candidate, int N, int N_sqrt, int board[N][N])
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

bool solve(int recursion_depth, int *unassigned_cells_idxs, int unassigned_cells_amount, int N, int N_sqrt, int board[N][N])
{
    if (unassigned_cells_amount == 0)
    {
// Sodoku solved here
#pragma omp critical
        {
            print_board(N, board);
            found_solution = true;
        }
        return true;
    }

    int unassigned_cell = unassigned_cells_idxs[unassigned_cells_amount - 1];

    int row = unassigned_cell / N;
    int col = unassigned_cell % N;

    for (int candidate = 1; candidate <= N; candidate++)
    {
#pragma omp flush(found_solution)
        if (!found_solution)
        {
            if (unassigned_cells_amount < 20)
            {
                if (validate(row, col, candidate, N, N_sqrt, board))
                {
                    board[row][col] = candidate;
                    solve(recursion_depth + 1, unassigned_cells_idxs, unassigned_cells_amount - 1, N, N_sqrt, board);
                }
            }
            else
            {
#pragma omp task firstprivate(board, row, col)
                {
                    if (validate(row, col, candidate, N, N_sqrt, board))
                    {
                        int new_board[N][N];
                        memcpy(new_board, board, N * N * sizeof(int));
                        new_board[row][col] = candidate;
                        solve(recursion_depth + 1, unassigned_cells_idxs, unassigned_cells_amount - 1, N, N_sqrt, new_board);
                    }
                }
            }
        }
    }

#pragma omp taskwait
    return false;
}

bool solve_serially(int recursion_depth, int *unassigned_cells_idxs, int unassigned_cells_amount, int N, int N_sqrt, int board[N][N])
{
    if (unassigned_cells_amount == 0)
    {
        // Sodoku solved here
        //printf("Recursion depth: %d \n", recursion_depth);
        print_board(N, board);
        found_solution = true;
        return true;
    }

    int unassigned_cell = unassigned_cells_idxs[unassigned_cells_amount - 1];

    int row = unassigned_cell / N;
    int col = unassigned_cell % N;

    for (int candidate = 1; candidate <= N; candidate++)
    {
        if (validate(row, col, candidate, N, N_sqrt, board))
        {
            board[row][col] = candidate;
            solve(recursion_depth + 1, unassigned_cells_idxs, unassigned_cells_amount - 1, N, N_sqrt, board);
        }
    }

    return false;
}

bool get_board_from_file(char *input_file, int N, int board[N][N])
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
            if (!fscanf(file, "%d, ", &board[i][j]))
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

    int board[N][N];

    if (get_board_from_file(input_file, N, board))
    {
        printf("Board successfully loaded! \n");
        print_board(N, board);
    }
    else
    {
        printf("Board could not be loaded! \n");
        return 1;
    }
        
    omp_set_nested(1);
    omp_set_num_threads(Threads);

    int *unassigned_cells_idxs = (int *)malloc(N * N * sizeof(int));
    int unassigned_cells_amount = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
            {
                unassigned_cells_idxs[unassigned_cells_amount] = i * N + j;
                unassigned_cells_amount++;
            }
        }
    }

    if(Threads == 1) 
    {
        solve_serially(0, unassigned_cells_idxs, unassigned_cells_amount, N, N_sqrt, board);
    } 
    else 
    {
    #pragma omp parallel
        {
            #pragma omp single
            solve(0, unassigned_cells_idxs, unassigned_cells_amount, N, N_sqrt, board);
            #pragma omp taskwait
        }
    }

    printf("Solution found!\n");

    return 0;
}