
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
    int *id;
    char *account;
    char *passwd;
    char *state;
    struct results_admin *next;
} link_results_admin;

/*employee结果集*/
typedef struct results_employee
{
    char *id;
    char *name;
    char *sex;
    char *age;
    char *image;
    struct results_employee *next;
} link_results_employee;

/*user结果集*/
typedef struct results_user
{
    int *id;
    char *account;
    char *passwd;
    char *status;
    struct results_user *next;
} link_results_user;

/*record结果集*/
typedef struct results_record
{
    int *id;
    char *online_time;
    char *down_time;
    struct results_record *next;
} link_results_record;

/*notify结果集*/
typedef struct results_notify
{
    int *id;
    char *notify;
    struct results_notify *next;
} link_results_notify;

typedef struct results
{
    link_results_admin *r_a;
    link_results_employee *r_e;
    link_results_user *r_u;
    link_results_record *r_r;
    link_results_notify *r_n;
}result_from_mysql;

result_from_mysql *display_mysql(MYSQL_RES *res);
result_from_mysql *get_results_from_mysql(MYSQL *mysql, const char *str);
// const char *output_singal_mysql_result(MYSQL_RES *res);
const char *get_inform_form_mysql(MYSQL *mysql, const char *sql, const char *data);
int search_mysql(MYSQL *mysql, const char *str);
int connect_mysql(MYSQL *mysql);
int close_mysql(MYSQL *mysql);

#endif