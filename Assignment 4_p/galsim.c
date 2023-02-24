#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include <pthread.h>

#define EPSILON_ZERO 0.001

typedef struct
{
    int N, nsteps, graphics, n_threads;
    double delta_t, G;
    const char *filename;
} InputData;

typedef struct
{
    double x, y;
} Position;

typedef struct
{
    double x, y, mass, vx, vy, brightness;
} Particle;

typedef struct
{
    double x, y;
} Force;

typedef struct
{
    Particle *p;
    Position *pos;
    double **d;
    InputData input;
    int start_idx, end_idx, thread_idx;
} ThreadData;

InputData get_inputs(const char *argv[])
{
    InputData input;
    input.N = atoi(argv[1]);
    input.filename = argv[2];
    input.nsteps = atoi(argv[3]);
    input.delta_t = atof(argv[4]);
    input.graphics = atoi(argv[5]);
    input.n_threads = atoi(argv[6]);
    input.G = (double)100 / input.N;
    return input;
}

Particle *load_particles(const InputData input)
{
    Particle *p = malloc(input.N * sizeof(Particle));
    FILE *file = fopen(input.filename, "rb");
    if (!file)
    {
        printf("Error in load_particles, couldn't open file: %s\n", input.filename);
        free(p);
        exit(-1);
    }
    if (!fread(p, sizeof(Particle), input.N * 6, file))
    {
        printf("Error in load_particles, couldn't open file: %s\n", input.filename);
        fclose(file);
        free(p);
        exit(-1);
    }

    fclose(file);

    return p;
}

int check_input_count(const int argc)
{
    if (argc == 7)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_input(const InputData input)
{
    printf("Input values:\n");
    printf("N = %d\n", input.N);
    printf("filename = %s\n", input.filename);
    printf("nsteps = %d\n", input.nsteps);
    printf("delta_t = %f\n", input.delta_t);
    printf("graphics = %d\n", input.graphics);
    printf("n_threads = %d\n", input.n_threads);
    printf("(G = %f)\n", input.G);
}

void print_particle(const Particle *p, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("# %2.0d | x: %5.2lf, y: %5.2lf, mass: %5.2lf, vx: %5.2lf, vy: %5.2lf, brightness: %5.2lf\n",
               (i + 1), p[i].x, p[i].y, p[i].vx, p[i].vy, p[i].mass, p[i].brightness);
    }
}

void initialize_graphics()
{
    int windowWidth = 800;
    char windowName[10] = "Simulation";
    InitializeGraphics(windowName, windowWidth, windowWidth);
    SetCAxes(0, 1);
}

void *thread_function_distance(void *arg)
{
    ThreadData *thread_data = (ThreadData *)arg;

    for (int i = thread_data->thread_idx; i < thread_data->input.N; i += thread_data->input.n_threads) //-- Every n_threads for-loop
    // for (int i = thread_data->start_idx; i < thread_data->end_idx; i++) //-- Segmented for-loop
    {
        for (int j = i + 1; j < thread_data->input.N; j++)
        {
            thread_data->d[i][j] = sqrt((thread_data->p[i].x - thread_data->p[j].x) * (thread_data->p[i].x - thread_data->p[j].x) + (thread_data->p[i].y - thread_data->p[j].y) * (thread_data->p[i].y - thread_data->p[j].y));
            thread_data->d[j][i] = thread_data->d[i][j];
        }
    }

    pthread_exit(NULL);
}

void *thread_function_velocity_position(void *arg)
{
    ThreadData *thread_data = (ThreadData *)arg;
    Force f = {0, 0};
    double temp_distance = 0;

    for (int i = thread_data->thread_idx; i < thread_data->input.N; i+=thread_data->input.n_threads) //-- Every n_threads for-loop
    // for (int i = thread_data->start_idx; i < thread_data->end_idx; i++) //-- Segmented for-loop
    {
        f.x = 0;
        f.y = 0;
        for (int j = 0; j < thread_data->input.N; j++)
        {
            if (i == j)
            {
                continue;
            }
            temp_distance = 1 / ((thread_data->d[i][j] + EPSILON_ZERO) * (thread_data->d[i][j] + EPSILON_ZERO) * (thread_data->d[i][j] + EPSILON_ZERO));
            f.x += thread_data->p[j].mass * temp_distance * (thread_data->p[i].x - thread_data->p[j].x);
            f.y += thread_data->p[j].mass * temp_distance * (thread_data->p[i].y - thread_data->p[j].y);
        }

        // Velocity
        thread_data->p[i].vx += thread_data->input.delta_t * f.x * -thread_data->input.G;
        thread_data->p[i].vy += thread_data->input.delta_t * f.y * -thread_data->input.G;

        // Position
        thread_data->pos[i].x = thread_data->p[i].x + thread_data->input.delta_t * thread_data->p[i].vx;
        thread_data->pos[i].y = thread_data->p[i].y + thread_data->input.delta_t * thread_data->p[i].vy;
    }

    pthread_exit(NULL);
}

