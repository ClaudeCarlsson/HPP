#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

// Gloabl variable for checking if a solution is found
volatile bool found_solution = false;

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

    // The checks has been passed, a possible candidate
    return true;
}

bool solve(int *unassigned_cells_idxs, int unassigned_cells_amount, int N, int N_sqrt, int board[N][N], int (*solved_board)[N])
{
    // Check to see if a solution is found
    if (unassigned_cells_amount == 0)
    {
        // Sodoku solved here
        #pragma omp critical
        {
            found_solution = true;
            // Flush the variable after writing it to ensure cache coherence
            #pragma omp flush(found_solution)
            // Copy a board to print it later
            memcpy(solved_board, board, N * N * sizeof(int));
        }
        return true;
    }

    // Get the cell
    int unassigned_cell = unassigned_cells_idxs[unassigned_cells_amount - 1];

    // Calculate the row and column
    int row = unassigned_cell / N;
    int col = unassigned_cell % N;

    // Starta a taskgroup
    #pragma omp taskgroup
    {
        // Loop the candidates
        for (int candidate = 1; candidate <= N; candidate++)
        {
            // Flush the variable before reading it to ensure cache coherence
            #pragma omp flush(found_solution)

            // Check that no solutions already exists
            if (!found_solution)
            {
                // To run only serial when 1 thread is enabled, change the if-statement
                //if (unassigned_cells_amount < 25 || omp_get_max_threads() == 1)
                if (unassigned_cells_amount < 25)
                {
                    // Validate the candidate
                    if (validate(row, col, candidate, N, N_sqrt, board))
                    {
                        // Candidate valid
                        board[row][col] = candidate;
                        solve(unassigned_cells_idxs, unassigned_cells_amount - 1, N, N_sqrt, board, solved_board);
                    }
                    board[row][col] = 0;
                }
                else
                {
                    // Start a task
                    #pragma omp task firstprivate(board, row, col)
                    {
                        // Validate the candidate
                        if (validate(row, col, candidate, N, N_sqrt, board))
                        {
                            // Candidate valid
                            // Check for cancellation
                            #pragma omp cancellation point taskgroup

                            // Make a copy of the board
                            int new_board[N][N];
                            memcpy(new_board, board, N * N * sizeof(int));
                            new_board[row][col] = candidate;

                            // Recursive call, check if that path solves the board
                            if (solve(unassigned_cells_idxs, unassigned_cells_amount - 1, N, N_sqrt, new_board, solved_board))
                            {
                                // Board solved, set global flag
                                found_solution = true;

                                // Flush the variable after writing it to ensure cache coherence
                                #pragma omp flush(found_solution)

                                // Since the board is solved we stop the task group
                                #pragma omp cancel taskgroup
                            }
                        }
                        // Check for cancellation
                        #pragma omp cancellation point taskgroup
                    }
                }
            }
        }
    }
    // Wait for all the tasks
    #pragma omp taskwait
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


void write_board(int N, int board[N][N])
{
    FILE *file = fopen("solved_board.txt", "w");
    if (!file)
    {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(file, "%d ", board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


int main(int argc, char *argv[])
{
    // Read input
    if (argc != 5)
    {
        printf("Usage: %s <N> <Input File> <Threads> <Output 0 or 1>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int N_sqrt = sqrt(N);
    char *input_file = argv[2];
    int Threads = atoi(argv[3]);
    int output = atoi(argv[4]);

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

    // Set the number of threads
    #ifdef _OPENMP
    omp_set_num_threads(Threads);
    #endif

    // Find unassigned cells
    int unassigned_cells_amount = 0;
    int *unassigned_cells_idxs = (int *)malloc(N * N * sizeof(int));
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
    // Make a solved board to print later 
    int solved_board[N][N];

    #ifdef _OPENMP
    double start_time = omp_get_wtime();
    #endif

    // Start the parallel region
    #pragma omp parallel
    {
        #pragma omp single
        solve(unassigned_cells_idxs, unassigned_cells_amount, N, N_sqrt, board, solved_board);
        #pragma omp taskwait
    }
    
    #ifdef _OPENMP
    double end_time = omp_get_wtime();
    #endif
    // Free the allocated memory
    free(unassigned_cells_idxs);

    printf("Solution found!\n");
    print_board(N, solved_board);
    if(output) {
        write_board(N, solved_board);
    }
    #ifdef _OPENMP
    printf("Time it took: %f\n", end_time - start_time);
    #endif
    return 0;
}