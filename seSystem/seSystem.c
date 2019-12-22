#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include "mysql.h"
#include "UI.h"

struct admin_id
{
    int id;
    char username[20];
    char passwd[20];
} admin_id;

struct employee_id
{
    int id;
    char username[20];
    char passwd[20];
} employee_id;

int adminLogIn()
{
    printf("enter your username:");
    char username[20];
    scanf("%s", username);
    printf("%s\n", username);
    printf("enter your passwd:");
    char passwd[20];
    scanf("%s", passwd);
    printf("%s\n", passwd);
    return 0;
}

int employeeLogIn()
{

    return 0;
}

int menuDemo()
{

    printf("************************************************\n");
    printf("*  Welcome the Company Worktime Manage System  *\n");
    printf("************************************************\n");
    printf("\n");
    printf("who you are?\n");
    printf("1.admin\t2.employee\n");
    int choice;
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        adminLogIn();
        break;
    case 2:
        employeeLogIn();
        break;
    default:
        menuDemo();
        break;
    }

    return 0;
}

int main()
{
    // MYSQL mysql;
    // MYSQL_ROW row;
    // MYSQL_RES *result;

    // mysql_init(&mysql);
    // if(!mysql_real_connect(&mysql,"localhost","root","123456","test",0,NULL,0)){
    //     printf("Connection failed,%s\n",mysql_error(&mysql));
    // }
    // mysql_close(&mysql);
    // menuDemo();
    UI();
    return 0;
}