#include <stdio.h> //Slip11B
#include <stdlib.h> 
#include <mpi.h> 
#define ARRAY_SIZE 1000 
int main(int argc, char *argv[])
{ 
    int rank, size; 
    int i, min, max; 
    int data[ARRAY_SIZE]; 
    int local_min, local_max; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    // Generate random data on root process 
    if (rank == 0)
    { 
        printf("Generating random data...\n"); 
        for (i = 0; i < ARRAY_SIZE; i++)
        { 
            data[i] = rand() % 100; 
        } 
    } 
    // Scatter data to all processes 
    MPI_Scatter(data, ARRAY_SIZE/size, MPI_INT, data, ARRAY_SIZE/size, MPI_INT, 0, MPI_COMM_WORLD); 
    // Calculate local min and max 
    local_min = data[0]; 
    local_max = data[0]; 
    for (i = 1; i < ARRAY_SIZE/size; i++)
    { 
        if (data[i] < local_min)
        { 
            local_min = data[i]; 
        } 
        if (data[i] > local_max)
        { 
            local_max = data[i]; 
        } 
    } 
    // Reduce local min and max to get the final min and max 
    MPI_Reduce(&local_min, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); 
    MPI_Reduce(&local_max, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 
    // Print the final min and max on root process 
    if (rank == 0)
    { 
        printf("The minimum number is: %d\n", min); 
        printf("The maximum number is: %d\n", max); 
    } 
    MPI_Finalize(); 
    return 0;
}