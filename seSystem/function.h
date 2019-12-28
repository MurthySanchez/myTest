#ifndef _FUNCTION_H_
#define _FUNCTION_H_


void on_function_three_ok_clicked(GtkWidget *button, GtkWidget *window);
void on_ok_clicked(GtkWidget *button, GtkWidget *window);
void goto_search(GtkWidget *button, gint data);
void on_cancel_clicked(GtkWidget *button, GtkWidget *window);
GtkWidget *create_addwin(GtkWidget *window, gint data);
GtkWidget *create_button(gchar *stockid);
void goto_first(GtkWidget *button, gint data);
void goto_last(GtkWidget *button, gint data);
void goto_back(GtkWidget *button, gint data);
void goto_forward(GtkWidget *button, gint data);
void append_row(GtkWidget *button, gint data);
GtkWidget *function(GtkWidget *window, gchar **titles, int field, int length, gint id,char **inits, int init_row);
// GtkWidget *admin_functionTwo(GtkWidget *window, gchar **titles, int field, int length, int id);
void on_function_two_ok_clicked(GtkWidget *button, GtkWidget *window);

// void on_ok_clicked(GtkWidget *button, GtkWidget *window);
// void on_cancel_clicked(GtkWidget *button, GtkWidget *window);
// GtkWidget *create_button(gchar *stockid);
// void goto_first(GtkWidget *button, gint data);
// void goto_last(GtkWidget *button, gint data);
// void goto_back(GtkWidget *button, gint data);
// void goto_forward(GtkWidget *button, gint data);
// GtkWidget *create_addwin(GtkWidget *window);
// GtkWidget *admin_functionTwo(GtkWidget *window, gchar **titles, int field, int length, int id);

#endif