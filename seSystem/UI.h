#ifndef UI_H_
#define UI_H_

#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mymysql.h"

#define WIDTH 846
#define HEIGHT 600
#define M_WIDTH 1600    //w main_page
#define M_HEIGHT    900 //h main_page
#define SMALL 64
#define MID 128
#define HUGE 256

struct Input
{
    const gchar *id;
    const gchar *passwd;
} Input;

struct Output
{
    char searchId[MID];
    char searchPasswd[HUGE];
} Output;

/*姓名，年龄，电话，性别，照片信息，考勤开始，考勤结束时间*/
struct employee
{
    char name[10];
    short age;
    char phone[11];
    char sex[2];
    char src_image[SMALL];
    char start_time[40];
    char end_time[40];
} employee;

//外部变量
extern MYSQL *mysql;

//全局变量
GtkWidget *main_window, *s_window; //定义窗口
GtkWidget *entryUser, *entryPW;    //entry
char sys_name[SMALL];

void first_page();
void main_page(int user);

int UI(char *name);

#endif