void draw_particles(Particle *p, const int N, const float c_rad, const float c_col, const float L, const float W)
{
    ClearScreen();
    for (int i = 0; i < N; i++)
    {
        DrawCircle(p[i].x, p[i].y, L, W, c_rad, c_col);
    }
    Refresh();
}

void update_particles(Particle *p, Position *pos, double **d, const InputData input)
{
    pthread_t thread[input.n_threads];
    ThreadData thread_data[input.n_threads];
    int particles_per_thread = input.N / input.n_threads;

    // Initialize thread arguments
    for (int i = 0; i < input.n_threads; i++)
    {
        thread_data[i].p = p;
        thread_data[i].pos = pos;
        thread_data[i].d = d;
        thread_data[i].input = input;
        thread_data[i].start_idx = (i)*particles_per_thread;
        thread_data[i].end_idx = (i + 1) * particles_per_thread;
        if (i == (input.n_threads - 1))
        {
            thread_data[i].end_idx = input.N;
        }
        thread_data[i].thread_idx = i;
    }

    for (int i = 0; i < input.n_threads; i++)
    {
        pthread_create(&thread[i], NULL, thread_function_distance, &thread_data[i]);
    }

    for (int i = 0; i < input.n_threads; i++)
    {
        pthread_join(thread[i], NULL);
    }

    for (int i = 0; i < input.n_threads; i++)
    {
        pthread_create(&thread[i], NULL, thread_function_velocity_position, &thread_data[i]);
    }

    for (int i = 0; i < input.n_threads; i++)
    {
        pthread_join(thread[i], NULL);
    }

    for (int i = 0; i < input.N; i++)
    {
        // Update particle position per step
        p[i].x = pos[i].x;
        p[i].y = pos[i].y;
    }
}

void start_system(Particle *p, const InputData input)
{
    const float c_rad = 0.005, c_col = 0;
    const int L = 1, W = 1;

    Position *pos = malloc(input.N * sizeof(Position));

    double **d = (double **)malloc(input.N * sizeof(double *));
    for (int i = 0; i < input.N; i++)
    {
        d[i] = (double *)malloc(input.N * sizeof(double));
    }

    for (int i = 0; i < input.nsteps; i++)
    {
        if (input.graphics)
        {
            draw_particles(p, input.N, c_rad, c_col, L, W);
        }

        update_particles(p, pos, d, input);
    }

    for (int i = 0; i < input.N; i++)
    {
        free(d[i]);
    }
    free(d);
    free(pos);
}

void write_to_output_file(const Particle *p, const int N)
{
    FILE *output = fopen("result.gal", "wb");
    fwrite(p, N * sizeof(Particle), 1, output);
    fclose(output);
}

int main(int argc, char const *argv[])
{
    // Checks input data
    if (!check_input_count(argc))
    {
        printf("Usage: %s  <N> <filename> <nsteps> <delta_t> <graphics> <n_threads> \n", argv[0]);
        return -1;
    }

    InputData input = get_inputs(argv);

    // Print inputs
    // print_input(input);

    // Load particles
    Particle *particles = load_particles(input);
    if (particles == NULL)
    {
        printf("Error loading the particles");
        return -1;
    }

    // Print particles
    // print_particle(particles, input.N);

    // Check graphics
    if (input.graphics)
    {
        initialize_graphics();
    }

    // Start system
    start_system(particles, input);

    // Write result to file
    write_to_output_file(particles, input.N);

    // Quit graphics if enabled
    if (input.graphics)
    {
        FlushDisplay();
        CloseDisplay();
    }

    free(particles);

    return 0;
}
