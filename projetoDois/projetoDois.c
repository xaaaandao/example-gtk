#include <gtk/gtk.h>
#include <stdlib.h>

GtkLabel *resultado;
GtkEntry *peso;
GtkEntry *altura;

void on_botao_clicked(GtkWidget *widget, gpointer data){
    const gchar *peso_str = gtk_entry_get_text(peso);
    const gchar *altura_str = gtk_entry_get_text(altura);

    float peso_f = atof(peso_str);
    float altura_f = atof(altura_str);

    float imc = peso_f / (altura_f * altura_f);

    char text[] = "SEU IMC É: ";
    char result[20];

    // concatena as string
    g_snprintf(result, 20, "%s%.2f", text, imc);
    gtk_label_set_text(resultado, result);

}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    // encerra aplicação
    gtk_main_quit();
}

int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("projetoDois.glade");

    gtk_builder_add_callback_symbols(builder,
                                    "on_botao_clicked", G_CALLBACK(on_botao_clicked),
                                    "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
                                    NULL);
    
    gtk_builder_connect_signals(builder, NULL);
    
    resultado = GTK_LABEL(gtk_builder_get_object(builder, "resultado"));
    peso = GTK_ENTRY(gtk_builder_get_object(builder, "peso"));
    altura = GTK_ENTRY(gtk_builder_get_object(builder, "altura"));
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}