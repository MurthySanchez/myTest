#include <gtk/gtk.h>
#include "function.h"
#include "mymysql.h"
#include "mysql/mysql.h"

const gchar *new_row[5];
static GtkWidget *clist0, *clist1, *clist2;
static GtkWidget *add_win;
static GtkWidget *entry_id;
static GtkWidget *entry_name;
static GtkWidget *entry_sex;
static GtkWidget *entry_age;
static GtkWidget *entry_search;
static GtkWidget *entry_date;
static GtkWidget *entry_state;
static GtkWidget *entry_image;
static GtkWidget *entry_passwd;

static GtkWidget *window_a;

gint current_row = 0, current_row0 = 0, current_row1 = 0, current_row2 = 0;
gint row_count = 0, row_count0 = 0, row_count1 = 0, row_count2 = 0;

/*admin function two add user inform*/
void on_function_two_ok_clicked(GtkWidget *button, GtkWidget *window)
{
    new_row[0] = gtk_entry_get_text(GTK_ENTRY(entry_id));
    new_row[1] = gtk_entry_get_text(GTK_ENTRY(entry_name));
    new_row[2] = gtk_entry_get_text(GTK_ENTRY(entry_sex));
    new_row[3] = gtk_entry_get_text(GTK_ENTRY(entry_age));

    if (g_strcmp0(new_row[0], "") == 0)
    {
        g_print("please input the IDnumber!\n");
        return;
    }
    row_count0++;
    gtk_clist_append(GTK_CLIST(clist0), (gchar **)(new_row));
    gtk_widget_destroy(window);
}

/*admin function three update user attendance state*/
void on_function_three_ok_clicked(GtkWidget *button, GtkWidget *window)
{
    new_row[0] = gtk_entry_get_text(GTK_ENTRY(entry_id));
    new_row[1] = gtk_entry_get_text(GTK_ENTRY(entry_name));
    new_row[2] = gtk_entry_get_text(GTK_ENTRY(entry_date));
    new_row[3] = gtk_entry_get_text(GTK_ENTRY(entry_state));
    if (g_strcmp0(new_row[0], "") == 0)
    {
        g_print("please input the IDnumber!\n");
        return;
    }
    row_count1++;
    gtk_clist_append(GTK_CLIST(clist1), (gchar **)(new_row));
    gtk_widget_destroy(window);
}

void on_ok_clicked(GtkWidget *button, GtkWidget *window)
{
    // new_row[0] = gtk_entry_get_text(GTK_ENTRY(entry_id));
    // new_row[1] = gtk_entry_get_text(GTK_ENTRY(entry_name));
    // new_row[2] = gtk_entry_get_text(GTK_ENTRY(entry_sex));
    // new_row[3] = gtk_entry_get_text(GTK_ENTRY(entry_birthday));
    // new_row[4] = gtk_entry_get_text(GTK_ENTRY(entry_email));
    // if (g_strcmp0(new_row[0], "") == 0)
    // {
    //     g_print("please input the IDnumber!\n");
    //     return;
    // }
    // row_count++;
    // gtk_clist_append(GTK_CLIST(clist), (gchar **)(new_row));
    // gtk_widget_destroy(window);
}

void goto_search(GtkWidget *button, gint data)
{
}

/*点击取消，关闭子窗口*/
void on_cancel_clicked(GtkWidget *button, GtkWidget *window)
{
    gtk_widget_destroy(window);
}

