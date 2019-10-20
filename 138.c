#include <stdio.h>
#include <stdlib.h> //malloc
#include <math.h> //sqrt, pow
#include <stdint.h> //int64_t
#include <mpi.h>

int main(){
  MPI_Init(NULL, NULL);
  int rank, world_size;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &world_size);
  MPI_Comm_rank(world, &rank);
  int64_t global_found = 0, local_found = 0, base = 16+(2*rank);
  int64_t total_leg_len = 0, local_leg_len = 0, leg = base;
  double height;
  MPI_Barrier(world);
  while(global_found < 12){
    //printf("Proc %i\tBase %i\tLeg %i\n", rank, base, leg);
    height = sqrt(pow(leg,2) - pow(base/2,2));
    if(height == base-1 || height == base+1){
      printf("Proc %i has found a triangle! Base: %i\tHeight: %i\tLeg: %i\n", rank, base, (int)height, leg);
      base+=(2*world_size);
      local_leg_len+=leg;
      local_found++;
      leg = (int)sqrt(pow(base-1,2)+pow(base/2,2))-1;
    } else if(height > base+1){
      base+=(2*world_size);
      leg = (int)sqrt(pow(base-1,2)+pow(base/2,2))-1;
    }
    MPI_Barrier(world);
    MPI_Allreduce(&local_found, &global_found, 1, MPI_INT, MPI_SUM, world);
    MPI_Reduce(&local_leg_len, &total_leg_len, 1, MPI_INT, MPI_SUM, 0, world);
    leg++;
  }
  if(rank == 0){
    printf("Total leg length is %i\n", total_leg_len);
  }
  MPI_Finalize();
  return 0;
}
