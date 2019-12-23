#include "mymysql.h"
#include "UI.h"
#include "gtk/gtk.h"
#include "mysql/mysql.h"
#include "stdio.h"
#include "stdlib.h"

#define SYSTEM_NAME "Company Attendance System"

/*全局变量*/
MYSQL* mysql;

/**************
 * 初始化系统
 * *************/
int init_system(){
    if (!(mysql=mysql_init(NULL)))
    { //分配和初始化MYSQL对象
        printf("mysql_init(): %s\n", mysql_error(mysql));
        return -1;
    }
    if (connect_mysql(mysql)==0)
        printf("Connected MySQL successful! \n");
    
    return 0;    
}

/*************
 * *main函数
 * ************/
int main()
{
    //init the system
    init_system();
    // mysql_query(mysql,"select * from admin");
    // printf("search...\n");
    // if(search_mysql(mysql,"SELECT * FROM admin WHERE id=95001"))
    //     printf("wrong!\n");

    // display_mysql(mysql_store_result(mysql));

    //loading the UI
    UI(SYSTEM_NAME);

    //close the DB
    if (!close_mysql(mysql))
        printf("DB closed success!\n");
    return 0;
}