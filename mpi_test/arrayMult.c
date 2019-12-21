#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE1 10
#define SIZE2 10
#define SIZE3 10

// int* rankArray(int* array){
//     int a,i,j;

//     for (i = 0; i <= SIZE1; i++) {
//         for(j=0;j<=SIZE2;j++){
//             srand((unsigned)time(NULL));
//             a = rand()%10;
//             array[i][j]=a;
//         }        
//     }
//     return *array;
// }

int main(int argc, char** argv) {
    int array1[SIZE1][SIZE2],array2[SIZE2][SIZE3],matrix[SIZE1][SIZE3];
    int i,j,k,temp;
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE1; i++) {
        for(j=0;j<SIZE2;j++){
            array1[i][j]=rand()%100;
        }
    }

    for (i = 0; i < SIZE2; i++) {
        for(j=0;j<SIZE3;j++){
            array2[i][j]=rand()%100;
        }        
    }

    MPI_Init(NULL,NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);// 得到当前进程的秩
    int world_size;//得到所有可以工作的进程数量(创建了几个进程)
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   
    // We are assuming at least 2 processes for this task
    if (world_size < 2) {
        fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if(world_rank==0){
        #pragma omp parallel for 
        for(i=0;i<SIZE1/2;i++){
            for(j=0;j<SIZE3;j++){
                for(k=0;k<SIZE2;k++){
                    matrix[i][j]=matrix[i][j]+array1[i][k]*array2[k][j]; 
                } 
            } 
        }
    }else if(world_rank==1){
        #pragma omp parallel for 
        for(i=SIZE1/2;i<SIZE1;i++){
            for(j=0;j<SIZE3;j++){
                for(k=0;k<SIZE2;k++){
                    matrix[i][j]=matrix[i][j]+array1[i][k]*array2[k][j]; 
                } 
            } 
        }
    }else if(world_rank==2){

    }else if(world_rank==3){

    }


    MPI_Finalize();
    

    for(i=0;i<SIZE1;i++){
        for(j=0;j<SIZE3;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    
    return 0;

}