#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <mysql/mysql.h>
#include "mymysql.h"
#include "config.h"

#define MAX_BUF_SIZE 1024 //缓冲区最大字节数

MYSQL_RES *res; //记录集

// MYSQL_ROW *g_row; //字符串数组，记录行

result_from_mysql *p;

/**
 * 保存数据库结果
 * input：MYSQL_RES res
 * */
result_from_mysql *display_mysql(MYSQL_RES *res)
{
    MYSQL_ROW row;
    link_results_employee *head, *node, *tail;
    int i;
    result_from_mysql *p;
    int iNum_rows = mysql_num_rows(res);     //GET ROWS
    int iNum_fields = mysql_num_fields(res); //GET FIELDS

    head = (link_results_employee *)malloc(sizeof(link_results_employee));
    p->r_e = head;
    tail = head; //tail->head

    printf("display_mysql():共%d个记录\n", iNum_rows);

    while ((row = mysql_fetch_row(res))) // 打印结果集
    {
        // for (i = 0; i < iNum_fields; i++)
        // {
        node = (link_results_employee *)malloc(sizeof(link_results_employee));
        //     node->result = row[i];
        //     printf("%s\t", row[i]); //输出
        //     // printf("2.%s\t", node->result);
        //     tail->next = node;
        //     tail = node;
        // }
        printf("kk\n");
        node->id = row[0];
        node->name = row[1];
        node->sex = row[2];
        node->age = row[3];
        node->image = row[4];
        tail->next = node;
        tail = node;
    }
    tail->next = NULL;
    printf("\n");
    // while (head->next != NULL)
    // {
    //     head = head->next;
    //     printf("%s\t", head->result);
    // }
    printf("\n");
    mysql_free_result(res); // 释放结果集
    return p;
}

result_from_mysql *get_results_from_mysql(MYSQL *mysql, const char *str)
{
    result_from_mysql *p;
    search_mysql(mysql, str);
    p = display_mysql(res);
    printf("get_results_from_mysql() as follow.\n");

    return p;
}

// /**
//  * 获取数据库结果
//  * input：MYSQL_RES res
//  * */
// const char *output_singal_mysql_result(MYSQL_RES *res)
// {
//     // MYSQL_RES *res; //记录集
//     // const char *result;
//     MYSQL_ROW row;
//     int i;
//     int iNum_rows = mysql_num_rows(res);     //GET ROWS
//     int iNum_fields = mysql_num_fields(res); //GET FIELDS

//     printf("共%d个记录\n", iNum_rows);

//     while ((row = mysql_fetch_row(res))) // 打印结果集
//     {
//         for (i = 0; i < iNum_fields; i++)
//         {
//             result = row[i];
//         }
//         printf("\n");
//     }
//     printf("\n");
//     mysql_free_result(res); // 释放结果集
//     return result;
// }

/**
 * 获取数据库结果
 * input：MYSQL *mysql, const char *pre_sql, const char *data
 * @mysql:数据库
 * @pre_sql:select 语句
 * @data:查询的数据
 * */
const char *get_inform_form_mysql(MYSQL *mysql, const char *pre_sql, const char *data)
{
    // MYSQL_RES *res; //记录集
    const char *result;
    char *sql;
    MYSQL_ROW row;
    int i;
    int iNum_rows = mysql_num_rows(res);     //GET ROWS
    int iNum_fields = mysql_num_fields(res); //GET FIELDS
    printf("pre_sql:%s,data:%s\n", pre_sql, data);
    if (data != NULL)
    {
        sprintf(sql, "%s'%s'", pre_sql, data);
    }
    else
    {
        sprintf(sql, pre_sql);
    }
    printf("%s", sql);
    mysql_query(mysql, sql);
    if (!(mysql_real_query(mysql, sql, strlen(sql))))
    { //sql语句错误
        printf("mysql_real_query():%s\n", mysql_error(mysql));
        return "-1"; //failed
    }
    else
    {
        res = mysql_store_result(mysql);
        if (!(row = mysql_num_rows(res)))
        { //无搜索结果
            printf("cannot find any answer!\n");
            return "-1";
        }
    }

    while ((row = mysql_fetch_row(res))) // 打印结果集
    {
        result = row[0];
    }
    printf("\n");
    mysql_free_result(res); // 释放结果集
    return result;
}

/**
 * 查询数据库
 * 输入参数：数据库，查询语句
 * 输出：0成功
 * */
int search_mysql(MYSQL *mysql, const char *str)
{
    // MYSQL_RES *res;
    // MYSQL_RES *res; //记录集
    // link_mysql_results *p;
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
    // p = display_mysql(res); //correct
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
