
#ifndef MY_MYSQL_H_
#define MY_MYSQL_H_

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdarg.h>
#include "config.h"

/*admin结果集*/
typedef struct results_admin
{
    char *id;
    char *account;
    char *passwd;
    char *state;
    struct results_admin *next;
} link_results_admin;

/*employee结果集*/
typedef struct results_employee
{
    char *id;   //编号
    char *name; //名字
    char *sex;  //性别
    char *age;  //年龄
    char *image;    //照片地址
    struct results_employee *next;
} link_results_employee;

/*user结果集*/
typedef struct results_user
{
    char *id;
    char *passwd;
    char *status;
    struct results_user *next;
} link_results_user;

/*record结果集*/
typedef struct results_record
{
    char *record_id;
    char *id;
    char *online_time;
    char *down_time;
    struct results_record *next;
} link_results_record;

/*notify结果集*/
typedef struct results_notify
{
    char *id;
    char *notify;
    char *notify_time;
    struct results_notify *next;
} link_results_notify;

typedef struct results
{
    link_results_admin *r_a;
    link_results_employee *r_e;
    link_results_user *r_u;
    link_results_record *r_r;
    link_results_notify *r_n;
} result_from_mysql;

char **get_rows_from_mysql(MYSQL *mysql, const char *str);
void display_mysql(MYSQL_RES *t_res);
result_from_mysql *store_mysql(MYSQL_RES *res, int ch);
result_from_mysql *get_results_from_mysql(MYSQL *mysql, const char *str, int ch);
int get_row_number_from_mysql(MYSQL *mysql, const char *str);
int search_mysql(MYSQL *mysql, const char *str);
int insert_to_mysql(MYSQL *mysql, const char *sql);
int connect_mysql(MYSQL *mysql);
int close_mysql(MYSQL *mysql);

#endif