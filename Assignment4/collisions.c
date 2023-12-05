#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// particle structure
typedef struct particle{
    double x_pos, y_pos; 
    double u, v; 
    double last_update_time;
    int c_wall, c_particles;  
} Particle;

// potential coolision structure
typedef struct collision{
    int particle1, particle2; 
    double time;
} Collision;

// calculate the distance between two given particles
double distance(Particle p1, Particle p2) {
    return sqrt(pow(p1.x_pos - p2.x_pos, 2) + pow(p1.y_pos - p2.y_pos, 2));
}

// Function to calculate potential collision time between two particles
double calculateCollisionTime(Particle p1, Particle p2) {
    // Implement collision time calculation logic here
    // You can use the relative velocity and particle radii to calculate the time.
    // Return a large value if no collision is possible.
}

// Function to calculate potential collision time between a particle and a wall
double calculateWallCollisionTime(Particle p, double boxSize, int wall) {
    // Implement wall collision time calculation logic here
    // You can use the particle velocity and position to calculate the time.
    // Return a large value if no collision is possible.
}

// Function to swap two collisions in the array
void swap(Collision *a, Collision *b) {
    Collision temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform insertion sort on an array of collisions
void insertionSort(Collision *collisions, int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        Collision key = collisions[i];
        j = i - 1;

        while (j >= 0 && collisions[j].time > key.time) {
            collisions[j + 1] = collisions[j];
            j = j - 1;
        }
        collisions[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    char *input_filename = argv[1];
    double end_time = atof(argv[2]);

    FILE *file = fopen(input_filename, "r");
    
    int N; // the number of total particles
    fscanf(file, "%d", &N);

    // Dynamically allocate memory for particles and collisions
    Particle *particles = (Particle *)malloc(N * sizeof(Particle));
    Collision *collisions = (Collision *)malloc(N * (N - 1) / 2 * sizeof(Collision));

    // Initialize particles and calculate initial collision times
    // Implement particle initialization and collision time calculation logic here

    // Sort the array of potential collisions (using insertion sort)
    insertionSort(collisions, N * (N - 1) / 2);

    // Simulate collisions until the end time is reached
    while (collisions[0].time < end_time) {
        // Process the earliest potential collision
        // Implement collision processing logic here

        // Update collision times for particles involved in the last collision
        // Implement collision time update logic here

        // Sort the array of potential collisions again
        insertionSort(collisions, N * (N - 1) / 2);
    }

    // Update all particle positions to the end time
    // Implement particle position update logic here

    
    // output final states & counts of wall collisions & counts of particles coolisions
    for (int i = 0; i < N; i++) {
        printf("%.6f, %.6f, %d, %d\n", particles[i].x_pos, particles[i].y_pos, particles[i].c_wall, particles[i].c_particles);
    }

    
    free(particles);
    free(collisions);

    return 0;
}
