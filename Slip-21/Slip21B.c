#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <mpi.h> 
#define ARRAY_SIZE 1000 
int main(int argc, char** argv) 
{ 
 int rank, size; 
 int array[ARRAY_SIZE]; 
 int i, sum = 0, global_sum = 0; 
 // Initialize MPI 
 MPI_Init(&argc, &argv); 
 MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 MPI_Comm_size(MPI_COMM_WORLD, &size); 
 // Initialize random number generator 
 srand(time(NULL) + rank); 
 // Fill array with random numbers 
 for (i = 0; i < ARRAY_SIZE; i++) { 
 array[i] = rand() % 1000; 
 } 
 // Calculate local sum of even numbers 
 for (i = 0; i < ARRAY_SIZE; i++) { 
 if (array[i] % 2 == 0) { 
 sum += array[i]; 
 } 
 } 
 // Reduce sum across all processes 
 MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
 if (rank == 0) { 
 printf("The sum of all even numbers in the array is: %d\n", global_sum); 
 } 
 // Finalize MPI 
 MPI_Finalize(); 
 return 0; 
}