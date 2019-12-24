#include "UI.h"
#include "mymysql.h"
#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define WIDTH 846
#define HEIGHT 600

struct Input
{
    const gchar *id;
    const gchar *passwd;
    char searchId[128];
    char searchPasswd[256];
} Input;

GtkWidget *main_window, s_window; //定义窗口
GtkWidget *entryUser, *entryPW;   //entry

extern MYSQL *mysql;
/*UI界面最新进展
 * 窗口搭建完成 846*600
 * 退出按钮ok
 * 设置窗口为19*27的格子
 *  添加系统logo 大小：125*89p
 * 添加label用户名，密码
 * 添加用户名输入框，密码输入框（不可见）
 * 添加bj
 * 数据库连接成功，数据可操作
 * 添加对话框
 * */

void delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    g_print("user clicked exit\n");
    gtk_main_quit();
}

void entry_toggle_visibility(GtkWidget *checkbutton, GtkWidget *entry)
{
    gtk_entry_set_visibility(GTK_ENTRY(entry),
                             GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void enter_callback(GtkWidget *widget, GtkWidget *entry)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("Entry contents: %s\n", entry_text);
}

GtkWidget *new_dialog(GtkWidget *widget, GtkMessageType type, const gchar *msg)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    type,
                                    GTK_BUTTONS_OK,
                                    msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return dialog;
}

/**
 * 函数功能：建一个新窗口
 * 传入参数：对象（管理员或员工）
 * */
void new_window()
{
    GtkWidget *s_window;
    GtkWidget *button;
    s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(s_window), "delete_event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(G_OBJECT(s_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(s_window), 10);

    button = gtk_button_new_with_label("Hello world !");
    // g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), "1");
    gtk_container_add(GTK_CONTAINER(s_window), button);

    gtk_widget_show(button);
    gtk_widget_show(s_window);

    g_print("Hello World\n"); //temp(data );
}

/**
 * 登陆按钮事件
 * */
void callBack(GtkWidget *widget, GtkWidget *button)
{
    GtkWidget *dialog;
    gboolean choice;
    char ch[2][6] = {"user", "admin"}; //0:user,1:admin
    /*get input id and passwd*/
    Input.id = gtk_entry_get_text(GTK_ENTRY(entryUser));
    printf("id is %s\n", Input.id);
    Input.passwd = gtk_entry_get_text(GTK_ENTRY(entryPW));
    printf("passwd is %s\n", Input.passwd);
    if ((choice = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))))
        sprintf(Input.searchId, "SELECT * FROM admin WHERE id=%s", Input.id); //admin table search
    // printf("yes\n");
    else
    {
        sprintf(Input.searchId, "SELECT * FROM user WHERE id=%s", Input.id); //user table search
        // printf("no!\n");
    }

    sprintf(Input.searchPasswd, "%s and passwd='%s'", Input.searchId, Input.passwd);
    /*search db*/
    /*********************/
    if (search_mysql(mysql, Input.searchId))
    {
        dialog = new_dialog(NULL, GTK_MESSAGE_ERROR, "用户名错误！");
        printf("cannot find the people\n");
    }
    else
    {
        printf("%s trying online.\n", Input.id);
        if (search_mysql(mysql, Input.searchPasswd))
        {
            dialog = new_dialog(NULL, GTK_MESSAGE_ERROR, "密码错误！");
            printf("wrong passwd!\n");
        }
        else
        {
            printf("%s %s successful logged in!\n", ch[choice], Input.id);
            gtk_widget_hide_all(main_window);
            new_window();
        }
    }
}
/*********************/

