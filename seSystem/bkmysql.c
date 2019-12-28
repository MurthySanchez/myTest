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
 * 获取结果集
 * */
char **get_rows_from_mysql(MYSQL *mysql, const char *str)
{
    MYSQL_ROW row;
    search_mysql(mysql, str);
    printf("storing ...\n");
    row = mysql_fetch_row(res);
    printf("get_rows_from_mysql():ok.\n");
    return row;
}

/**
 * 将获取到的链表输出
 * 输入数据：
 * @mysql:数据库
 * @str: 搜索内容
 * @ch:不同选项代表结果输出不同类型结构体
 * 0-4:
 *          0:link_results_employee
 *          1:link_results_admin
 *          2:link_results_user
 *          3:link_results_record
 *          4:link_results_notify
 * 返回数据：@p:result_from_mysql 返回大结构体
 * */
result_from_mysql *get_results_from_mysql(MYSQL *mysql, const char *str, int ch)
{
    result_from_mysql *p;
    search_mysql(mysql, str);
    printf("storing p...\n");
    p = store_mysql(res, ch);
    printf("get_results_from_mysql():ok.\n");
    return p;
}

/**
 * 写入数据库
 * 输入参数：
 * @mysql:mysql
 * @sql: sql语句
 * */
int set_value_to_mysql(MYSQL *t_mysql, const char *sql)
{
    // MYSQL_RES *t_res; //记录集
    printf("%s\n", sql);
    if (mysql_real_query(t_mysql, sql, strlen(sql)))
    {
        printf("mysql_real_query():%s\n", mysql_error(t_mysql));
        return -1;
    }
    return 0;
}

/**
 * 保存数据库结果
 * 输入数据：
 * @res:
 * @ch:0-4:
 *          0:link_results_employee
 *          1:link_results_admin
 *          2:link_results_user
 *          3:link_results_record
 *          4:link_results_notify
 * 输出数据：
 * @p:result_from_mysql类型
 * */
