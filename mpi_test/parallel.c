#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
#include "mpich/mpi.h"

#define SIZE 8
#define DEFAULT_OMP_NUM 4

/*****
 * rules:
 *      tag:
 *              701:rank 0 recvice array B from buf_B in other rank(including rank 0)
 *              702:rank 0 recvice array A from buf_A in other rank(including rank 0)
 *              703:rank 0 send array A's line to buf_A in other rank
 *              704:rank 0 send array B's row to buf_B in other rank
 *              705:rank 0 receive arrayC
 * ****/

int main(int argc, char *argv[])
{
    int i, j, k, n, temp;
    int local[2]; //规定local[0]=num, local[1]=x, local[2]=y
    int *A, *B, *C, *buf_A, *buf_B, *buf_key;
    double start, end;
    //init MPI environment
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /*获取当前正在运行进程的标识号*/
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /*获取所有参与运算的进程个数*/

    omp_set_num_threads(DEFAULT_OMP_NUM); //设置4线程
    int buff_size = SIZE / comm_size;

    //init array && buff
    A = (int *)malloc(sizeof(int *) * SIZE * SIZE);
    B = (int *)malloc(sizeof(int *) * SIZE * SIZE);
    C = (int *)malloc(sizeof(int *) * SIZE * SIZE);
    buf_A = (int *)malloc(sizeof(int *) * SIZE * buff_size);
    buf_B = (int *)malloc(sizeof(int *) * SIZE * buff_size);
    buf_key = (int *)malloc(sizeof(int *) * SIZE * SIZE);
    if (rank == 0)
    {
        /*Part One create array A,B*/
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < buff_size; j++)
            {
                buf_A[i * buff_size + j] = rand() % 100;
                buf_B[i * buff_size + j] = rand() % 100;
            }
        }
        //put rank 0's key to the main host
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < buff_size; j++)
            {
                A[i * SIZE + j] = buf_A[i * buff_size + j];
                B[i * SIZE + j] = buf_B[i * buff_size + j];
            }
        }

        for (int n = 1; n < comm_size; n++)
        {
            MPI_Recv(buf_A, buff_size * SIZE, MPI_INT, n, 702, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buf_B, buff_size * SIZE, MPI_INT, n, 701, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (i = 0; i < SIZE; i++)
            {
                for (j = 0; j < buff_size; j++)
                {
                    A[i * SIZE + n * buff_size + j] = buf_A[i * buff_size + j];
                    B[i * SIZE + n * buff_size + j] = buf_B[i * buff_size + j];
                }
            }
        }

        /*Part Two calculate C=A*B*/

        //send message to rank i
        for (i = 1; i < comm_size; i++)
        {
            MPI_Send(A + (i - 1) * buff_size * SIZE, SIZE * buff_size, MPI_INT, i, 703, MPI_COMM_WORLD);
            MPI_Send(B, SIZE * SIZE, MPI_INT, i, 704, MPI_COMM_WORLD);
        }
        //put buf_key in C
        for (n = 1; n < comm_size; n++)
        {
            MPI_Recv(buf_key, buff_size * SIZE, MPI_FLOAT, n, 705, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int i = 0; i < buff_size; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    C[((n - 1) * buff_size + i) * SIZE + j] = buf_key[i * SIZE + j];
                }
            }
        }
        //rank 0 calculator
        for (int i = (comm_size - 1) * buff_size; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                float temp = 0.0;
                for (int k = 0; k < SIZE; k++)
                    temp += A[i * SIZE + k] * B[k * SIZE + j];
                C[i * SIZE + j] = temp;
            }
        }

        /*Part Three find out the bump*/
        local[0] = -1; //set the initation MaxNum is -1
        for (i = 1; i < SIZE - 1; i++)
        {
            for (j = 1; j < SIZE - 1; j++)
            {
                temp = (C[i * SIZE + j] - C[(i - 1) * SIZE + j - 1]) + (C[i * SIZE + j] - C[(i - 1) * SIZE + j]) + (C[i * SIZE + j] - C[(i - 1) * SIZE + j + 1]) + (C[i * SIZE + j] - C[i * SIZE + j - 1]) + (C[i * SIZE + j] - C[i * SIZE + j]) + (C[i * SIZE + j] - C[i * SIZE + j + 1]) + (C[i * SIZE + j] - C[(i + 1) * SIZE + j - 1]) + (C[i * SIZE + j] - C[(i + 1) * SIZE + j]) + (C[i * SIZE + j] - C[(i + 1) * SIZE + j + 1]);
                if (temp > local[0])
                {
                    local[0] = temp;
                    local[1] = i;
                    local[2] = j;
                }
            }
        }
        /** output
        //输出 A
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                printf("%-5d", A[i * SIZE + j]);
            }
            printf("\n");
        }
        printf("-----------------\n");
        //output B
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                printf("%-5d", B[i * SIZE + j]);
            }
            printf("\n");
        }
        printf("-----------------\n");
        //output C
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                printf("%d  ", C[i * SIZE + j]);
            }
            printf("\n");
        }
        **/
        //output bump
        printf("凸点值为%d(%d,%d)\n", local[0], local[1]+1, local[2]+1);
        printf("证明：\n");
        printf("%d %d %d\n%d %d %d\n%d %d %d\n",C[(local[1]-1)*SIZE+local[2]-1],C[(local[1]-1)*SIZE+local[2]],C[(local[1]-1)*SIZE+local[2]+1],
                                            C[(local[1])*SIZE+local[2]-1],C[local[1]*SIZE+local[2]],C[local[1]*SIZE+local[2]+1],
                                            C[(local[1]+1)*SIZE+local[2]-1],C[(local[1]+1)*SIZE+local[2]],C[(local[1]+1)*SIZE+local[2]+1]);
                
        free(buf_A);
        free(buf_B);
        free(buf_key);
        free(A);
        free(B);
        free(C);
    }
    else
    {
#pragma omp parallel for private(i, j)
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < buff_size; j++)
            {
                buf_A[i * buff_size + j] = rand() % 100;
                buf_B[i * buff_size + j] = rand() % 100;
            }
        }

        MPI_Send(buf_A, buff_size * SIZE, MPI_INT, 0, 702, MPI_COMM_WORLD);
        MPI_Send(buf_B, buff_size * SIZE, MPI_INT, 0, 701, MPI_COMM_WORLD);

        //calculate C=A*B
        MPI_Recv(buf_A, SIZE * buff_size, MPI_INT, 0, 703, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B, SIZE * SIZE, MPI_INT, 0, 704, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

#pragma omp parallel for private(i, j, k)
        for (i = 0; i < buff_size; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                float tmp = 0.0;
                for (k = 0; k < SIZE; k++)
                {
                    tmp += buf_A[i * SIZE + k] * B[j * SIZE + j];
                    buf_key[i * SIZE + j] = tmp;
                }
            }
        }
        MPI_Send(buf_key, buff_size * SIZE, MPI_FLOAT, 0, 705, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}