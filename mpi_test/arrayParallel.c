#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
#include "mpich/mpi.h"

#define SIZE 5
#define SQUARE 3
#define DEFAULT_OMP_NUM 4

typedef struct
{
    /* data */
    int comm_rank;
    union {
        int num; //凸点值
        int x;   //横坐标
        int y;   //纵坐标
    } number;

} CommRankNumber;

int main(int argc, char *argv[])
{
    int i, j;
    double start, end;
    int **arrayA, **arrayB, **matrix;

    //init MPI environment
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /*获取当前正在运行进程的标识号*/
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /*获取所有参与运算的进程个数*/

    //each process need to do
    int length = SIZE / comm_size;
    //init arrays
    arrayA=(int **)calloc(SIZE,sizeof(int));
    arrayB=(int **)calloc(SIZE,sizeof(int));
    matrix=(int **)calloc(SIZE,sizeof(int));
    for (i = 0; i < SIZE; i++)
    {
        arrayA[i] = (int *)calloc(SIZE, sizeof(int));
        arrayB[i] = (int *)calloc(SIZE, sizeof(int));
        matrix[i] = (int *)calloc(SIZE, sizeof(int));
    }

    //暂存数组
    int **buff_scatterA, **buff_scatterB, **buff_scatterM;
    buff_scatterA=(int **)calloc(SIZE,sizeof(int));
    buff_scatterB=(int **)calloc(SIZE,sizeof(int));
    buff_scatterM=(int **)calloc(SIZE,sizeof(int));
    for (i = 0; i < SIZE; i++)
    {
        buff_scatterA[i] = (int *)calloc(SIZE, sizeof(int));
        buff_scatterB[i] = (int *)calloc(SIZE, sizeof(int));
        buff_scatterM[i] = (int *)calloc(SIZE, sizeof(int));
    }
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            arrayA[i][j] = rand() % 100;
            arrayB[i][j] = rand() % 100;
        }
    }
    // for(i=0;i<SIZE;i++){
    //     for(j=0;j<SIZE;j++){
    //         matrix[i][j]=matrix[i][j]+array1[i][j]+array2[i][j];
    //     }
    // }

    //matrix=arrayA+arrayB
    if (rank == 0)
    {
        //数据分发
        // printf("scattering the data with rank %d, out of %d\n",rank,comm_size);
        MPI_Scatter(arrayA, length, MPI_INT, buff_scatterA, length, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(arrayB, length, MPI_INT, buff_scatterB, length, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(matrix, length, MPI_INT, buff_scatterM, length, MPI_INT, 0, MPI_COMM_WORLD);
        // printf("ok!\n");
        // MPI_Send(arrayA,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD);
        // MPI_Send(arrayB,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD);
        //MPI_Send(matrix,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD);
    }
    else
    {
        //接收数据
        printf("scattering the data by rank %d, out of %d\n",rank,comm_size);
        MPI_Scatter(arrayA, length, MPI_INT, buff_scatterA, length, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(arrayB, length, MPI_INT, buff_scatterB, length, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(matrix, length, MPI_INT, buff_scatterM, length, MPI_INT, 0, MPI_COMM_WORLD);
        // MPI_Recv(arrayA,length,MPI_INT,rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        // MPI_Recv(arrayB,length,MPI_INT,rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //MPI_Recv(matrix,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                matrix[i][j] = matrix[i][j] + arrayA[i][j] + arrayB[i][j];
            }
        }
    }
    
    if (rank == 0)
    {
        //接收数组
        printf("receiving...\n");
        // MPI_Recv(matrix,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Gather(matrix, length*SIZE, MPI_INT, buff_scatterM, length*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                printf("%d  ",matrix[i][j]);
            }
            printf("\n");
        }
        printf("ok!\n");
    }else
    {
        printf("sending...\n");
        MPI_Gather(matrix, length*SIZE, MPI_INT, buff_scatterM, length*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
        // MPI_Send(matrix,SIZE*SIZE,MPI_INT,rank,0,MPI_COMM_WORLD);
    }
    

    MPI_Finalize();
    free(buff_scatterA);
    free(buff_scatterB);
    free(buff_scatterM);
    free(arrayA);
    free(arrayB);
    free(matrix);
}