#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mymysql.h"
#include "config.h"

#define MAX_BUF_SIZE 1024 //缓冲区最大字节数

// MYSQL_RES *g_res; //记录集
// MYSQL_ROW *g_row; //字符串数组，记录行

/**
 * 显示数据库结果
 * input：MYSQL_RES res
 * */
void display_mysql(MYSQL_RES *res){
    MYSQL_ROW row;
    int i;
    int iNum_rows=mysql_num_rows(res);//GET ROWS
    int iNum_fields=mysql_num_fields(res);//GET FIELDS

    printf("共%d个记录，每个记录%d字段\n", iNum_rows, iNum_fields);  

    while ((row=mysql_fetch_row(res))) // 打印结果集  
        for(i = 0; i < iNum_fields; i++)         
            printf("%s\t", row[i]);              //输出  
    printf("\n");
    mysql_free_result(res); // 释放结果集
}

/**
 * 查询数据库
 * 输入参数：数据库，查询语句
 * 输出：0成功
 * */
 int search_mysql(MYSQL* mysql,const char* str)
{
    int row;
    //search in the database 
    printf("%s\n",str);
    mysql_query(mysql,str);
    if(!(mysql_real_query(mysql, str, strlen(str)))){
        printf("mysql_real_query():%s\n",mysql_error(mysql));
        return  -1;//failed
    }else
    {
        if(!(row=mysql_num_rows(mysql_store_result(mysql)))){
            printf("cannot find any answer!\n");
            return -1;
        }           
    }

    return 0;

    // //give the result to g_res
    // g_res=mysql_use_result(mysql);
    // if(g_res)
    // {
    //     printf("We've gotten %lu rows\n",(unsigned long)mysql_num_rows(g_res));
    //     while((g_row=mysql_fetch_row(g_res)))
    //     {
    //         printf("Fetched data\n");
    //         display_row(mysql,g_row);
    //     }
    // }
    // else
    // {
    //     printf("%s\n",mysql_error(mysql));//返回错误消息
    //     return -1;
    // }
}

/**
 * 连接mysql
 * */
int connect_mysql(MYSQL* mysql)
{
    //尝试与运行在主机上的MySQL数据库引擎建立连接
    if (NULL == mysql_real_connect(mysql,
                                   HOST,
                                   USER,
                                   PASSWD,
                                   DB,
                                   0,
                                   NULL,
                                   0))
    {
        printf("mysql_real_connect(): %s\n", mysql_error(mysql));
        return -1;
    }

    return 0;
}

/**
 * close the mysql
 * */
int close_mysql(MYSQL* mysql)
{
    mysql_close(mysql);
    return 0;
}
