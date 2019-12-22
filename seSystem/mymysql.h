
#ifndef MY_MYSQL_H_
#define MY_MYSQL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "config.h"

int connect_mysql();
int close_mysql();

#endif