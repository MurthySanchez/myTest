#define GTK_ENABLE_BROKEN
#include<gtk/gtk.h>
#include<stdio.h>
#include"dirent.h"
#include"unistd.h"
#include"sys/file.h"
#include"fcntl.h"
#include"string.h"
#include"time.h"
#include"math.h"
#include<stdlib.h>
#include<sys/time.h>
#include<gdk/gdk.h>
 
#define PMAX     100 //最大进程数目
 
enum//进程界面的枚举类型
{
	NAME_COLUMN,//进程名列
	NP_COLUMNS
};
 
int USER,NICE,SYSTEM,IDLE;
 
char *title=" 进程信息 ";
 
gint s_total = 0;
gint r_total = 0;	
gdouble pfuser[PMAX];
gdouble rate = 0;//cpu 使用率	
 
GtkWidget *window;//主窗口
GtkWidget *notebook;//notebook控件
GtkWidget *vbox;
GtkWidget *hbox;
 
GtkWidget *label;
GtkWidget *mem_bar;
GtkWidget *cpu_bar;
GtkWidget *swap_bar;
 
GtkWidget *info_label;
GString   *info;
GtkWidget *status_bar0;
GtkWidget *mem_label;
GtkWidget *swap_label;
 
GtkWidget *scrolled_window;
 
GtkListStore *process_store;
 
GtkWidget *ptree_view;
 
GtkCellRenderer *renderer;//用于显示tree view中的每个列标题
GtkCellRenderer *drenderer;
GtkCellRenderer *mrenderer;
GtkTreeViewColumn *column;//tree view控件列数
GtkTreeViewColumn *dcolumn;
GtkTreeViewColumn *mcolumn;
GtkWidget *pdelete_button; //刷新进程按钮和结束进程按钮
GtkWidget *main_vbox;
GtkWidget *bbvbox;
 
 
GtkWidget *table;
 
GtkWidget *table1;//定义表格
 
GtkWidget *frame;//定义框架
 
GtkWidget *frame0;
 
 
GtkWidget *button[6],*cpu_rate_label,*process_label,*mem_rate_label,*swap_rate_label,*time_label,*s_label,*r_label,*uptime_label;//定义标签
 
gint length;
 
GtkWidget *CreateMenuItem(GtkWidget *,char *);//创建菜单项函数
 
GtkWidget *CreateMenuFile(GtkWidget *);//创建菜单File函数
 
GtkWidget *CreateMenuShutDown(GtkWidget *);//创建菜单Shutdown函数
 
GtkWidget *CreateMenuHelp(GtkWidget *);//创建菜单Help函数
 
void show_dialog (gchar *, gchar *);
void get_cpu_info (GString *);
void draw_cpu_load_graph (void);
void draw_mem_load_graph (void);
 
gint uptime(void);//计算系统开机时间和运行时间
 
gint mem_timeout(void);//
 
gint pro_timeout(void);//
 
gint sys_time(void);//计算系统时间
 
void get_process_info (GtkListStore *);
void get_disk_info (GtkListStore *);
void prefresh_button_clicked2 (gpointer data);
void pdelete_button_clicked (gpointer data);
 
void notebook_pro_init(void);//进程页面初始化
 
int select_name(char name[]){
	int i;
	for(i=0;name[i]!=0;i++)
		if(isalpha(name[i])||name[i]=='.')
		return 0;
	return 1;
}
 
/*回调函数，退出窗口管理程序*/
void delete_event(GtkWidget *window,gpointer data){
	gtk_main_quit();
}
 
/*回调函数，重启*/
void restart(GtkWidget *window,gpointer data){
	system("reboot");
}
 
/*回调函数，关机*/
void shutdown(GtkWidget *window,gpointer data){
	system("halt");
}
 
static gboolean scan_window(gpointer data)
{
  	GtkTreeSelection *selection;
  	GtkTreeModel *model;
	gchar *pid;
	gboolean valid;
	GtkTreeIter iter;
	GtkTreeIter selected_iter;
 
  	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(ptree_view));//获得当前选择的项
	if (gtk_tree_selection_get_selected(selection, &model, &iter))  {
		gtk_tree_model_get (model, &iter, NAME_COLUMN, &pid, -1);//在树的相应列中获得该进程的PID
		gtk_list_store_clear (process_store);
		get_process_info (process_store);	
		valid = gtk_tree_model_get_iter_first(model, &iter);
		while (valid) {
			GValue value = G_VALUE_INIT;
			model = gtk_tree_view_get_model(ptree_view);
			gtk_tree_model_get_value(model, &iter, NAME_COLUMN, &value);
			if (!strcmp(pid, g_value_get_string(&value))) {
				selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(ptree_view));
				gtk_tree_selection_select_iter(selection, &iter);
				return TRUE;
			}
			valid = gtk_tree_model_iter_next(model, &iter);
		}
	}
	gtk_list_store_clear (process_store);
	get_process_info (process_store);	
 
	return TRUE;
}
 