result_from_mysql *store_mysql(MYSQL_RES *res, int ch)
{
    MYSQL_ROW row;
    result_from_mysql *p;
    switch (ch)
    {
    case 0:
    {
        int i;
        link_results_employee *head_e, *node_e, *tail_e;
        int iNum_rows = mysql_num_rows(res); //GET ROWS

        head_e = (link_results_employee *)malloc(sizeof(link_results_employee));
        p->r_e = head_e;
        tail_e = head_e; //tail_e->head_e

        printf("store_mysql():共%d个记录\n", iNum_rows);

        while ((row = mysql_fetch_row(res))) // 打印结果集
        {
            node_e = (link_results_employee *)malloc(sizeof(link_results_employee));
            printf("ee\n");
            node_e->id = row[0];
            node_e->name = row[1];
            node_e->sex = row[2];
            node_e->age = row[3];
            node_e->image = row[4];
            tail_e->next = node_e;
            tail_e = node_e;
        }
        tail_e->next = NULL;
        printf("\n");
        mysql_free_result(res); // 释放结果集
        return p;
    }
    case 1: //admin
    {
        link_results_admin *head_a, *node_a, *tail_a;
        int i;
        int iNum_rows = mysql_num_rows(res); //GET ROWS

        head_a = (link_results_admin *)malloc(sizeof(link_results_admin));
        p->r_a = head_a;
        tail_a = head_a; //tail_a->head_a

        printf("store_mysql():共%d个记录\n", iNum_rows);

        while ((row = mysql_fetch_row(res))) // 打印结果集
        {
            node_a = (link_results_admin *)malloc(sizeof(link_results_admin));
            printf("aa\n");
            node_a->id = row[0];
            node_a->account = row[1];
            node_a->passwd = row[2];
            node_a->state = row[3];
            tail_a->next = node_a;
            tail_a = node_a;
        }
        tail_a->next = NULL;
        printf("\n");
        mysql_free_result(res); // 释放结果集
        return p;
    }
    case 2: //user
    {
        link_results_user *head_u, *node_u, *tail_u;
        int i;
        int iNum_rows = mysql_num_rows(res); //GET ROWS

        head_u = (link_results_user *)malloc(sizeof(link_results_user));
        p->r_u = head_u;
        tail_u = head_u; //tail_u->head_u

        printf("store_mysql():共%d个记录\n", iNum_rows);

        while ((row = mysql_fetch_row(res))) // 打印结果集
        {
            node_u = (link_results_user *)malloc(sizeof(link_results_user));
            printf("uu\n");
            node_u->id = row[0];
            node_u->account = row[1];
            node_u->passwd = row[2];
            node_u->status = row[3];
            tail_u->next = node_u;
            tail_u = node_u;
        }
        tail_u->next = NULL;
        printf("\n");
        mysql_free_result(res); // 释放结果集
        return p;
    }
    case 3: //record
    {
        link_results_record *head_r, *node_r, *tail_r;
        int i;
        int iNum_rows = mysql_num_rows(res); //GET ROWS

        head_r = (link_results_record *)malloc(sizeof(link_results_record));
        p->r_r = head_r;
        tail_r = head_r; //tail_r->head_r

        printf("store_mysql():共%d个记录\n", iNum_rows);

        while ((row = mysql_fetch_row(res))) // 打印结果集
        {
            node_r = (link_results_record *)malloc(sizeof(link_results_record));
            printf("rr\n");
            node_r->id = row[0];
            node_r->online_time = row[1];
            node_r->down_time = row[2];
            tail_r->next = node_r;
            tail_r = node_r;
        }
        tail_r->next = NULL;
        printf("\n");
        mysql_free_result(res); // 释放结果集
        return p;
    }
    case 4: //notify
    {
        link_results_notify *head_n, *node_n, *tail_n;
        int i;
        int iNum_rows = mysql_num_rows(res); //GET ROWS

        head_n = (link_results_notify *)malloc(sizeof(link_results_notify));
        p->r_n = head_n;
        tail_n = head_n; //tail_n->head_n

        printf("store_mysql():共%d个记录\n", iNum_rows);

        while ((row = mysql_fetch_row(res))) // 打印结果集
        {
            node_n = (link_results_notify *)malloc(sizeof(link_results_notify));
            printf("nn\n");
            node_n->id = row[0];
            node_n->notify = row[1];
            tail_n->next = node_n;
            tail_n = node_n;
        }
        tail_n->next = NULL;
        printf("\n");
        mysql_free_result(res); // 释放结果集
        return p;
    }
    default:
        printf("something wrong in store_mysql() ");
        break;
    }
}

void display_mysql(MYSQL_RES *t_res)
{
    int iNum_rows = mysql_num_rows(g_res);     // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
}

// /**
//  * 获取数据库结果
//  * input：MYSQL *mysql, const char *pre_sql, const char *data
//  * @mysql:数据库
//  * @pre_sql:select 语句
//  * @data:查询的数据
//  * */
// const char *get_inform_form_mysql(MYSQL *mysql, const char *pre_sql, const char *data)
// {
//     // MYSQL_RES *res; //记录集
//     const char *result;
//     char *sql;
//     MYSQL_ROW row;
//     int i;
//     int iNum_rows = mysql_num_rows(res); //GET ROW
//     printf("pre_sql:%s,data:%s\n", pre_sql, data);
//     if (data != NULL)
//     {
//         sprintf(sql, "%s'%s'", pre_sql, data);
//     }
//     else
//     {
//         sprintf(sql, "%s", pre_sql);
//     }
//     printf("%s", sql);
//     mysql_query(mysql, sql);
//     if (!(mysql_real_query(mysql, sql, strlen(sql))))
//     { //sql语句错误
//         printf("mysql_real_query():%s\n", mysql_error(mysql));
//         return "-1"; //failed
//     }
//     else
//     {
//         res = mysql_store_result(mysql);
//         if (!(i = mysql_num_rows(res)))
//         { //无搜索结果
//             printf("cannot find any answer!\n");
//             return "-1";
//         }
//     }

//     while ((row = mysql_fetch_row(res))) // 打印结果集
//     {
//         result = row[0];
//     }
//     printf("\n");
//     mysql_free_result(res); // 释放结果集
//     return result;
// }

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