int UI(char *name)
{
    GtkWidget *button, *radio1, *radio2; //定义按钮
    GtkWidget *table;                    //定义table
    GtkWidget *image;                    //image
    GtkWidget *frame;                    //frame
    GtkWidget *label;                    //label
    GtkWidget *check;                    //check
    GSList *group;

    gtk_init(NULL, NULL); //初始化

    /*窗口初始化*/
    /*********************/
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(main_window), name);     //设置标题
    gtk_widget_set_size_request(main_window, WIDTH, HEIGHT); //设置大小
    // gtk_window_set_default_size(GTK_WINDOW(main_window),WIDTH,HEIGHT);    //设置大小
    gtk_window_set_resizable(GTK_WINDOW(main_window), FALSE);
    gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER); //设置窗口位置
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 0);        //设置窗口边框宽度
    // change_background(main_window, WIDTH, HEIGHT*1.5, "./image/bj.jpg");  //设置窗口背景图片
    // image=gtk_image_new_from_file("./image/bj2.PNG");
    // gtk_container_add(GTK_CONTAINER(main_window),image);
    g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //事件监听，检测用户关闭windows时窗口关闭
    /*********************/

    /*control main_window widget -->frame*/
    frame = gtk_frame_new("");
    gtk_container_add(GTK_CONTAINER(main_window), frame);

    /*********************/
    table = gtk_table_new(19, 27, TRUE);
    gtk_container_add(GTK_CONTAINER(frame), table);
    /*********************/

    /*logo*/
    /*********************/
    image = gtk_image_new_from_file("./image/icon.png");
    gtk_table_attach_defaults(GTK_TABLE(table), image, 9, 19, 3, 7);
    gtk_widget_show(image);
    /*********************/

    /*frame for 用户名*/
    /*********************/
    // frame=gtk_frame_new("");
    label = gtk_label_new("用户名");
    // gtk_container_add(GTK_CONTAINER(frame),label);
    gtk_table_attach_defaults(GTK_TABLE(table), label, 8, 10, 9, 10);

    entryUser = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entryUser), 50);
    g_signal_connect(G_OBJECT(entryUser), "activate", G_CALLBACK(enter_callback), entryUser);
    gtk_table_attach_defaults(GTK_TABLE(table), entryUser, 11, 18, 9, 10);
    /*********************/

    /*frame for 密码*/
    /*********************/
    // frame=gtk_frame_new("");
    label = gtk_label_new("密码");
    // gtk_container_add(GTK_CONTAINER(frame),label);
    gtk_table_attach_defaults(GTK_TABLE(table), label, 8, 10, 11, 12);

    entryPW = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entryPW), 50);
    g_signal_connect(G_OBJECT(entryPW), "activate", G_CALLBACK(enter_callback), entryPW);
    gtk_entry_set_visibility(GTK_ENTRY(entryPW), FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table), entryPW, 11, 18, 11, 12);

    image = gtk_image_new_from_file("./image/eye.png");
    check = gtk_check_button_new();
    gtk_container_add(GTK_CONTAINER(check), image);
    gtk_table_attach_defaults(GTK_TABLE(table), check, 18, 20, 11, 12);
    g_signal_connect(G_OBJECT(check), "toggled",
                     G_CALLBACK(entry_toggle_visibility), entryPW);
    gtk_container_set_border_width(GTK_CONTAINER(check), 0); //设置窗口边框宽度
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), FALSE);
    /*********************/

    /*选择登陆身份*/
    /*********************/
    radio1 = gtk_radio_button_new_with_label(NULL, "管理员");
    gtk_table_attach_defaults(GTK_TABLE(table), radio1, 11, 14, 12, 13);
    // gtk_signal_connect(GTK_OBJECT(radio1),"released",G_CALLBACK(radio_clicked),(gpointer)1);

    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1));

    radio2 = gtk_radio_button_new_with_label(group, "职工");
    gtk_table_attach_defaults(GTK_TABLE(table), radio2, 15, 17, 12, 13);
    // gtk_signal_connect(GTK_OBJECT(radio2),"released",G_CALLBACK(radio_clicked),(gpointer)2);
    /*********************/

    /*登陆按钮*/
    /*********************/
    button = gtk_button_new_with_label("登陆");
    // g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),main_window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 11, 17, 14, 15);
    // g_signal_connect(GtkWidget(main_window), )
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(callBack), radio1);
    gtk_widget_show(button); //显示按钮
    /*********************/

    /*退出按钮*/
    /*********************/
    button = gtk_button_new_with_label("退出系统");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(delete_event), main_window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 23, 26, 16, 17);
    gtk_widget_show(button); //显示按钮
    /*********************/

    /*table for bj*/
    /*********************/
    image = gtk_image_new_from_file("./image/bj.jpg");
    // gtk_container_add(GTK_CONTAINER(frame),image);
    gtk_table_attach_defaults(GTK_TABLE(table), image, 0, 27, 0, 19);
    /*********************/

    gtk_widget_show(table);
    gtk_widget_show_all(main_window); //显示窗口(all)
    gtk_main();                       //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生

    return FALSE;
}