/*主函数*/
int main(int argc,char *argv[]){
	gint i;
	int v,v0;
	int timer;
	GtkWidget *label2,*label;
	GtkWidget *label0;
	GtkWidget *text;
	gpointer date,data;
	gdouble value1,value2;
	gpointer gdata;
	GtkWidget *label3;
	GtkWidget *button1;
	GtkWidget *vscrollbar,*hscrollbar;//定义滚动条
	GtkWidget *MenuBar;//定义菜单栏
	GtkWidget *MenuItemFile,*MenuItemShutDown,*MenuItemHelp;
    
	gtk_init(&argc,&argv);//在任何构件生成之前完成
 	memset (pfuser, 0 ,sizeof (pfuser));
 
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//创建主窗口
	gtk_window_set_title(GTK_WINDOW(window),"任务管理器");//设置窗口标题
	gtk_widget_set_usize(window, 600, 500);//设置窗口大小 
	gtk_window_set_resizable (GTK_WINDOW (window), TRUE);// 窗口大小可改变（TRUE）
	gtk_container_set_border_width(GTK_CONTAINER(window), 0);//设置窗口边框宽度
	gtk_widget_show(window);
 
	table=gtk_table_new(12,11,TRUE);//创建表格12行*10列
	gtk_widget_show(table);
	gtk_container_add(GTK_CONTAINER(window),table);//将table装进窗口 
 
	table1=gtk_table_new(14, 11,TRUE);//创建表格12行*10列
	gtk_widget_show(table1);
 
	notebook=gtk_notebook_new();//创建notebook
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);//设置notebook的格式
	gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 11, 1, 11);//将notebook加入表格中
	gtk_widget_show(notebook);
	label0=gtk_label_new(title);//notebook页面标题           
 
	gtk_widget_show (label0);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table1, label0);
 
	uptime_label=gtk_label_new("");//
 
	MenuBar=gtk_menu_bar_new();//创建菜单栏
	gtk_table_attach_defaults(GTK_TABLE(table),MenuBar,0,11,0,1);//将菜单栏加入表格
	MenuItemFile=CreateMenuItem(MenuBar,"文件");//增加菜单项
  	CreateMenuFile(MenuItemFile);//调用创建根菜单项函数
  	MenuItemShutDown=CreateMenuItem(MenuBar,"关机选项");//增加菜单项
	CreateMenuShutDown(MenuItemShutDown);//调用创建根菜单项函数
   	gtk_widget_show(MenuBar);
 
	notebook_pro_init();//进程页面初始化
 
   	gtk_signal_connect(GTK_OBJECT(window),"delete_event",GTK_SIGNAL_FUNC(delete_event),NULL);
 
 	gtk_main();
 
}
 
/*创建菜单项*/
GtkWidget *CreateMenuItem(GtkWidget *MenuBar,char *test){
    	GtkWidget *MenuItem;
    	MenuItem=gtk_menu_item_new_with_label(test);//创建根菜单项
   	gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar),MenuItem);//把根菜单和菜单栏连在一起
  	gtk_widget_show(MenuItem);//显示根菜单
    	return MenuItem;
}
 
/*创建文件菜单*/
GtkWidget *CreateMenuFile(GtkWidget *MenuItem){
     	GtkWidget *Menu;//定义根菜单
    	GtkWidget *Exit;
   	Menu=gtk_menu_new();//创建菜单
   	Exit=CreateMenuItem(Menu,"退出");//调用创建根菜单函数
    	gtk_signal_connect(GTK_OBJECT(Exit),"activate",GTK_SIGNAL_FUNC(delete_event),NULL);//关于delete_event的回调函数
    	gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem),Menu);//把根菜单项和根菜单绑定起来
    	gtk_widget_show(Menu);
}
 
/*创建关机选项菜单*/
GtkWidget *CreateMenuShutDown(GtkWidget *MenuItem){
     	GtkWidget *Menu;//定义菜单根
     	GtkWidget *Restart,*ShutDown,*LogOut;
    	Menu=gtk_menu_new();//创建根菜单
   	ShutDown=CreateMenuItem(Menu,"关机");//调用创建根菜单函数
    	Restart=CreateMenuItem(Menu,"重启");
    	gtk_signal_connect(GTK_OBJECT(Restart),"activate",GTK_SIGNAL_FUNC(restart),NULL);    
    	gtk_signal_connect(GTK_OBJECT(ShutDown),"activate",GTK_SIGNAL_FUNC(shutdown),NULL);
  	gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuItem),Menu);//把父菜单项于子菜单联系起来
    	gtk_widget_show(Menu);
}
 
