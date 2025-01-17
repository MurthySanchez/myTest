#include <gtk/gtk.h>
#include "function.h"


// static gchar *titles[5] = {"编号", "姓名", "出生年月", "电子邮件"};
const gchar *new_row[5];
static GtkWidget *clist;
static GtkWidget *add_win;
static GtkWidget *entry_id;
static GtkWidget *entry_name;
static GtkWidget *entry_sex;
static GtkWidget *entry_birthday;
static GtkWidget *entry_email;
static GtkWidget *entry_search;

// struct titles
// {
//     char *title;
//     struct titles *next;
// }titles;

static GtkWidget *window_a;

gint current_row = 0;
gint row_count = 0;

/**/
void on_ok_clicked(GtkWidget *button, GtkWidget *window)
{
    new_row[0] = gtk_entry_get_text(GTK_ENTRY(entry_id));
    new_row[1] = gtk_entry_get_text(GTK_ENTRY(entry_name));
    new_row[2] = gtk_entry_get_text(GTK_ENTRY(entry_sex));
    new_row[3] = gtk_entry_get_text(GTK_ENTRY(entry_birthday));
    new_row[4] = gtk_entry_get_text(GTK_ENTRY(entry_email));
    if (g_strcmp0(new_row[0], "") == 0)
    {
        g_print("please input the IDnumber!\n");
        return;
    }
    row_count++;
    gtk_clist_append(GTK_CLIST(clist), (gchar **)(new_row));
    gtk_widget_destroy(window);
}

void goto_search(GtkWidget *button, gpointer data)
{

}

/*点击取消，关闭子窗口*/
void on_cancel_clicked(GtkWidget *button, GtkWidget *window)
{
    gtk_widget_destroy(window);
}

/*添加信息窗口*/
GtkWidget *create_addwin(GtkWidget *window)
{
    GtkWidget *win;
    GtkWidget *vbox;
    GtkWidget *table;
    GtkWidget *bbox;
    GtkWidget *label;
    GtkWidget *button;
    win = gtk_dialog_new_with_buttons("添加员工信息", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
    win = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(win), "添加记录");
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(win), vbox);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(win)->vbox), vbox);
    table = gtk_table_new(5, 2, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 5);

    label = gtk_label_new("编号");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
    entry_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), entry_id, 1, 2, 0, 1);
    label = gtk_label_new("姓名");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 1, 2);
    entry_name = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), entry_name, 1, 2, 1, 2);
    label = gtk_label_new("性别");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 2, 3);
    entry_sex = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), entry_sex, 1, 2, 2, 3);
    label = gtk_label_new("出生年月");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 3, 4);
    entry_birthday = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), entry_birthday, 1, 2, 3, 4);
    label = gtk_label_new("电子邮件");
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 4, 5);
    entry_email = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table), entry_email, 1, 2, 4, 5);
    bbox = gtk_hbutton_box_new();
    gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 5);
    gtk_box_set_spacing(GTK_BOX(bbox), 5);

    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_ok_clicked), win);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);
    button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), win);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);

    gtk_widget_show_all(win);
    //gtk_dialog_run(GTK_DIALOG(win));
    return win;
}

/*创建带图标的按钮*/
GtkWidget *create_button(gchar *stockid)
{
    GtkWidget *button;
    GtkWidget *image;
    image = gtk_image_new_from_stock(stockid, GTK_ICON_SIZE_MENU);
    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), image);
    return button;
}

/*去第一行*/
void goto_first(GtkWidget *button, gpointer data)
{
    current_row = 0;
    gtk_clist_select_row(GTK_CLIST(clist), current_row, 0);
}

/*去最后一行*/
void goto_last(GtkWidget *button, gpointer data)
{
    current_row = row_count - 1;
    gtk_clist_select_row(GTK_CLIST(clist), current_row, 0);
}

/*下一行*/
void goto_back(GtkWidget *button, gpointer data)
{
    current_row--;
    if (current_row == -1)
        return;
    gtk_clist_select_row(GTK_CLIST(clist), current_row, 0);
}

/*上一行*/
void goto_forward(GtkWidget *button, gpointer data)
{
    current_row++;
    if (current_row > row_count)
        return;
    gtk_clist_select_row(GTK_CLIST(clist), current_row, 0);
}

/*添加数据*/
void append_row(GtkWidget *button, gint data)
{
    add_win = create_addwin(window_a);
}

/**
 * 生成输出表格
 * @window:表格所在窗口
 * @titiles:表头
 * @field:列数
 * @length:窗口大小
 * @id:0-2
 * 0: admin添加员工信息
 * 1：admin员工考勤信息
 * 2：员工查看自身考勤信息
 * */
GtkWidget *admin_functionTwo(GtkWidget *window, gchar **titles, int field, int length, int id)
{
    GtkWidget *vbox;
    GtkWidget *bbox;
    GtkWidget *button;
    GtkTooltips *button_tips;

    window_a=window;
 
    vbox = gtk_vbox_new(FALSE, 0);
    // gtk_container_add(GTK_CONTAINER(window), vbox);
    clist = gtk_clist_new_with_titles(field, titles);
    for (int i = 0; i < field; i++)
    {
        gtk_clist_set_column_width(GTK_CLIST(clist), i, length/field);
        gtk_clist_set_column_justification(GTK_CLIST(clist), field, GTK_JUSTIFY_FILL);
    }
    gtk_box_pack_start(GTK_BOX(vbox), clist, TRUE, TRUE, 5);

    bbox = gtk_hbutton_box_new();
    button_tips = gtk_tooltips_new();
    gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 5);
    gtk_box_set_spacing(GTK_BOX(bbox), 5);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
    gtk_button_box_set_child_size(GTK_BUTTON_BOX(bbox), 20, 20);
    // entry_search = gtk_entry_new();
    // gtk_box_pack_start(GTK_BOX(bbox), entry_search, FALSE, FALSE, 5);
    button = create_button(GTK_STOCK_FIND);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "查询", "查询");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(goto_search),NULL);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
    button = create_button(GTK_STOCK_GOTO_FIRST);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到首行", "首行");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_first), NULL);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
    button = create_button(GTK_STOCK_GO_BACK);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到前一行", "前一行");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_back), NULL);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
    button = create_button(GTK_STOCK_GO_FORWARD);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到下一行", "下一行");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_forward), NULL);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
    button = create_button(GTK_STOCK_GOTO_LAST);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到尾行", "尾行");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_last), NULL);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);

    button = create_button(GTK_STOCK_ADD);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "新增一行", "新增");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(append_row), id);
    gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
    // button = create_button(GTK_STOCK_QUIT);
    // gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "退出", "退出");
    // g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    // gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);

    // gtk_widget_show_all(window);
    // gtk_main();
    // return TRUE;
    return vbox;
}
