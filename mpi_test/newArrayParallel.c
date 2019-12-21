#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
#include "mpi.h"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

int main(int argc, char *argv[])----------------------------------------------------
{
    int i, j, k, l;
    double start, end;
    int *arrayA, *arrayB, *matrix, *buff_scatterA, *buff_scatterB, *buff_scatterM, *local, *temp_local, *max,*temp;

    //init MPI environment
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /*获取当前正在运行进程的标识号*/
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /*获取所有参与运算的进程个数*/

    //each process need to do
    int length = SIZE / comm_size;
    //init arrays
    arrayA = (int *)malloc(sizeof(int) * SIZE * SIZE);
    arrayB = (int *)malloc(sizeof(int) * SIZE * SIZE);
    matrix = (int *)malloc(sizeof(int) * SIZE * SIZE);
    buff_scatterA = (int *)malloc(sizeof(int) * SIZE * length);
    buff_scatterB = (int *)malloc(sizeof(int) * SIZE * length);
    buff_scatterM = (int *)malloc(sizeof(int) * SIZE * length);
    temp_local = (int *)malloc(sizeof(int) * 2);
    local = (int *)malloc(sizeof(int) * 2);
    max = (int *)malloc(sizeof(int) * 1);
    temp = (int *)malloc(sizeof(int) * 1);

    if (rank == 0)
    {
        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
            {
                arrayA[i * SIZE + j] = rand() % 100;
                arrayB[i * SIZE + j] = rand() % 100;
            }
        for (i = 1; i < comm_size; i++)
        {
            MPI_Send(arrayB + (i - 1) * length * SIZE, SIZE * length, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for (l = 1; l < comm_size; l++)
        {
            MPI_Send(arrayA + (l - 1) * length * SIZE, SIZE * length, MPI_INT, l, 1, MPI_COMM_WORLD);
        }
        //接收从进程计算的结果
        for (k = 1; k < comm_size; k++)
        {
            MPI_Recv(buff_scatterM, length * SIZE, MPI_INT, k, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(temp, 1, MPI_INT, k, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(temp_local, 2, MPI_INT, k, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (k == 1)
            {
                max[0] = temp[0];
                local[0] = temp_local[0] + (k - 1) * length;
                local[1] = temp_local[1];
            }
            else
            {
                if (temp[0] > max[0])
                {
                    max[0] = temp[0];
                    local[0] = temp_local[0] + (k - 1) * length;
                    local[1] = temp_local[1];
                }
            }
            //将结果传递给数组c
            for (i = 0; i < length; i++)
            {
                for (j = 0; j < SIZE; j++)
                {
                    matrix[((k - 1) * length + i) * SIZE + j] = buff_scatterM[i * SIZE + j];
                }
            }
        }
//计算a剩下的数据
#pragma omp parallel for private(i, j)
        for (i = (comm_size - 1) * length; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                matrix[i * SIZE + j] = arrayA[i * SIZE + j] + arrayB[i * SIZE + j];
            }
        }
        for (i = (comm_size - 1) * length + 1; i < length - 1; i++)
        {
            for (j = 1; j < SIZE - 1; j++)
            {
                temp[0] = (matrix[i * SIZE + j] - matrix[(i - 1) * SIZE + (j - 1)]) + (matrix[i * SIZE + j] - matrix[(i - 1) * SIZE + j]) + (matrix[i * SIZE + j] - matrix[(i - 1) * SIZE + (j + 1)]) + (matrix[i * SIZE + j] - matrix[i * SIZE + (j - 1)]) + (matrix[i * SIZE + j] - matrix[i * SIZE + (j + 1)]) + (matrix[i * SIZE + j] - matrix[(i + 1) * SIZE + (j - 1)]) + (matrix[i * SIZE + j] - matrix[(i + 1) * SIZE + j]) + (matrix[i * SIZE + j] - matrix[(i + 1) * SIZE + (j + 1)]);
                if (temp[0] > max[0])
                {
                    max[0] = temp[0];
                    local[0] = i;
                    local[1] = j;
                }
            }
        }
        // for (i = 0; i < SIZE; i++)
        // {
        //     for (j = 0; j < SIZE; j++)
        //     {
        //         printf("%d ", arrayA[i * SIZE + j]);
        //     }
        //     printf("\n");
        // }
        // printf("....\n");
        // for (i = 0; i < SIZE; i++)
        // {
        //     for (j = 0; j < SIZE; j++)
        //     {
        //         printf("%d ", arrayB[i * SIZE + j]);
        //     }
        //     printf("\n");
        // }
        // printf("....\n");
        // for (i = 0; i < SIZE; i++)
        // {
        //     for (j = 0; j < SIZE; j++)
        //     {
        //         printf("%d ", matrix[i * SIZE + j]);
        //     }
        //     printf("\n");
        // }
        printf("最凸点：(%d,%d)\n", local[0], local[1]);
        free(arrayA);
        free(arrayB);
        free(matrix);
        free(buff_scatterA);
        free(buff_scatterB);
        free(buff_scatterM);
        free(local);
        free(temp_local);
        free(max);
        free(temp);
    }
    else
    {
        //接收广播的数据
        MPI_Recv(buff_scatterB, SIZE * length, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(buff_scatterA, SIZE * length, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //计算乘积结果，并将结果发送给主进程
#pragma omp parallel for private(i, j)
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                buff_scatterM[i * SIZE + j] = buff_scatterA[i * SIZE + j] + buff_scatterB[i * SIZE + j];
            }
        }
        for (i = 1; i < length - 1; i++)
        {
            for (j = 1; j < SIZE - 1; j++)
            {
                temp[0] = (buff_scatterM[i * SIZE + j] - buff_scatterM[(i - 1) * SIZE + (j - 1)]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[(i - 1) * SIZE + j]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[(i - 1) * SIZE + (j + 1)]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[i * SIZE + (j - 1)]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[i * SIZE + (j + 1)]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[(i + 1) * SIZE + (j - 1)]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[(i + 1) * SIZE + j]) + (buff_scatterM[i * SIZE + j] - buff_scatterM[(i + 1) * SIZE + (j + 1)]);
                if (i == 1 && j == 1)
                {
                    max[0] = temp[0];
                    local[0] = i;
                    local[1] = j;
                }
                else
                {
                    if (temp[0] > max[0])
                    {
                        max[0] = temp[0];
                        local[0] = i;
                        local[1] = j;
                    }
                }
            }
        }
        //将计算结果传送给主进程
        MPI_Send(buff_scatterM, length * SIZE, MPI_INT, 0, 3, MPI_COMM_WORLD);
        MPI_Send(max, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
        MPI_Send(local, 2, MPI_INT, 0, 5, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}