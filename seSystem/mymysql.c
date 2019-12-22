#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mymysql.h"
#include "config.h"

#define MAX_BUF_SIZE 1024 //缓冲区最大字节数

MYSQL mysql; //连接
// MYSQL_RES *g_res; //记录集
// MYSQL_ROW *g_row; //字符串数组，记录行

/**
 * 执行数据库
 * */
int executsql(const char *sql)
{
    if (mysql_real_query(&mysql, sql, strlen(sql)))
        return -1; //failed
    return 0;      //success
}

/**
 * 连接mysql
 * */
int connect_mysql()
{
    if (NULL == mysql_init(&mysql))
    { //分配和初始化MYSQL对象
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    //尝试与运行在主机上的MySQL数据库引擎建立连接
    if (NULL == mysql_real_connect(&mysql,
                                   HOST,
                                   USER,
                                   PASSWD,
                                   DB,
                                   0,
                                   NULL,
                                   0))
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }

    return 0;
}

/**
 * close the mysql
 * */
int close_mysql()
{
    mysql_close(&mysql);
    return 0;
}

int main()
{
    if(!connect_mysql())
        printf("Connected MySQL successful! \n");
    mysql_close(&mysql);
    return 0;
}