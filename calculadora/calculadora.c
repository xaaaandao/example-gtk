#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

GtkEntry *display;
char operacao[100];
float primeiro_numero;
bool limpar_display = FALSE;


float ler_display(){
    const gchar *string = gtk_entry_get_text(display);
    return atof(string);
}

void on_botao_clicked(GtkButton *button, gpointer data){

    if(limpar_display){
        gtk_entry_set_text(display, "0");
        limpar_display = FALSE;
    }

    if(strcmp(gtk_entry_get_text(display), "0") == 0)
        gtk_entry_set_text(display, gtk_button_get_label(button));
    else {
        char texto[100];
        g_snprintf(texto, 100, "%s%s", gtk_entry_get_text(display), gtk_button_get_label(button));
        gtk_entry_set_text(display, texto);
    }
}


void on_botao_divisao_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "divisao");
    primeiro_numero = ler_display();
    limpar_display = TRUE;
}

void on_botao_multiplicacao_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "multiplicacao");
    primeiro_numero = ler_display();
    limpar_display = TRUE;
}

void on_botao_soma_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "soma");
    primeiro_numero = ler_display();
    limpar_display = TRUE;
    // g_print("%s", operacao);
    // g_print("%f", primeiro_numero);
}

void on_botao_subtracao_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "subtracao");
    primeiro_numero = ler_display();
    limpar_display = TRUE;
}

void on_botao_igual_clicked(GtkWidget *widget, gpointer data){
    float segundo_numero = ler_display();
    float resultado_f;

    if(strcmp(operacao, "soma") == 0)  resultado_f = primeiro_numero + segundo_numero;
    if(strcmp(operacao, "subtracao") == 0)  resultado_f = primeiro_numero - segundo_numero;
    if(strcmp(operacao, "multiplicacao") == 0)  resultado_f = primeiro_numero * segundo_numero;
    if(strcmp(operacao, "divisao") == 0)  resultado_f = primeiro_numero / segundo_numero;
    if(strcmp(operacao, "porcentagem") == 0)  resultado_f = (primeiro_numero * segundo_numero) / 100;
    if(strcmp(operacao, "raiz_quadrada") == 0)  resultado_f = sqrt(segundo_numero);

    char resultado[10];
    // Converte o valor
    sprintf(resultado, "%f", resultado_f);
    gtk_entry_set_text(display, resultado);
}

void on_botao_raiz_quadrada_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "raiz_quadrada");
    limpar_display = TRUE;
    
    on_botao_igual_clicked(widget, data);
}

void on_botao_porcentagem_clicked(GtkWidget *widget, gpointer data){
    strcpy(operacao, "porcentagem");
    primeiro_numero = ler_display();
    limpar_display = TRUE;
}

void on_botao_ponto_clicked(GtkWidget *widget, gpointer data){
    char texto[100];
    g_snprintf(texto, 100, "%s%s", gtk_entry_get_text(display), ",");
    gtk_entry_set_text(display, texto);
}

void on_botao_reset_clicked(GtkWidget *widget, gpointer data){
    gtk_entry_set_text(display, "0"); 
}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    // encerra aplicação
    gtk_main_quit();
}

int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("calculadora.glade");

    gtk_builder_add_callback_symbols(builder,
                                    "on_botao_clicked", G_CALLBACK(on_botao_clicked),
                                    "on_botao_raiz_quadrada_clicked", G_CALLBACK(on_botao_raiz_quadrada_clicked),
                                    "on_botao_divisao_clicked", G_CALLBACK(on_botao_divisao_clicked),
                                    "on_botao_reset_clicked", G_CALLBACK(on_botao_reset_clicked),
                                    "on_botao_multiplicacao_clicked", G_CALLBACK(on_botao_multiplicacao_clicked),
                                    "on_botao_subtracao_clicked", G_CALLBACK(on_botao_subtracao_clicked),
                                    "on_botao_soma_clicked", G_CALLBACK(on_botao_soma_clicked),
                                    "on_botao_igual_clicked", G_CALLBACK(on_botao_igual_clicked),
                                    "on_botao_ponto_clicked", G_CALLBACK(on_botao_ponto_clicked),
                                    "on_botao_porcentagem_clicked", G_CALLBACK(on_botao_porcentagem_clicked),
                                    NULL);
    
    gtk_builder_connect_signals(builder, NULL);
    
    display = GTK_ENTRY(gtk_builder_get_object(builder, "display"));
    gtk_entry_set_text(display, "0"); 

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}