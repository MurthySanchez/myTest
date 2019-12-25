#include "UI.h"
#include "function.h"
#include "mymysql.h"
#include "gtk/gtk.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

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
 * 连接主界面
 * */

/**
 * 获取系统时间
 * */
char *get_current_time()
{
    static char timestr[40];
    time_t t;
    struct tm *nowtime;

    time(&t);
    nowtime = localtime(&t);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", nowtime);

    return timestr;
}

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

/**
 * Type:
 * GTK_MESSAGE_INFO
 *GTK_MESSAGE_ERROR
 * GTK_MESSAGE_QUESTION
 *GTK_MESSAGE_WARNING
 **/
void new_dialog(GtkWidget *widget, GtkMessageType type, const gchar *msg)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    type,
                                    GTK_BUTTONS_OK,
                                    msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    // return dialog;
}

void go_back_to_firstPage(GtkWidget *widget, GtkWidget *button)
{
    char message[MID];
    printf("user exit the system.\n");
    gtk_widget_hide_all(s_window);
    sprintf(employee.end_time, "%s", get_current_time());
    snprintf(message, sizeof(message), "现在时间是%s，您已成功登出。\n已将结束时间计入考勤表中，您可自行查阅。", employee.end_time);
    new_dialog(main_window, GTK_MESSAGE_INFO, message);
    first_page();
}

/**
 * 搜索员工信息表
 * 找出员工：姓名，年龄，电话，性别，照片信息，考勤开始，考勤结束时间
 * */
void get_personal_inform(char* user)
{
    MYSQL_ROW row;
    int i;
    int rows=mysql_num_rows(res);
    int fields=mysql_num_fields(res);
    // char sql[MID];//
    // snprintf(sql,MID,"%s");
    search_mysql(mysql,"select name,sex,age,image from employee where id='147001'");
    
    printf("\n");
    getchar();

}

/**
 * 函数功能：建一个新窗口
 * 传入参数：对象（管理员或员工）
 * */
