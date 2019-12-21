#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
#include<omp.h>
#define size 1024
#define NUM_THREADS 4
void main(int *argc ,char *argv[] )
{
	int *A,*B,*C,*buff_A,*buff_B,*temp_ans,*local,*temp_local,*max;
	int i,j,k,l,*temp,line;
	int rank;
    	int size_num;
	omp_set_num_threads(NUM_THREADS);  //设置4线程
    	
	MPI_Init(0,0);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	MPI_Comm_size(MPI_COMM_WORLD, &size_num);
	line = size/size_num;
	A = (int*)malloc(sizeof(int)*size*size);
    	B = (int*)malloc(sizeof(int)*size*size);
    	C = (int*)malloc(sizeof(int)*size*size);
	buff_A = (int*)malloc(sizeof(int)*size*line);
	buff_B = (int*)malloc(sizeof(int)*size*line);
	temp_ans = (int*)malloc(sizeof(int)*size*line);
	temp_local = (int*)malloc(sizeof(int)*2);
	local = (int*)malloc(sizeof(int)*2);
	max = (int*)malloc(sizeof(int)*1);
	temp = (int*)malloc(sizeof(int)*1);

	if(rank==0){
		for(i=0;i<size;i++)
			for(j=0;j<size;j++)
			{
				A[i*size+j]=rand()%100;
				B[i*size+j]=rand()%100;
			}
		for (i=1;i<size_num;i++)
        	{
                	MPI_Send(B+(i-1)*line*size,size*line,MPI_INT,i,0,MPI_COMM_WORLD);
        	}
		for (l=1; l<size_num; l++)
        	{
            		MPI_Send(A+(l-1)*line*size,size*line,MPI_INT,l,1, MPI_COMM_WORLD);
        	}
		//接收从进程计算的结果
        	for (k=1;k<size_num;k++)
        	{
            		MPI_Recv(temp_ans,line*size,MPI_INT,k,3,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            		MPI_Recv(temp,1,MPI_INT,k,4,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(temp_local,2,MPI_INT,k,5,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(k==1){
				max[0]=temp[0];
				local[0]=temp_local[0]+(k-1)*line;
				local[1]=temp_local[1];			
			}
			else{
				if(temp[0]>max[0]){
					max[0]=temp[0];
					local[0]=temp_local[0]+(k-1)*line;
					local[1]=temp_local[1];	
				}
			}
			//将结果传递给数组c
            		for (i=0;i<line;i++)
           		{
                		for (j=0;j<size;j++)
                		{
                    			C[((k-1)*line+i)*size+j] = temp_ans[i*size+j];
                		}
            		}
        	}
		//计算a剩下的数据
		#pragma omp parallel for private(i,j)
        	for (i=(size_num-1)*line;i<size;i++)
        	{
            		for (j=0;j<size;j++)
            		{
                    		C[i*size+j] = A[i*size+j]+B[i*size+j];
                		 
            		}
        	}
		
		for(i=(size_num-1)*line+1;i<line-1;i++)
		{
			for(j=1;j<size-1;j++)
			{
				temp[0]=(C[i*size+j]-C[(i-1)*size+(j-1)])+(C[i*size+j]-C[(i-1)*size+j])+(C[i*size+j]-C[(i-1)*size+(j+1)])+(C[i*size+j]-C[i*size+(j-1)])+(C[i*size+j]-C[i*size+(j+1)])+(C[i*size+j]-C[(i+1)*size+(j-1)])+(C[i*size+j]-C[(i+1)*size+j])+(C[i*size+j]-C[(i+1)*size+(j+1)]);
				if(temp[0]>max[0]){
					max[0]=temp[0];
					local[0]=i;
					local[1]=j;
				}
			}
		}		
		for(i=0;i<size;i++){
                	for(j=0;j<size;j++)
                	{       
				printf("%d ",A[i*size+j]);
                	}
			printf("\n");
		}printf("....\n");
		for(i=0;i<size;i++){
                	for(j=0;j<size;j++)
                	{       
				printf("%d ",B[i*size+j]);
                	}
			printf("\n");
		}printf("....\n");
		for(i=0;i<size;i++){
                	for(j=0;j<size;j++)
                	{       
				printf("%d ",C[i*size+j]);
                	}
			printf("\n");
		}
		printf("最凸点：(%d,%d)\n",local[0],local[1]);
		free(A);
        	free(B);
        	free(C);
        	free(buff_A);
		free(buff_B);
        	free(temp_ans);
		free(local);
		free(temp_local);
		free(max);
		free(temp);
	}
	else{
		//接收广播的数据
        	MPI_Recv(buff_B,size*line,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	MPI_Recv(buff_A,size*line,MPI_INT,0,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	//计算乘积结果，并将结果发送给主进程
		#pragma omp parallel for private(i,j)
        	for (i=0;i<line;i++)
        	{
            		for (j=0;j<size;j++)
            		{                		
                    		temp_ans[i*size+j] = buff_A[i*size+j]+buff_B[i*size+j];
           		 }
       		}
		for(i=1;i<line-1;i++)
		{
			for(j=1;j<size-1;j++)
			{
				temp[0]=(temp_ans[i*size+j]-temp_ans[(i-1)*size+(j-1)])+(temp_ans[i*size+j]-temp_ans[(i-1)*size+j])+(temp_ans[i*size+j]-temp_ans[(i-1)*size+(j+1)])+(temp_ans[i*size+j]-temp_ans[i*size+(j-1)])+(temp_ans[i*size+j]-temp_ans[i*size+(j+1)])+(temp_ans[i*size+j]-temp_ans[(i+1)*size+(j-1)])+(temp_ans[i*size+j]-temp_ans[(i+1)*size+j])+(temp_ans[i*size+j]-temp_ans[(i+1)*size+(j+1)]);
				if(i==1&&j==1){
					max[0]=temp[0];
					local[0]=i;
					local[1]=j;
				}
				else{
					if(temp[0]>max[0]){
						max[0]=temp[0];
						local[0]=i;
						local[1]=j;
					}
				}
			}
		}
        //将计算结果传送给主进程
        MPI_Send(temp_ans,line*size,MPI_INT,0,3,MPI_COMM_WORLD);
		MPI_Send(max,1,MPI_INT,0,4,MPI_COMM_WORLD);
		MPI_Send(local,2,MPI_INT,0,5,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}