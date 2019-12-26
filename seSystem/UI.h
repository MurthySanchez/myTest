#ifndef UI_H_
#define UI_H_

#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mymysql.h"

#define WIDTH 846
#define HEIGHT 600
#define M_WIDTH 1600 //w main_page
#define M_HEIGHT 900 //h main_page
#define SMALL 64
#define MID 128
#define HUGE 256

//外部变量
extern MYSQL *mysql;
extern MYSQL_RES *res;

/*输入信息*/
struct Input
{
    const gchar *id;
    const gchar *passwd;
} Input;

/*由输入信息生成搜索语句*/
struct Output
{
    char searchId[MID];
    char searchPasswd[HUGE];
} Output;

/*考勤开始，考勤结束时间*/
struct record
{
    char start_time[40];
    char end_time[40];
} record;

//全局变量
GtkWidget *main_window, *s_window; //定义窗口
GtkWidget *entryUser, *entryPW;    //entry
char sys_name[SMALL];
char *admin_image;
GtkTextBuffer *buffer; //文本框缓冲区
GtkTextIter *Iter;
result_from_mysql *p; //存放搜索结果

void first_page();
void main_page(int user);

int UI(char *name);

#endif