void main_page(int user)
{
    GtkWidget *frame;
    GtkWidget *hbox, *vbox, *vbox_f; //hbox:横盒子，vbox：纵盒子
    GtkWidget *table;
    GtkWidget *entry;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *image;
    GtkWidget *text_view;

    /*窗口初始化*/
    /*********************/
    s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s_window), sys_name);     //设置标题
    gtk_widget_set_size_request(s_window, M_WIDTH, M_HEIGHT); //设置大小
    gtk_window_set_resizable(GTK_WINDOW(s_window), FALSE);
    gtk_window_set_position(GTK_WINDOW(s_window), GTK_WIN_POS_CENTER);                //设置窗口位置
    gtk_container_set_border_width(GTK_CONTAINER(s_window), 0);                       //设置窗口边框宽度
    g_signal_connect(G_OBJECT(s_window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //事件监听，检测用户关闭windows时窗口关闭
    /*********************/

    /*control main_window widget -->frame*/
    // frame = gtk_frame_new("");
    table = gtk_table_new(20, 28, TRUE);
    gtk_container_add(GTK_CONTAINER(s_window), table);
    // gtk_container_set_border_width(GTK_CONTAINER(table), 0); //设置窗口边框宽度

    /*logo*/
    /*********************/
    image = gtk_image_new_from_file("./image/logo.png");
    gtk_table_attach_defaults(GTK_TABLE(table), image, 2, 7, 2, 4);
    /*********************/

    /*card*/
    /*********************/
    frame = gtk_frame_new(NULL);
    gtk_table_attach_defaults(GTK_TABLE(table), frame, 20, 25, 2, 5);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_container_add(GTK_CONTAINER(frame), hbox);

    // char src_image[SMALL] = {"./image/person/apple.jpeg"};
    image = gtk_image_new_from_file(employee.image);
    gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 5);

    char welcm_lebel[SMALL];
    sprintf(welcm_lebel, "欢迎您，\n%s", Input.id);
    label = gtk_label_new(welcm_lebel);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
    /*********************/

    /*function*/
    if (user == 0)
    {
        /*********************/
        // vbox = gtk_vbox_new(FALSE, 0);
        // gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        // gtk_table_attach_defaults(GTK_TABLE(table), vbox, 2, 21, 6, 15);

        ////function one////
        frame = gtk_frame_new("温馨提示");
        gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);
        char tips[HUGE];
        sprintf(employee.start_time, "%s", get_current_time());
        snprintf(tips, HUGE, "现在时间是：%s，已录入考勤开始时间。\n结束时间将随您退出本程序计入程序后台，您可在系统内部自助查询。", employee.start_time);
        label = gtk_label_new(tips);
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
        // gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_container_add(GTK_CONTAINER(frame), label);
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 2, 21, 6, 8);

        ////function two////
        // hbox = gtk_hbox_new(FALSE, 0);
        // gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
        // gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

        frame = gtk_frame_new("通知");
        // gtk_box_pack_start(GTK_BOX(hbox), frame, FALSE, FALSE, 5);
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 2, 9, 9, 18);
        char notice[HUGE] = {"1.weidalfjljfljd\n2.dajfkjdls"};
        label = gtk_label_new(notice);
        gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_container_add(GTK_CONTAINER(frame), label);


        ////function three////
        frame = gtk_frame_new("考勤信息查询");
        // gtk_box_pack_start(GTK_BOX(hbox), frame, FALSE, FALSE, 140);
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 11, 21, 9, 18);


        /*********************/
    }
    else
    {
        /*********************/
        // hbox = gtk_hbox_new(FALSE, 0);
        // gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
        // gtk_table_attach_defaults(GTK_TABLE(table), hbox, 2, 21, 6, 15);

        // vbox = gtk_vbox_new(FALSE, 0);
        // gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        // gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 5);

        ////function one////
        frame = gtk_frame_new("发布通知");
        // gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 5);
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 2, 11, 6, 8);
        vbox_f = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(frame), vbox_f);
        text_view = gtk_text_view_new();
        gtk_widget_set_size_request(text_view, 250, 100);
        gtk_box_pack_start(GTK_BOX(vbox_f), text_view, FALSE, FALSE, 5);
        // g_signal_connect();
        button = gtk_button_new_with_label("发布");
        gtk_box_pack_start(GTK_BOX(vbox_f), button, FALSE, FALSE, 10);
        // g_signal_connect();

        ////function two////
        frame = gtk_frame_new("员工信息查询");
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 2, 11, 10, 18);
        // gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 40);
        vbox = admin_functionTwo(s_window);
        gtk_container_add(GTK_CONTAINER(frame), vbox);

        ////function three///
        frame = gtk_frame_new("员工考勤信息");
        gtk_table_attach_defaults(GTK_TABLE(table), frame, 12, 25, 6, 18);
        // gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 300);
    }

    /*退出登陆&&退出系统*/
    /*********************/
    button = create_button(GTK_STOCK_HOME);
    // gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "退出回到首页", "首页");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(go_back_to_firstPage), s_window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 26, 27, 16, 17);

    ////exit the system////
    button = create_button(GTK_STOCK_QUIT);
    // gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips), button, "退出系统", "退出");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(delete_event), s_window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 26, 27, 18, 19);
    /*********************/

    /*function 4*/
    /*********************/
    label = gtk_label_new("当前在线人数：");
    // gtk_table_attach_defaults(GTK_TABLE(table),label,2,11,18,19);
    gtk_table_attach_defaults(GTK_TABLE(table), label, 16, 25, 0, 1);
    /*********************/

    image = gtk_image_new_from_file("./image/bj.jpg");
    // gtk_container_add(GTK_CONTAINER(table), image);
    gtk_table_attach_defaults(GTK_TABLE(table), image, 0, 28, 0, 20);

    gtk_widget_show_all(s_window);
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
        sprintf(Output.searchId, "SELECT * FROM admin WHERE id='%s'", Input.id); //admin table search
    // printf("yes\n");
    else
    {
        sprintf(Output.searchId, "SELECT * FROM user WHERE id='%s'", Input.id); //user table search
        // printf("no!\n");
    }

    sprintf(Output.searchPasswd, "%s and passwd='%s'", Output.searchId, Input.passwd);
    /*search db*/
    /*********************/
    if (search_mysql(mysql, Output.searchId))
    {
        new_dialog(NULL, GTK_MESSAGE_ERROR, "不存在该用户！");
        printf("cannot find the people\n");
    }
    else
    {
        printf("%s trying online.\n", Input.id);
        if (search_mysql(mysql, Output.searchPasswd))
        {
            new_dialog(NULL, GTK_MESSAGE_ERROR, "密码错误！");
            printf("wrong passwd!\n");
        }
        else
        {
            printf("%s %s successful logged in!\n", ch[choice], Input.id);
            gtk_widget_hide_all(main_window);
            get_personal_inform(ch[choice]);
            main_page(choice);
        }
    }
}
/*********************/

void first_page()
{
    GtkWidget *button, *radio1, *radio2; //定义按钮
    GtkWidget *table;                    //定义table
    GtkWidget *image;                    //image
    GtkWidget *frame;                    //frame
    GtkWidget *label;                    //label
    GtkWidget *check;                    //check
    GSList *group;

    /*窗口初始化*/
    /*********************/
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(main_window), "login");  //设置标题
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

    // /*control main_window widget -->frame*/
    // frame = gtk_frame_new("");
    // gtk_container_add(GTK_CONTAINER(main_window), frame);

    /*********************/
    table = gtk_table_new(20, 28, TRUE);
    gtk_container_add(GTK_CONTAINER(main_window), table);
    /*********************/

    /*logo*/
    /*********************/
    image = gtk_image_new_from_file("./image/logo.png");
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
    gtk_table_attach_defaults(GTK_TABLE(table), image, 0, 28, 0, 20);
    /*********************/

    gtk_widget_show(table);
    gtk_widget_show_all(main_window); //显示窗口(all)
}

int UI(char *name)
{
    sprintf(sys_name, "%s", name);
    gtk_init(NULL, NULL); //初始化

    // first_page();
    // main_page(1);
    get_personal_inform("user");

    gtk_main(); //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生
}