/*进程页面初始化*/
void notebook_pro_init(void){
	int i;
  	gchar *col_name = "进程名";
	GtkWidget *frame;
 
	frame=gtk_frame_new(NULL);//页面框架
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);//框架与边缘的距离
	gtk_frame_set_shadow_type (GTK_FRAME (frame),GTK_SHADOW_ETCHED_OUT);//框架的阴影模式
	gtk_widget_set_size_request(frame,450,450);//框架大小
	gtk_widget_show(frame);
 
  	scrolled_window = gtk_scrolled_window_new (NULL, NULL);//添加滚动窗口控件
  	gtk_widget_set_size_request (scrolled_window, 300, 300);
	gtk_scrolled_window_set_policy(scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  	gtk_widget_show (scrolled_window);
  	gtk_container_add (GTK_CONTAINER (frame), scrolled_window);//将进程信息树加到滚动窗口中
	gtk_table_attach_defaults (GTK_TABLE (table1), frame, 0, 14, 0, 12);//将notebook加入表格中
	
	//进程信息
  	process_store = gtk_list_store_new (NP_COLUMNS, G_TYPE_STRING);
  
  	ptree_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (process_store));  
  	//添加tree view控件，显示进程信息树
 
  	g_object_unref (G_OBJECT (process_store));//减少引用次数
 
 
  	gtk_widget_show (ptree_view);
  	gtk_container_add (GTK_CONTAINER (scrolled_window), ptree_view);//将进程信息树加到滚动窗口中
  
  
	renderer = gtk_cell_renderer_text_new ();//添加一个cell_renderer_text用于显示文字
  	column = gtk_tree_view_column_new_with_attributes (col_name,renderer,"text", 0,NULL);//新建一列		
	gtk_tree_view_append_column (GTK_TREE_VIEW (ptree_view), column);//将该列加到树中	
	gtk_tree_view_columns_autosize(ptree_view);
  
  	pdelete_button = gtk_button_new ();//创建杀死进程按钮
  	gtk_widget_show (pdelete_button);
  	gtk_widget_set_size_request (pdelete_button, 60, 30);
  	gtk_button_set_label (GTK_BUTTON (pdelete_button), "结束进程");
  	g_signal_connect (G_OBJECT (pdelete_button),"clicked",G_CALLBACK(pdelete_button_clicked),NULL);//该按钮点击后执行pdelete_button_clicked 
	gtk_table_attach_defaults (GTK_TABLE (table1), pdelete_button, 6, 8, 12, 13);//将notebook加入表格中
 
  	get_process_info (process_store);
	g_timeout_add(1000, scan_window, NULL);
}
 
/*获得进程相关信息的函数*/
void get_process_info (GtkListStore *store){
	FILE *fp;
	char buffer[1024];
	char host_name[1024];
  	gchar *info;
  	GtkTreeIter iter;
 
  	s_total = 0;
  	r_total = 0;  
 
	system("wmctrl -l > /tmp/NacvBQWR");
	fp = fopen("/tmp/NacvBQWR", "r");
	gethostname(host_name, sizeof(host_name));
	while (fgets(buffer, sizeof(buffer), fp) > 0) {
		info = strstr(buffer, host_name);
		info = info + strlen(host_name) + 1;
		if (!strcmp(info, "桌面\n")) 
			continue;
		char *p = info;
		while (*p != '\n')
			p++;
		*p = '\0';
		gtk_list_store_append (store, &iter);//增加到列表
		gtk_list_store_set (store, &iter, NAME_COLUMN, info, -1);
	}
	fclose(fp);
}
 
/*进程杀死按钮处理函数*/
void pdelete_button_clicked (gpointer data){//kill按钮被点击，停止一个进程的运行
  	GtkTreeSelection *selection;
  	GtkTreeModel *model;
  	GtkTreeIter iter;
  	gchar *pid;
  	pid_t pid_num;
	gchar cmd[256] = "wmctrl -c ";
 
  	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(ptree_view));//获得当前选择的项
  	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
		gtk_tree_model_get (model, &iter, NAME_COLUMN, &pid, -1);//在树的相应列中获得该进程的PID
		if (pid == NULL)
			return;
		strcat(cmd, pid);
		system(cmd);
	    gtk_list_store_clear (process_store);//刷新进程信息
	    get_process_info (process_store);	
  	}
}
 
/*显示一个对话框，标题title，内容为content*/
void show_dialog (gchar *title, gchar *content){
	GtkWidget *dialog;
	GtkWidget *label;
        dialog = gtk_dialog_new_with_buttons (title,
                                         GTK_WINDOW (window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_CLOSE,
                                         GTK_RESPONSE_NONE,
                                         NULL);//创建一个对话框构件
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);//不可改变大小
	g_signal_connect_swapped (dialog,
                             "response", 
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);//事件回调函数为退出	
	
	label = gtk_label_new (content);//创建一个标签，显示content的内容
	gtk_widget_show (label);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                      label);			  
	gtk_widget_show (dialog);
}