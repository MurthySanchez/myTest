#include "gtk/gtk.h"
#include "stdio.h"
#include "stdlib.h"
#include "UI.h"
/*UI界面最新进展
 * 窗口搭建完成
 * 下一步：
 *          添加输入框
 * */

gint delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data )
{
    /* 如果你的 "delete_event" 信号处理函数返回 FALSE，GTK 会发出 "destroy" 信号。
     * 返回 TRUE，你不希望关闭窗口。
     * 当你想弹出“你确定要退出吗?”对话框时它很有用。*/
 
    g_print ("delete event occurred\n");
 
    /* 改 TRUE 为 FALSE 程序会关闭。*/
 
    return FALSE;
}

int UI(char name[]){
    GtkWidget* window;//定义窗口
    GtkWidget* btn_cls;//定义按钮

    gtk_init(NULL,NULL);//初始化

    /*窗口初始化*/
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL); //创建一个置顶窗口
    gtk_window_set_title(GTK_WINDOW(window),name);   //设置标题
    gtk_window_set_default_size(GTK_WINDOW(window),750,550);    //设置大小
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); //设置窗口位置

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);//事件监听，检测用户关闭windows时窗口关闭

    gtk_widget_show(window);    //显示窗口

    /*按钮初始化*/
    btn_cls=gtk_button_new_with_label("exit");
    g_signal_connect_swapped(G_OBJECT(btn_cls),"cliked",G_CALLBACK(delete_event),window);   //点击弹出退出
    gtk_container_add(GTK_CONTAINER(window),btn_cls);   //将btn加入
    gtk_widget_show(btn_cls);   //显示按钮

    gtk_main(); //gtk+2.0等待事件(如键盘事件或鼠标事件) 的发生

    return FALSE;
}

int main(){
    char name[50]="Company Attendance System";
    UI(name);
}