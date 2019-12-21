#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"

#define SIZE 16
#define SQUARE 3
#define MALLOC(type,n) (type *)malloc((n)*sizeof(type))

int main(int argc, char *argv[]){
    int i,j,temp=0,MaxNum=-1,location[1];
    double start,end;
    //创建两个随机二维数组
    int **array1,**array2,**matrix;
    array1=MALLOC(int *, SIZE);
    array2=MALLOC(int *, SIZE);
    matrix=MALLOC(int *, SIZE);
    srand((unsigned)time(NULL));
    for(i=0;i<SIZE;i++){
        array1[i]=MALLOC(int, SIZE);
        array2[i]=MALLOC(int, SIZE);
        matrix[i]=MALLOC(int, SIZE);
        for(j=0;j<SIZE;j++){
            array1[i][j]=rand()%100;
            array2[i][j]=rand()%100;
            matrix[i][j]=0;
        }   
    }

    // for(i=0;i<SIZE;i++){
    //     for(j=0;j<SIZE;j++)
    //         printf("%d\t",array1[i][j]);
    //     printf("\n");
    // }

    //（串行）计算matrix=array1+array2
    start=omp_get_wtime();
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            matrix[i][j]=matrix[i][j]+array1[i][j]+array2[i][j];
        }
    }
    end=omp_get_wtime();
    printf("串行矩阵相加运行时间为%f\n",end-start);

    start=omp_get_wtime();
    //寻找凸点
    for(i=1;i<SIZE-1;i++){
        for(j=1;j<SIZE-1;j++){
            temp=(matrix[i][j]-matrix[i-1][j-1])+(matrix[i][j]-matrix[i-1][j])+(matrix[i][j]-matrix[i-1][j+1])
                +(matrix[i][j]-matrix[i][j-1])+(matrix[i][j]-matrix[i][j])+(matrix[i][j]-matrix[i][j+1])
                +(matrix[i][j]-matrix[i+1][j-1])+(matrix[i][j]-matrix[i+1][j])+(matrix[i][j]-matrix[i+1][j+1]);
            if(temp>MaxNum){
                MaxNum=temp;
                location[0]=i;
                location[1]=j;
            }
        }
    }
    end=omp_get_wtime();
    printf("串行计算凸点运行时间为%f\n",end-start);

    //打印数组
    // for(i=0;i<SIZE;i++){
    //     for(j=0;j<SIZE;j++){
    //         printf("%d  ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    //打印凸点
    printf("凸点值为:%d，坐标（%d，%d），坐标值为：%d\n",MaxNum,location[0]+1,location[1]+1,matrix[location[0]][location[1]]);
    //printf("证明：\n");
    // printf("%d %d %d\n%d %d %d\n%d %d %d\n",matrix[location[0]-1][location[1]-1],matrix[location[0]-1][location[1]],matrix[location[0]-1][location[1]+1],
                                            // matrix[location[0]][location[1]-1],matrix[location[0]][location[1]],matrix[location[0]][location[1]+1],
                                            // matrix[location[0]+1][location[1]-1],matrix[location[0]+1][location[1]],matrix[location[0]+1][location[1]+1]);
                
    free(array1);
    free(array2);
    free(matrix);        
    return 0;
}