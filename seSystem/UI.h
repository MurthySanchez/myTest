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

struct employee
{
    const char *id;
    const char *name;
    const char *sex;
    const char *age;
    const char *image;
} employee;

/*考勤开始，考勤结束时间*/
struct record
{
    char record_id[8];
    char start_time[40];
    char end_time[40];
} record;

void first_page();
void get_personal_inform(int choice);
void send_notify(GtkWidget *widget, GtkTextBuffer *buffer);
void callBack(GtkWidget *widget, GtkWidget *button);
char *longSQLcreated(char *num);
void main_page(int user);
void new_dialog(GtkWidget *widget, GtkMessageType type, const gchar *msg);
int UI(char *name);

#endif