#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "UI.h"
#include "mysql.h"

#define WIDTH 846
#define HEIGHT 600
/*UI界面最新进展
 * 窗口搭建完成 846*600
 * 退出按钮ok
 * 设置窗口为19*27的格子
 *  添加系统logo 大小：125*89p
 * 添加label用户名，密码
 * 添加用户名输入框，密码输入框（不可见）
 * */

struct Input
{
    const gchar *username;
    const gchar *passwd;
} Input;

GtkWidget *entryUser, *entryPW; //entry

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

void callBack(GtkWidget *widget, gpointer data)
{
    /*get input username and passwd*/
    Input.username = gtk_entry_get_text(GTK_ENTRY(entryUser));
    printf("username is %s\n", Input.username);
    Input.passwd = gtk_entry_get_text(GTK_ENTRY(entryPW));
    printf("passwd is %s\n", Input.passwd);

    /*connect db*/
    /*********************/
    if(!connect_mysql())
        printf("Connected MySQL successful! \n");
    mysql_close(&mysql);
    /*********************/
}

void change_background(GtkWidget *widget, int w, int h, const gchar *path)
{
    //1.允许窗口可以绘图
    gtk_widget_set_app_paintable(widget, TRUE);
    gtk_widget_realize(widget);

    /* 更改背景图时，图片会重叠 
	* 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。 
	*/
    gtk_widget_queue_draw(widget);
    GdkPixbuf *src = gdk_pixbuf_new_from_file(path, NULL);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, w, h, GDK_INTERP_BILINEAR);

    /* 创建pixmap图像;  
	* NULL：不需要蒙版;  
	* 123： 0~255，透明到不透明 
	*/
    GdkPixmap *pixmap = NULL;
    gdk_pixbuf_render_pixmap_and_mask(dst, &pixmap, NULL, 255);

    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASL
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

    g_object_unref(src);
    g_object_unref(dst);
    g_object_unref(pixmap);

    return;
}

int UI(char *name)
{
    GtkWidget *window; //定义窗口
    GtkWidget *button; //定义按钮
    GtkWidget *table;  //定义table
    GtkWidget *image;  //image
    GtkWidget *frame;  //frame
    GtkWidget *label;  //label
    GtkWidget *check;  //check

    gtk_init(NULL, NULL); //初始化

    /*窗口初始化*/
    /*********************/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);       //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(window), name);     //设置标题
    gtk_widget_set_size_request(window, WIDTH, HEIGHT); //设置大小
    // gtk_window_set_default_size(GTK_WINDOW(window),WIDTH,HEIGHT);    //设置大小
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //设置窗口位置
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);        //设置窗口边框宽度
    // change_background(window, WIDTH, HEIGHT*1.5, "./image/bj.jpg");  //设置窗口背景图片
    // image=gtk_image_new_from_file("./image/bj2.PNG");
    // gtk_container_add(GTK_CONTAINER(window),image);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //事件监听，检测用户关闭windows时窗口关闭
    /*********************/

    /*control window widget -->frame*/
    frame = gtk_frame_new("");
    gtk_container_add(GTK_CONTAINER(window), frame);

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

    /*登陆按钮*/
    /*********************/
    button = gtk_button_new_with_label("登陆");
    // g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),window);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 11, 17, 14, 15);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(callBack), NULL);
    gtk_widget_show(button); //显示按钮
    /*********************/

    /*退出按钮*/
    /*********************/
    button = gtk_button_new_with_label("退出系统");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(delete_event), window);
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
    gtk_widget_show_all(window); //显示窗口(all)
    gtk_main();                  //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生

    return FALSE;
}

int main()
{
    char *name = "Company Attendance System";
    UI(name);
}