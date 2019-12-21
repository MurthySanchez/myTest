#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "UI.h"
/*UI界面最新进展
 * 窗口搭建完成
 * 退出按钮ok
 * 
 * */

void delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data )
{ 
    g_print ("user clicked exit\n");
    gtk_main_quit();
  
}

int UI(char name[]){
    GtkWidget* window;//定义窗口
    GtkWidget* button;//定义按钮
    GtkWidget* table;//定义table
    gtk_init(NULL,NULL);//初始化

    /*窗口初始化*/
    /*********************/
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL); //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(window),name);   //设置标题
    gtk_window_set_default_size(GTK_WINDOW(window),846,600);    //设置大小4134x5846
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); //设置窗口位置
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);    //设置窗口边框宽度
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);//事件监听，检测用户关闭windows时窗口关闭
    /*********************/

    table=gtk_table_new(19,27,TRUE);
    gtk_container_add(GTK_CONTAINER(window),table);

    /*退出按钮*/
    /*********************/
    button=gtk_button_new_with_label("exit");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_event),window);
    gtk_table_attach_defaults(GTK_TABLE(table),button,23,25,16,17);
    gtk_widget_show(button);   //显示按钮
    /*********************/

    gtk_widget_show(table);
    gtk_widget_show(window);    //显示窗口
    gtk_main(); //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生

    return FALSE;
}

int main(){
    char name[50]="Company Attendance System";
    UI(name);
}