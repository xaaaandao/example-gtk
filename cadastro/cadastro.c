#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

typedef struct usuario{
    int id;
    char nome[100];
    char email[100];
    struct usuario *proximo;
} user;

int id = 0;
user *cabecalho_user;
user *proximo_user;

void mensagem(char text[100], char secondary_text[100], char icon_name[100]){
    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "mensagem"));

    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", secondary_text, NULL);
    g_object_set(mensagem_dialogo, "icon_name", icon_name, NULL);

    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(GTK_DIALOG(mensagem_dialogo));
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));
}

void on_button_listar_inicial_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack, "view_listar");
}

void on_button_sair_inicial_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack, "view_login");  
    g_object_set(window, "icon_name", "changes-prevent", NULL);
}

void on_button_cad_voltar_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_button_listar_voltar_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_button_cadastrar_clicked(GtkWidget *widget, gpointer data){
    const char *cad_nome = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "cad_nome")));
    const char *cad_email = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "cad_email")));
    /*
    char cad_nome_c[100];
    char cad_email_c[100];
    
    sprintf(cad_nome_c, "%s", cad_nome);
    sprintf(cad_email_c, "%s", cad_email);
    */
    if(strcmp(cad_nome, "") == 0){
        mensagem("Aviso", "campo nome obrigatório!", "dialog-error");
    } else {
        proximo_user->id = id;
        id++;
        strcpy(proximo_user->nome, cad_nome);
        strcpy(proximo_user->email, cad_email);

        g_print("%d, %s, %s", proximo_user->id, proximo_user->nome, proximo_user->email);

        char texto[100];
        g_snprintf(texto, 100, "%s%s%s", "usuario ", proximo_user->nome, " cadastrado");
        mensagem("Aviso", texto, "dialog-emblem-default");
        
        proximo_user -> proximo = (user*) malloc(sizeof(user));
        proximo_user = proximo_user -> proximo;
    }
}

void on_button_listar_clicked(GtkWidget *widget, gpointer data){
    proximo_user -> proximo = NULL;
    proximo_user = cabecalho_user;

    GtkTreeIter iter;
    //modelo_armazenamento = gtk_list_store_new(3, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_clear(modelo_armazenamento);

    while(proximo_user->proximo != NULL){

        g_print("%d, %s, %s", proximo_user->id, proximo_user->nome, proximo_user->email);

        gtk_list_store_append(modelo_armazenamento, &iter);
        gtk_list_store_set(modelo_armazenamento, &iter,
                            0, proximo_user->id,
                            1, proximo_user->nome,
                            2, proximo_user->email,
                            -1);
                     
        proximo_user = proximo_user ->proximo;
    }
}

void login(char *email, char *senha, bool lembrar){
    if((strcmp(email, "admin") == 0) && (strcmp(senha, "admin") == 0)){
        mensagem("Bem vindo", "Usuário logado com sucesso!", "emblem-default");
        // vai pra próxima página
        gtk_stack_set_visible_child_name(stack, "view_inicial");
        g_object_set(window, "icon_name", "avatar_default", NULL);
    } else {
        mensagem("Bem vindo", "Email ou senha incorreto!", "dialog-error");
    }
}

void on_main_window_destroy(GtkWidget *widget, gpointer data){
    // encerra aplicação
    gtk_main_quit();
}

void on_button_login_clicked(GtkWidget *widget, gpointer data){
    // encerra aplicação
    const gchar *email = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "email")));
    const gchar *senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "senha")));
    gboolean lembrar = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "lembrar")));
    
    //g_print("%s", email);
    char email_c[100];
    char senha_c[100];
    int lembrar_i = lembrar;
    bool lembrar_b = lembrar_i;

    // faz a conversão
    sprintf(email_c, "%s", email);
    sprintf(senha_c, "%s", senha);
    
    login(email_c, senha_c, lembrar_b);
}

void on_button_cadastrar_inicial_clicked(GtkWidget *widget, gpointer data){
    gtk_stack_set_visible_child_name(stack, "view_cadastro");
}

int main(int argc, char *argv[]){

    cabecalho_user = (user*) malloc (sizeof(user));
    proximo_user = cabecalho_user;
    

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("cadastro.glade");

    gtk_builder_add_callback_symbols(builder,
                                    "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
                                    "on_button_login_clicked", G_CALLBACK(on_button_login_clicked),
                                    "on_button_cadastrar_inicial_clicked", G_CALLBACK(on_button_cadastrar_inicial_clicked),
                                    "on_button_listar_inicial_clicked", G_CALLBACK(on_button_listar_inicial_clicked),
                                    "on_button_sair_inicial_clicked", G_CALLBACK(on_button_sair_inicial_clicked),
                                    "on_button_cad_voltar_clicked", G_CALLBACK(on_button_cad_voltar_clicked),
                                    "on_button_cadastrar_clicked", G_CALLBACK(on_button_cadastrar_clicked),
                                    "on_button_listar_voltar_clicked", G_CALLBACK(on_button_listar_voltar_clicked),
                                    "on_button_listar_clicked", G_CALLBACK(on_button_listar_clicked),
                                    NULL);
    
    gtk_builder_connect_signals(builder, NULL);
    
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    modelo_armazenamento = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}