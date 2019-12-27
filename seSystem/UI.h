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
    char *id;
    char *name;
    char *sex;
    char *age;
    char *image;
} employee;

/*考勤开始，考勤结束时间*/
struct record
{
    char start_time[40];
    char end_time[40];
} record;

void first_page();
void main_page(int user);

int UI(char *name);

#endif