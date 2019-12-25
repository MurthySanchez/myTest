
#ifndef MY_MYSQL_H_
#define MY_MYSQL_H_

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "config.h"

// /*结果集*/
// typedef struct results
// {
//     char *result;
//     struct results *next;    
// }link_mysql_results;

void display_mysql(MYSQL_RES *res);
int search_mysql(MYSQL *mysql, const char *str);
int connect_mysql(MYSQL *mysql);
int close_mysql(MYSQL *mysql);

#endif