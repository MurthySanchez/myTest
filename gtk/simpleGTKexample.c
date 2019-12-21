#include "gtk/gtk.h"                           //必须引用gtk/gtk.h这个头文件
int main(int argc,char *argv[])                //标准c语言主函数的声明
{
    GtkWidget *window;                        //声明一个窗口控件的指针，其中GtkWidget是gtk+2.0控件类型。window是变量名，与变量类型无关
    
    gtk_init(&argc,&argv);                    //初始化gtk+环境，在gtk+程序中是必须的
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /*用来创建窗口。函数gtk_window_new 创建一个窗口并返回这个窗口的控件指针,这里把指针的值赋给了window这个变量；参数GTK_WINDOW_TOPLEVEL指明窗口的类型为最上层的主窗口，还有一个参数GTK_WINDOW_POPUP指明窗口类型为弹出式无边框窗口*/
    
    gtk_window_set_title(GTK_WINDOW(window),"hello World");//给window窗口设置标题

    gtk_window_set_default_size(GTK_WINDOW(window),400,500);//给window窗口设置大小
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    /*事件监听函数，意思是，对于对象window，当"destroy"时间发生的时候，调用gtk_main_quit函数，传递这个函数的参数为NULL，也就是当你点击窗口关闭按钮的时候，结束程序*/

    gtk_widget_show(window);        //显示上一步创建的窗口
    
    gtk_main();
    /*这个函数是最关键的，它是gtk+2.0的主事件循环，每个gtk+2.0程序都要有一个否则程序无法运行*/
    return FALSE;
    /*代码最后的逻辑返回值为FALSE它相当于整型的0。*/
}
