#include <gtk/gtk.h>
// #include"sungtk_interface.h"
/************************自定义列表************************************/
//每一行点击时的回调函数类型
typedef gboolean (*SunGtkSelectRow)(GtkWidget *widget, GdkEventButton *event, gpointer data);
 
//为列表创建的链表的结构体
typedef struct _clist_link
{
 GtkWidget *event_box; //每一行都有一个事件盒子，用于支持点击
 GtkWidget *label;  //将label放置在事件盒子中，用于显示文字
 struct _clist_link *next;
}CListLink;
 
//整个列表的结构体
typedef struct _sungtk_clist
{
 GtkWidget *fixed;  //整个列表是一个固定布局
 GtkWidget *vbox;  //利用垂直布局，可以动态追加行
 gint select_row;  //当前选中行
 gint font_size;   //字体大小
 gchar font_color[30]; //字体颜色
 gint row_height;  //每行的高度
 gint col_width;   //每行宽度
 gint total_num;   //行总数
 gchar sig_str[30];  //信号
 SunGtkSelectRow callback;//行点击回调函数
 CListLink *head;
}SunGtkCList;
 
#define SUNGTK_CLIST(x) (SunGtkCList *)x 
 
//自定义列表创建
extern SunGtkCList *sungtk_clist_new();
 
//列表释放资源
extern int sungtk_clist_unref(SunGtkCList *clist);
 
//追加一行
extern int sungtk_clist_append(SunGtkCList *clist, const gchar *text);
 
//设置前景颜色
extern int sungtk_clist_set_foreground(SunGtkCList *clist, const gchar *color_buf);
 
//设置其中一行的颜色
extern int sungtk_clist_set_row_color(SunGtkCList *clist, gint row, const gchar *color_buf);
 
//选中某一行
extern int sungtk_clist_select_row(SunGtkCList *clist, gint row, const gchar *color_buf);
 
//设置行高度
extern int sungtk_clist_set_row_height(SunGtkCList *clist, gint height);
 
//设置列宽度
extern int sungtk_clist_set_col_width(SunGtkCList *clist, gint width);
 
//设置字体大小
extern int sungtk_clist_set_text_size(SunGtkCList *clist, int size);
 
//获取某一行内容
extern const gchar *sungtk_clist_get_row_data(SunGtkCList *clist, gint row);
 
//设置某一行内容
extern int sungtk_clist_set_row_data(SunGtkCList *clist, gint row, const gchar *text);
 
//设置点击行的信号
extern int sungtk_clist_set_select_row_signal(SunGtkCList *clist, const gchar *detailed_signal, SunGtkSelectRow callback);
 
//设置整个列表行在固定布局的位置
extern void sungtk_clist_set_position_in_fixed(SunGtkCList *clist, gint x, gint y);
 
 
SunGtkCList *list = NULL;
 
static gboolean callback_list_release(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	int row = (int)data;
	printf("row===%d\n", row);
	
	const char *text = sungtk_clist_get_row_data(list, row);
	printf("text==%s==\n", text);
	return TRUE;
}
 
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
 
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow *)window, "Hello");
	gtk_widget_set_size_request(window, 400,300);
	
	GtkWidget *table = gtk_table_new(5, 5, TRUE);
	gtk_container_add(GTK_CONTAINER(window), table);
 
	list = sungtk_clist_new();
	sungtk_clist_set_row_height(list, 40);
	sungtk_clist_set_col_width(list, 200);
	sungtk_clist_set_text_size(list, 13);
	sungtk_clist_set_select_row_signal(list, "button-release-event", callback_list_release);
	gtk_table_attach_defaults(GTK_TABLE(table), list->fixed, 1, 4, 1, 5);
	
	sungtk_clist_append(list, "aaaaaaaaaaa");
	sungtk_clist_append(list, "bbbbbbbbbb");
	
	sungtk_clist_set_row_color(list, 0, "red");
	
 
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
 
 