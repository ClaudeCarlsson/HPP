#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

#define EPSILON_ZERO 0.001

typedef struct
{
    int N, nsteps, graphics;
    double delta_t, G;
    const char *filename;
} InputData;

typedef struct
{
    double x, y, mass, vx, vy, brightness;
} Particle;

typedef struct
{
    FILE *file;
    size_t filesize;
} InputFile;

typedef struct
{
    double x;
    double y;
} Force;

typedef struct
{
    double x;
    double y;
} Acceleration;

typedef struct
{
    double x;
    double y;
    double abs;
    double abs_eps_3pow;
} Distance;

typedef struct
{
    double x;
    double y;
} Position;

InputData get_inputs(char const *argv[])
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

InputFile read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    InputFile input_file;
    input_file.file = file;
    input_file.filesize = fileSize;

    return input_file;
}

void get_file_contents(InputFile input_file, Particle *p, int N)
{
    for (int i = 0; i < N; i++)
    {
        fread(&p[i], sizeof(Particle), N * 6, input_file.file);
    }
}

Particle *load_particles(InputData input)
{
    InputFile input_file = read_file(input.filename);
    Particle *p = malloc(input.N * sizeof(Particle));
    get_file_contents(input_file, p, input.N);
    return p;
}

int check_input_count(int argc)
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

void print_input(InputData input)
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
    const int windowWidth = 800;
    InitializeGraphics("Simulation", windowWidth, windowWidth);
    SetCAxes(0, 1);
}

void update_particles(Particle *p, InputData input)
{
    Position *pos = malloc(input.N * sizeof(Position));
    double temp = 0;

    for (int i = 0; i < input.N; i++)
    {
        Distance r = {0, 0, 0, 0};
        Force f = {0, 0};
        Acceleration a = {0, 0};

        for (int j = 0; j < input.N; j++)
        {
            if (i == j)
            {
                continue;
            }
            r.x = p[i].x - p[j].x;
            r.y = p[i].y - p[j].y;

            r.abs = sqrt((r.x * r.x) + (r.y * r.y));
            r.abs_eps_3pow = (r.abs + EPSILON_ZERO) * (r.abs + EPSILON_ZERO) * (r.abs + EPSILON_ZERO);

            temp = 1 / r.abs_eps_3pow;
            f.x += p[j].mass * temp * r.x;
            f.y += p[j].mass * temp * r.y;
        }
        // Force
        f.x *= -input.G * p[i].mass;
        f.y *= -input.G * p[i].mass;

        // Acceleration
        temp = 1 / p[i].mass;
        a.x = f.x * temp;
        a.y = f.y * temp;

        // Velocity
        p[i].vx = p[i].vx + input.delta_t * a.x;
        p[i].vy = p[i].vy + input.delta_t * a.y;

        // Position
        pos[i].x = p[i].x + input.delta_t * p[i].vx;
        pos[i].y = p[i].y + input.delta_t * p[i].vy;
    }

    for (int i = 0; i < input.N; i++)
    {
        // Update particle position per step
        p[i].x = pos[i].x;
        p[i].y = pos[i].y;
    }
}

void draw_particles(Particle *p, int N, float c_rad, float c_col, float L, float W)
{
    ClearScreen();
    for (int i = 0; i < N; i++)
    {
        DrawCircle(p[i].x, p[i].y, L, W, c_rad, c_col);
    }
    Refresh();
}

void start_system(Particle *p, InputData input)
{
    const float circleRadius = 0.005, circleColor = 0, L = 1, W = 1;
    for (int i = 0; i < input.nsteps; i++)
    {
        if (input.graphics)
        {
            draw_particles(p, input.N, circleRadius, circleColor, L, W);
        }

        update_particles(p, input);

        usleep(300);
    }
}

void write_to_output_file(Particle *p, int N)
{
    FILE *output = fopen("result.gal", "wb");

    for (int i = 0; i < N; i++)
    {
        fwrite(&p[i], sizeof(Particle), 1, output);
    }

    fclose(output);
}

int main(int argc, char const *argv[])
{
    // Checks input data
    InputData input;
    if (check_input_count(argc))
    {
        input = get_inputs(argv);
    }
    else
    {
        printf("Usage: %s  <N> <filename> <nsteps> <delta_t> <graphics> \n", argv[0]);
        return -1;
    }

    // Print inputs
    // print_input(input);

    // Load particles
    Particle *particles = load_particles(input);

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
