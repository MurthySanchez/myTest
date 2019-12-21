#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

const int maxn = 10;

//计算x,y两个数组对应位的和，存入第三个数组z
bool Parallel_vector_sum(
    double local_x[], //加数组
    double local_y[], //被加数组
    double local_z[], //存储和的数组
    int local_n       //加的个数
)
{
    for (int local_i = 0; local_i < local_n; local_i++)
    {
        local_z[local_i] = local_x[local_i] + local_y[local_i];
    }
    return true;
}

//从键盘读取数组
bool Read_vector(
    double local_a[], //存储数据的数组，OUT
    int local_n,      //每个进程需要分配的数量
    int n,            //读取的总个数
    string vec_name,  //数组的名字
    int my_rank,      //进程号
    MPI_Comm comm     //通信子
)
{
    double *a = NULL;

    if (my_rank == 0)
    {
        //输入数组
        a = new double[n];
        cout << "Enter the vector " << vec_name << endl;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        //数据分发
        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE, 0, comm);

        delete[] a;
    }
    else
    {
        //接收数据
        MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n, MPI_DOUBLE, 0, comm);
    }
    return true;
}

bool Print_vector(
    double local_b[], //需要输出的数组
    int local_n,      //每个进程需要输出的数量
    int n,            //总数量
    string title,     //数组的名字
    int my_rank,      //进程号
    MPI_Comm comm     //通信子
)
{
    double *b = NULL;

    if (my_rank == 0)
    {
        //接收数组
        b = new double[n];
        MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);

        //打印数组
        cout << title << endl;
        for (int i = 0; i < n; i++)
        {
            cout << b[i] << " ";
        }
        cout << endl;
        delete[] b;
    }
    else
    {
        //发送数组
        MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
    }
    return true;
}

int main(void)
{
    int my_rank = 0;
    int comm_sz = 0;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    streambuf *inbuf = cin.rdbuf((new ifstream("input"))->rdbuf()); //重定向，OJ时将它注释掉

    int local_n = maxn / comm_sz;
    double local_a[maxn], local_b[maxn], local_c[maxn];

    //读取待相加的两个数组
    Read_vector(local_a, local_n, maxn, "arryA", my_rank, MPI_COMM_WORLD);
    Read_vector(local_b, local_n, maxn, "arryB", my_rank, MPI_COMM_WORLD);

    //计算对应的和
    Parallel_vector_sum(local_a, local_b, local_c, local_n);

    //打印结果数组
    Print_vector(local_c, local_n, maxn, "arry", my_rank, MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
