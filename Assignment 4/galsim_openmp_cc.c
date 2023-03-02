#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include <omp.h>

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

void update_particles(Particle *p, Position *pos, double **d, const InputData input)
{
    Force f = {0, 0};
    double temp_distance = 0;
#pragma omp parallel for
    for (int i = 0; i < input.N; i++)
    {
        for (int j = i + 1; j < input.N; j++)
        {
            d[i][j] = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
            d[j][i] = d[i][j];
        }
    }
#pragma omp parallel for
    for (int i = 0; i < input.N; i++)
    {
        f.x = 0;
        f.y = 0;
        for (int j = 0; j < input.N; j++)
        {
            if (i == j)
            {
                continue;
            }
            temp_distance = 1 / ((d[i][j] + EPSILON_ZERO) * (d[i][j] + EPSILON_ZERO) * (d[i][j] + EPSILON_ZERO));
            f.x += p[j].mass * temp_distance * (p[i].x - p[j].x);
            f.y += p[j].mass * temp_distance * (p[i].y - p[j].y);
        }

        // Velocity
        p[i].vx += input.delta_t * f.x * -input.G;
        p[i].vy += input.delta_t * f.y * -input.G;

        // Position
        pos[i].x = p[i].x + input.delta_t * p[i].vx;
        pos[i].y = p[i].y + input.delta_t * p[i].vy;
    }

#pragma omp parallel for
    for (int i = 0; i < input.N; i++)
    {
        // Update particle position per step
        p[i].x = pos[i].x;
        p[i].y = pos[i].y;
    }
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

    // Set the amount of threads
    omp_set_num_threads(input.n_threads);

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
