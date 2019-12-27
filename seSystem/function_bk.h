#ifndef _FUNCTION_H_
#define _FUNCTION_H_

const gchar *new_row[5];
static    GtkWidget *clist;
//clist0:admin_user, clist1:admin_attend, clist2:user_attend
static GtkWidget *clist0,*clist1,*clist2;
static GtkWidget *add_win;

//admin_user
static GtkWidget *entry_user_id;
static GtkWidget *entry_user_name;
static GtkWidget *entry_user_sex;
static GtkWidget *entry_user_age;

// static GtkWidget *entry_email;
static GtkWidget *entry_search;

// struct titles
// {
//     char *title;
//     struct titles *next;
// }titles;

static GtkWidget *window_a;

void on_ok_clicked(GtkWidget *button, GtkWidget *window);
void on_cancel_clicked(GtkWidget *button, GtkWidget *window);
GtkWidget *create_button(gchar *stockid);
void goto_first(GtkWidget *button, gpointer data);
void goto_last(GtkWidget *button, gpointer data);
void goto_back(GtkWidget *button, gpointer data);
void goto_forward(GtkWidget *button, gpointer data);
GtkWidget *create_addwin(GtkWidget *window);
GtkWidget *create_addwin_user(GtkWidget *window);
GtkWidget *create_addwin_attend(GtkWidget *window);
GtkWidget *create_addwin_user_attend(GtkWidget *window);
GtkWidget *admin_functionTwo(GtkWidget *window, gchar **titles, int field, int length, int id);

#endif