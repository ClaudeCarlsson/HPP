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
    double x, y;
} Position;

typedef struct
{
    double x, y, mass, vx, vy, brightness;
} Particle;

typedef struct
{
    double x, y, abs, abs_eps_3pow;
} Distance;

typedef struct
{
    double x, y;
} Force;

typedef struct
{
    double x, y;
} Acceleration;

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
    
    FILE *file = fopen(input.filename, "rb");
    if(!file)
    {
        printf("Error in load_particles(), couldn't open file: %s\n",input.filename);
        exit(-1);
    }

    Particle *p = malloc(input.N * sizeof(Particle));
    if(!fread(p, sizeof(Particle), input.N * 6, file)) 
    {
        printf("Error in load_particles(), couldn't open file: %s\n",input.filename);
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

void update_particles(Particle *p, const InputData input)
{
    Distance r = {0, 0, 0};
    Force f = {0, 0};
    Acceleration a = {0, 0};
    Position *pos = malloc(input.N * sizeof(Position));
    double temp = 0;

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
        p[i].vx += input.delta_t * a.x;
        p[i].vy += input.delta_t * a.y;

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

    free(pos);
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
    for (int i = 0; i < input.nsteps; i++)
    {
        if (input.graphics)
        {
            draw_particles(p, input.N, c_rad, c_col, L, W);
        }

        update_particles(p, input);

        // usleep(500);
    }
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
    if (particles == NULL) {
        printf("test");
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
