#include <gtk/gtk.h>

int main(int argc, char *argv[]){
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("helloWorld.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    // Depois que fechar a aplicação ela vai ser destruída
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}