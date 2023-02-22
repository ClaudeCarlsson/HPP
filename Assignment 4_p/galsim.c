#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include <pthread.h>

#define EPSILON_ZERO 0.001

typedef struct
{
    int N, nsteps, graphics;
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

InputData get_inputs(const char *argv[])
{
    InputData input;
    input.N = atoi(argv[1]);
    input.filename = argv[2];
    input.nsteps = atoi(argv[3]);
    input.delta_t = atof(argv[4]);
    input.graphics = atoi(argv[5]);
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
    if (argc == 6)
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

void draw_particles(Particle *p, const int N, const float c_rad, const float c_col, const float L, const float W)
{
    ClearScreen();
    for (int i = 0; i < N; i++)
    {
        DrawCircle(p[i].x, p[i].y, L, W, c_rad, c_col);
    }
    Refresh();
}

typedef struct {
    Particle *p;
    Position *pos;
    double **d;
    int start_index;
    int end_index;
    InputData input;
} ThreadData;

#define NUM_THREADS 1

void *update_particles_helper(void *thread_data)
{
    ThreadData *data = (ThreadData *) thread_data;

    double temp_distance;
    Force f = {0, 0};

    for (int i = data->start_index; i < data->end_index; i++) {
        for (int j = 0; j < data->input.N; j++) {
            if (i == j) {
                continue;
            }

            temp_distance = 1 / ((data->d[i][j] + EPSILON_ZERO) * (data->d[i][j] + EPSILON_ZERO) * (data->d[i][j] + EPSILON_ZERO));
            f.x += data->p[j].mass * temp_distance * (data->p[i].x - data->p[j].x);
            f.y += data->p[j].mass * temp_distance * (data->p[i].y - data->p[j].y);
        }

        // Velocity
        data->p[i].vx += data->input.delta_t * f.x * -data->input.G;
        data->p[i].vy += data->input.delta_t * f.y * -data->input.G;

        // Position
        data->pos[i].x = data->p[i].x + data->input.delta_t * data->p[i].vx;
        data->pos[i].y = data->p[i].y + data->input.delta_t * data->p[i].vy;

        // Reset force
        f.x = 0;
        f.y = 0;
    }

    pthread_exit(NULL);
}

void update_particles(Particle *p, Position *pos, double **d, const InputData input)
{
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Initialize thread data
    int particles_per_thread = input.N / NUM_THREADS;
    int remainder_particles = input.N % NUM_THREADS;
    int start_index = 0;
    int end_index = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        start_index = end_index;
        end_index = start_index + particles_per_thread;

        if (i == NUM_THREADS - 1) {
            end_index += remainder_particles;
        }

        thread_data[i].p = p;
        thread_data[i].pos = pos;
        thread_data[i].d = d;
        thread_data[i].start_index = start_index;
        thread_data[i].end_index = end_index;
        thread_data[i].input = input;

        pthread_create(&threads[i], NULL, update_particles_helper, (void *)&thread_data[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < input.N; i++)
    {
        // Update particle position per step
        p[i].x = thread_data[i].pos->x;
        p[i].y = thread_data[i].pos->y;
        p[i].vx = thread_data[i].p->vx;
        p[i].vy = thread_data[i].p->vy;
    }
}

void start_system(Particle *p, const InputData input)
{
    //const float c_rad = 0.005, c_col = 0;
    //const int L = 1, W = 1;

    Position *pos = malloc(input.N * sizeof(Position));

    double **d = (double **)malloc(input.N * sizeof(double *));
    for (int i = 0; i < input.N; i++)
    {
        d[i] = (double *)malloc(input.N * sizeof(double));
    }

    for (int i = 0; i < input.nsteps; i++)
    {
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
        printf("Usage: %s  <N> <filename> <nsteps> <delta_t> <graphics> \n", argv[0]);
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
    print_particle(particles, input.N);

    // Check graphics
    if (input.graphics)
    {
        initialize_graphics();
    }

    // Start system
    start_system(particles, input);

    // Print particles
    print_particle(particles, input.N);

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
