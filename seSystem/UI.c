#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "UI.h"
/*UI界面最新进展
 * 窗口搭建完成
 * 退出按钮ok
 * 设置窗口为19*27的格子
 *  添加系统logo 大小：125*89p
 * 添加label用户名，密码
 * */

void delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data )
{ 
    g_print ("user clicked exit\n");
    gtk_main_quit();
  
}

void enter_callback( GtkWidget *widget, GtkWidget *entry )
{
   const gchar *entry_text;
   entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
   printf("Entry contents: %s\n", entry_text);
}

// 鼠标移动事件(点击鼠标任何键)的处理函数
gboolean deal_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
	// 获得移动鼠标的坐标值，距离窗口左顶点
	gint i = event->x;
	gint j = event->y;
	printf("motion_x = %d, motion_y = %d\n", i, j);
	
	return TRUE;
}

int UI(char* name){
    GtkWidget* window;//定义窗口
    GtkWidget* button;//定义按钮
    GtkWidget* table;//定义table
    GtkWidget* image;//image
    GtkWidget* frame;//frame
    GtkWidget* label;//label
    GtkWidget* entry;//entry
    gtk_init(NULL,NULL);//初始化

    /*窗口初始化*/
    /*********************/
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL); //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(window),name);   //设置标题
    gtk_window_set_default_size(GTK_WINDOW(window),846,600);    //设置大小
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); //设置窗口位置
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);    //设置窗口边框宽度
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);//事件监听，检测用户关闭windows时窗口关闭
    /*********************/

    table=gtk_table_new(19,27,TRUE);
    gtk_container_add(GTK_CONTAINER(window),table);

    /*logo*/
    /*********************/
    image=gtk_image_new_from_file("./image/icon.png");
    gtk_table_attach_defaults(GTK_TABLE(table),image,9,19,3,7);
    gtk_widget_show(image);
    /*********************/

    /*frame for 用户名*/
    /*********************/
    // frame=gtk_frame_new("");
    label=gtk_label_new("用户名");
    // gtk_container_add(GTK_CONTAINER(frame),label);
    gtk_table_attach_defaults(GTK_TABLE(table),label,9,11,9,10);

    entry=gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (G_OBJECT (entry), "activate", G_CALLBACK (enter_callback), entry);
    gtk_table_attach_defaults(GTK_TABLE(table),entry,12,19,9,10);
    /*********************/

    /*frame for 密码*/
    /*********************/
    // frame=gtk_frame_new("");
    label=gtk_label_new("密码");
    // gtk_container_add(GTK_CONTAINER(frame),label);
    gtk_table_attach_defaults(GTK_TABLE(table),label,9,11,11,12);

    entry=gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    // g_signal_connect (G_OBJECT (entry), "activate", G_CALLBACK (enter_callback), entry);
    gtk_entry_set_visibility(GTK_ENTRY(entry),FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),entry,12,19,11,12);

    image=gtk_image_new_from_file("./image/eye.png");
    // gtk_entry_set_icon_activatable(GTK_ENTRY(entry),"./image/eye.png",TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table),image,19,20,11,12);
    gtk_widget_add_events(image, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_MOTION_MASK);
    g_signal_connect(image,"motion-notify-event",G_CALLBACK(deal_motion_notify_event),image);
    gtk_widget_show(image);
    /*********************/

    /*登陆按钮*/
    /*********************/
    button=gtk_button_new_with_label("登陆");
    // g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),window);
    gtk_table_attach_defaults(GTK_TABLE(table),button,11,17,13,14);
    gtk_widget_show(button);   //显示按钮
    /*********************/

    /*退出按钮*/
    /*********************/
    button=gtk_button_new_with_label("退出系统");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),window);
    gtk_table_attach_defaults(GTK_TABLE(table),button,23,25,16,17);
    gtk_widget_show(button);   //显示按钮
    /*********************/

    gtk_widget_show(table);
    gtk_widget_show_all(window);    //显示窗口(all)
    gtk_main(); //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生

    return FALSE;
}

int main(){
    char* name="Company Attendance System";
    UI(name);
}