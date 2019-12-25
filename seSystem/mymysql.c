#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mymysql.h"
#include "config.h"

#define MAX_BUF_SIZE 1024 //缓冲区最大字节数

MYSQL_RES *res; //记录集
// MYSQL_ROW *g_row; //字符串数组，记录行

/**
 * 显示数据库结果
 * input：MYSQL_RES res
 * */
void display_mysql(MYSQL_RES *res)
{
    MYSQL_ROW row;
    // link_mysql_results *head, *node, *end;
    int i;
    int iNum_rows = mysql_num_rows(res);     //GET ROWS
    int iNum_fields = mysql_num_fields(res); //GET FIELDS

    // head = (link_mysql_results *)malloc(sizeof(link_mysql_results));
    // end = head; //end->head

    printf("共%d个记录\n", iNum_rows);

    while ((row = mysql_fetch_row(res)))// 打印结果集
    { 
        for (i = 0; i < iNum_fields; i++)
        {
            // node = (link_mysql_results *)malloc(sizeof(link_mysql_results));
            // node->result = row[i];
            printf("%s\t", row[i]); //输出
            // printf("2.%s\t", node->result);
            // end->next = node;
            // end = node;
        }
        // end->next = NULL;
        printf("\n");
    }

    printf("\n");
    mysql_free_result(res); // 释放结果集
}

/**
 * 查询数据库
 * 输入参数：数据库，查询语句
 * 输出：0成功
 * */
int search_mysql(MYSQL *mysql, const char *str)
{
    // MYSQL_RES *res;
    int row;
    //search in the database
    printf("%s\n", str);
    mysql_query(mysql, str);
    if (!(mysql_real_query(mysql, str, strlen(str))))
    { //sql语句错误
        printf("mysql_real_query():%s\n", mysql_error(mysql));
        return -1; //failed
    }
    else
    {
        res = mysql_store_result(mysql);
        if (!(row = mysql_num_rows(res)))
        { //无搜索结果
            printf("cannot find any answer!\n");
            return -1;
        }
    }
    // display_mysql(res); //correct
    // display_mysql(mysql_store_result(mysql));    //段错误 (核心已转储)

    return 0;
}

/**
 * 连接mysql
 * */
int connect_mysql(MYSQL *mysql)
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
int close_mysql(MYSQL *mysql)
{
    mysql_close(mysql);
    return 0;
}
