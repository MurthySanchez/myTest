#include <gtk/gtk.h>
GtkWidget *text_view;
GtkTextBuffer *buffer;
GtkTextIter *Iter;
void button_event(GtkWidget *widget, gpointer *data);
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, 200, 150);
    g_signal_connect(GTK_OBJECT(window),"destroy", G_CALLBACK(gtk_main_quit), NULL);
    box = gtk_vbox_new(FALSE, 0);
    gtk_widget_show(box);
    text_view = gtk_text_view_new(); /*创建文本框构件*/
    gtk_widget_set_request(text_view, 200, 120);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_box_pack_start(GTK_BOX(box), text_view, FALSE, FALSE, 0);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_widget_show(text_view);
    button = gtk_button_new_with_label("确定");
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 5);
    gtk_signal_connect(GTK_OBJECT(button),"clicked", GTK_SIGNAL_FUNC(button_event), NULL);
    gtk_widget_show(window);
    gtk_main();
}
void button_event(GtkWidget *widget, gpointer *data)
{
    gchar *text;
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &start, &end); /*获得缓冲区开始和结束位置的Iter*/
    const GtkTextIter s = start, e = end;
    text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &s, &e, FALSE); /*获得文本框缓冲区文本*/
    g_print("%s\n", text);
}