/*添加信息窗口*/
GtkWidget *create_addwin(GtkWidget *window, gint data)
{
    GtkWidget *win;
    GtkWidget *vbox;
    GtkWidget *table;
    GtkWidget *bbox;
    GtkWidget *label;
    GtkWidget *button;

    switch (data)
    {
    case 0: //admin
        win = gtk_dialog_new_with_buttons("添加员工信息", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
        win = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(win), "添加员工");
        gtk_container_set_border_width(GTK_CONTAINER(win), 10);
        gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
        g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);
        vbox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(win), vbox);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(win)->vbox), vbox);
        table = gtk_table_new(4, 2, FALSE);
        gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 5);

        label = gtk_label_new("员工编号"); //必填
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
        label = gtk_label_new("年龄");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 3, 4);
        entry_age = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_age, 1, 2, 3, 4);
        bbox = gtk_hbutton_box_new();
        gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 5);
        gtk_box_set_spacing(GTK_BOX(bbox), 5);

        gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
        button = gtk_button_new_from_stock(GTK_STOCK_OK);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_function_two_ok_clicked), win);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);
        button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), win);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);

        break;
    case 1:
        win = gtk_dialog_new_with_buttons("修改员工考勤信息", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
        win = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(win), "添加员工考勤状态");
        gtk_container_set_border_width(GTK_CONTAINER(win), 10);
        gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
        g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);
        vbox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(win), vbox);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(win)->vbox), vbox);
        table = gtk_table_new(4, 2, FALSE);
        gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 5);

        label = gtk_label_new("员工编号");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
        entry_id = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_id, 1, 2, 0, 1);
        label = gtk_label_new("姓名");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 1, 2);
        entry_name = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_name, 1, 2, 1, 2);
        label = gtk_label_new("日期");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 2, 3);
        entry_date = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_date, 1, 2, 2, 3);
        label = gtk_label_new("考勤状态");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 3, 4);
        entry_state = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_state, 1, 2, 3, 4);

        bbox = gtk_hbutton_box_new();
        gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 5);
        gtk_box_set_spacing(GTK_BOX(bbox), 5);

        gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
        button = gtk_button_new_from_stock(GTK_STOCK_OK);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_function_three_ok_clicked), win);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);
        button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_cancel_clicked), win);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 5);

        break;
    default: //user change inform
        win = gtk_dialog_new_with_buttons("修改员工个人信息", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
        win = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(win), "修改个人信息");
        gtk_container_set_border_width(GTK_CONTAINER(win), 10);
        gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
        g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(gtk_widget_destroy), win);
        vbox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(win), vbox);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(win)->vbox), vbox);
        table = gtk_table_new(6, 2, FALSE);
        gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 5);

        label = gtk_label_new("编号");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
        entry_id = gtk_entry_new();
        gtk_entry_set_editable(GTK_ENTRY(entry_id), FALSE);
        gtk_table_attach_defaults(GTK_TABLE(table), entry_id, 1, 2, 0, 1);
        label = gtk_label_new("姓名");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 1, 2);
        entry_name = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_name, 1, 2, 1, 2);
        label = gtk_label_new("性别");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 2, 3);
        entry_sex = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_sex, 1, 2, 2, 3);
        label = gtk_label_new("年龄");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 3, 4);
        entry_age = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_age, 1, 2, 3, 4);
        label = gtk_label_new("头像地址");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 4, 5);
        entry_image = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_image, 1, 2, 4, 5);
        label = gtk_label_new("密码");
        gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 5, 6);
        entry_passwd = gtk_entry_new();
        gtk_table_attach_defaults(GTK_TABLE(table), entry_passwd, 1, 2, 5, 6);

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
        break;
    }

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
void goto_first(GtkWidget *button, gint data)
{
    switch (data)
    {
    case 0:
        current_row0 = 0;
        gtk_clist_select_row(GTK_CLIST(clist0), current_row0, 0);
        break;
    case 1:
        current_row1 = 0;
        gtk_clist_select_row(GTK_CLIST(clist1), current_row1, 0);
        break;
    case 2:
        current_row2 = 0;
        gtk_clist_select_row(GTK_CLIST(clist2), current_row2, 0);
        break;
    default:
        break;
    }
}

/*去最后一行*/
void goto_last(GtkWidget *button, gint data)
{
    switch (data)
    {
    case 0:
        current_row0 = row_count0 - 1;
        gtk_clist_select_row(GTK_CLIST(clist0), current_row0, 0);
        break;
    case 1:
        current_row1 = row_count1 - 1;
        gtk_clist_select_row(GTK_CLIST(clist1), current_row1, 0);
        break;
    case 2:
        current_row2 = row_count2 - 1;
        gtk_clist_select_row(GTK_CLIST(clist2), current_row2, 0);
        break;
    default:
        break;
    }
}

/*下一行*/
void goto_back(GtkWidget *button, gint data)
{
    switch (data)
    {
    case 0:
        current_row0--;
        if (current_row0 == -1)
            return;
        gtk_clist_select_row(GTK_CLIST(clist0), current_row0, 0);
        break;
    case 1:
        current_row1--;
        if (current_row1 == -1)
            return;
        gtk_clist_select_row(GTK_CLIST(clist1), current_row1, 0);
        break;
    case 2:
        current_row2--;
        if (current_row2 == -1)
            return;
        gtk_clist_select_row(GTK_CLIST(clist2), current_row2, 0);
        break;
    default:
        break;
    }
}

