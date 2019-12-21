#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define S 8

int main()
{
       int a[S];
       int rank, comm_size;
       int buff_size=S/comm_size;
       int a_buff[S];
       MPI_Init(0, 0);
       MPI_Comm_rank(MPI_COMM_WORLD, &rank);
       MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
       
       if (rank == 0)
       {
              a_buff[rank]=rank;
             MPI_Recv(a_buff,S,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
             for(int i=0;i<S;i++){
                    printf("%d\n",a_buff[i]);
             }
       }else{
              a_buff[rank]=rank;
              MPI_Send(a_buff,S,MPI_INT,0,0,MPI_COMM_WORLD);
       }

       MPI_Finalize();
       return 0;
}