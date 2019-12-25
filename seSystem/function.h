#ifndef _FUNCTION_H_
#define _FUNCTION_H_

static gchar *titles[5] = {"编号", "姓名", "出生年月", "电子邮件"};
const gchar *new_row[5];
static GtkWidget *clist;
static GtkWidget *add_win;
static GtkWidget *entry_id;
static GtkWidget *entry_name;
static GtkWidget *entry_sex;
static GtkWidget *entry_birthday;
static GtkWidget *entry_email;
static GtkWidget *entry_search;

// static GtkWidget *window;

void on_ok_clicked(GtkWidget *button, gpointer data);
void on_cancel_clicked(GtkWidget *button, gpointer data);
GtkWidget *create_button(gchar *stockid);
void goto_first(GtkWidget *button, gpointer data);
void goto_last(GtkWidget *button, gpointer data);
void goto_back(GtkWidget *button, gpointer data);
void goto_forward(GtkWidget *button, gpointer data);
GtkWidget *admin_functionTwo(GtkWidget *window);

#endif