/*上一行*/
void goto_forward(GtkWidget *button, gint data)
{
    switch (data)
    {
    case 0:
        current_row0++;
        if (current_row0 > row_count0)
            return;
        gtk_clist_select_row(GTK_CLIST(clist0), current_row0, 0);
        break;
    case 1:
        current_row1++;
        if (current_row1 > row_count1)
            return;
        gtk_clist_select_row(GTK_CLIST(clist1), current_row1, 0);
        break;
    case 2:
        current_row2++;
        if (current_row2 > row_count2)
            return;
        gtk_clist_select_row(GTK_CLIST(clist2), current_row2, 0);
        break;
    default:
        break;
    }
}

/*添加数据*/
void append_row(GtkWidget *button, gint data)
{
    switch (data)
    {
    case 0:
        add_win = create_addwin(window_a, data);
        break;
    case 1:
        add_win = create_addwin(window_a, data);
        break;
    default:
        g_print("something error in append_row().\n");
        break;
    }
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
 * @inits:表格初始显示值
 * */
GtkWidget *function(GtkWidget *window, gchar **titles, int field, int length, gint id, MYSQL_RES *inits)
{
    GtkWidget *vbox;
    GtkWidget *bbox;
    GtkWidget *button;
    GtkTooltips *button_tips;
    MYSQL_ROW row;

    window_a = window;

    vbox = gtk_vbox_new(FALSE, 0);
    // gtk_container_add(GTK_CONTAINER(window), vbox);
    switch (id)
    {
    case 0: //admin
        clist0 = gtk_clist_new_with_titles(field, titles);
        for (int i = 0; i < field; i++)
        {
            gtk_clist_set_column_width(GTK_CLIST(clist0), i, length / field);
            gtk_clist_set_column_justification(GTK_CLIST(clist0), field, GTK_JUSTIFY_FILL);
        }
        while(row=mysql_fetch_row(inits))
        {
            gtk_clist_append(GTK_CLIST(clist0), row);
        }
        gtk_box_pack_start(GTK_BOX(vbox), clist0, TRUE, TRUE, 5);

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
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_search), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_FIRST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到首行", "首行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_first), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_BACK);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到前一行", "前一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_back), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_FORWARD);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到下一行", "下一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_forward), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_LAST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到尾行", "尾行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_last), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);

        button = create_button(GTK_STOCK_ADD);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "新增一行", "新增");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(append_row), (gpointer)0);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        break;
    case 1: //admin
        clist1 = gtk_clist_new_with_titles(field, titles);
        for (int i = 0; i < field; i++)
        {
            gtk_clist_set_column_width(GTK_CLIST(clist1), i, length / field);
            gtk_clist_set_column_justification(GTK_CLIST(clist1), field, GTK_JUSTIFY_FILL);
        }
        while(row=mysql_fetch_row(inits))
        {
            gtk_clist_append(GTK_CLIST(clist1), row);
        }
        gtk_box_pack_start(GTK_BOX(vbox), clist1, TRUE, TRUE, 5);

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
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_search), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_FIRST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到首行", "首行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_first), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_BACK);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到前一行", "前一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_back), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_FORWARD);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到下一行", "下一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_forward), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_LAST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到尾行", "尾行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_last), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);

        button = create_button(GTK_STOCK_ADD);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "新增一行", "新增");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(append_row), (gpointer)1);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        break;
    case 2: //employee
        clist2 = gtk_clist_new_with_titles(field, titles);
        for (int i = 0; i < field; i++)
        {
            gtk_clist_set_column_width(GTK_CLIST(clist2), i, length / field);
            gtk_clist_set_column_justification(GTK_CLIST(clist2), field, GTK_JUSTIFY_FILL);
        }
        while(row=mysql_fetch_row(inits))
        {
            gtk_clist_append(GTK_CLIST(clist2), row);
        }
        gtk_box_pack_start(GTK_BOX(vbox), clist2, TRUE, TRUE, 5);

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
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_search), (gpointer)2);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_FIRST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到首行", "首行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_first), (gpointer)2);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_BACK);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到前一行", "前一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_back), (gpointer)2);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GO_FORWARD);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到下一行", "下一行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_forward), (gpointer)2);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);
        button = create_button(GTK_STOCK_GOTO_LAST);
        gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "转到尾行", "尾行");
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(goto_last), (gpointer)2);
        gtk_box_pack_start(GTK_BOX(bbox), button, FALSE, FALSE, 2);

        break;

    default:
        break;
    }

    return vbox;
}
