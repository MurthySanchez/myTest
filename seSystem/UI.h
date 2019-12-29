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
typedef struct Input
{
    char id[11];
    char passwd[20];
} In;


/*由输入信息生成搜索语句*/
typedef struct Output
{
    char searchId[MID];
    char searchPasswd[HUGE];
} Out;

typedef struct employee
{
    char id[11];
    char name[10];
    char sex[10];
    char age[10];
    char image[MID];
} employ;

/*考勤开始，考勤结束时间*/
typedef struct record
{
    // char record_id[8];
    char start_time[40];
    char end_time[40];
} recrd;

void first_page();
void get_personal_inform(int choice);
void send_notify(GtkWidget *widget, GtkTextBuffer *buffer);
void callBack(GtkWidget *widget, GtkWidget *button);
// char *longSQLcreated(char *num);
void main_page(int user);
void create_dialog(GtkWidget *widget, GtkMessageType type, const gchar *msg);
void go_back_to_firstPage(GtkWidget *widget, gint data);
void delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
int UI(char *name);

#endif