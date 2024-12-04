#include <gtk/gtk.h>
#define gb(s) gtk_builder_get_object(builder, s)
#define gte(s) gtk_entry_get_text(s)

GtkBuilder *builder;

//Items do login
GtkWidget *JanelaLogin;
GtkEntry *Ent_Usr; GtkEntry *Ent_PIN; GtkLabel *LgnInc;

//Items da janela principal
GtkWidget *JanelaPrincipal;
GtkWidget *PrincFixed; GtkWidget *Cabecalho; GtkWidget *Planilha;

//Items da janela de gerenciar conta
GtkWidget *JanelaGerenciamento;
GtkEntry *Ent_APin; GtkEntry *Ent_NPin; GtkEntry *Ent_NUsr; GtkEntry *Ent_NUPin;

//Items da janela de filtros
GtkWidget *JanelaFiltros;
GtkEntry *F_Ma;GtkEntry *F_Mo;GtkEntry *F_No;GtkEntry *F_De; GtkEntry *F_Ti;
GtkEntry *F_NS;GtkEntry *F_NP;GtkEntry *F_Al;GtkEntry *F_St;




#include "fncs.h"
//Incluindo headers para gerenciar cada janela
#include "login.h"
#include "princ.h"
#include "gercn.h"
#include "filtros.h"

int main(int argc, char *argv[]) {

    reg_users();

    gtk_init(&argc, &argv);

    //Declarando o builder
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "estoque.glade", NULL);

    //Items do login
    JanelaLogin = GTK_WIDGET(gb("JanelaLogin")); //gtk_window_set_resizable(JanelaLogin, FALSE);
    Ent_Usr = GTK_ENTRY(gb("EntradaUsuario"));
    Ent_PIN = GTK_ENTRY(gb("EntradaPIN"));
    LgnInc = GTK_LABEL(gb("LoginIncorreto"));

    // Items da janela principal

    JanelaPrincipal = GTK_WIDGET(gb("JanelaPrincipal"));
    Planilha = GTK_WIDGET(gb("Planilha"));
    PrincFixed = GTK_WIDGET(gb("PrincFixed"));
    Cabecalho = criar_cabecalho();

    // Items do gerenciamento de conta
    JanelaGerenciamento = GTK_WIDGET(gb("JanelaGerenciamento"));
    Ent_APin = GTK_ENTRY(gb("Ent_APin"));
    Ent_NPin = GTK_ENTRY(gb("Ent_NPin"));
    Ent_NUsr = GTK_ENTRY(gb("Ent_NUsr"));
    Ent_NUPin = GTK_ENTRY(gb("Ent_NUPin"));

    // Items da janela de filtros
    JanelaFiltros = GTK_WIDGET(gb("JanelaFiltros"));
    F_Ma = GTK_ENTRY(gb("F_Ma"));
    F_Mo = GTK_ENTRY(gb("F_Mo"));
    F_No = GTK_ENTRY(gb("F_No"));
    F_De = GTK_ENTRY(gb("F_De"));
    F_Ti = GTK_ENTRY(gb("F_Ti"));
    F_NS = GTK_ENTRY(gb("F_NS"));
    F_NP = GTK_ENTRY(gb("F_NP"));
    F_Al = GTK_ENTRY(gb("F_Al"));
    F_St = GTK_ENTRY(gb("F_St"));



    gtk_fixed_put(GTK_FIXED(PrincFixed), Cabecalho, 0, 280);
    carregarDados(nomeArquivoPlanilha);
    aplicarFiltros();
    // gtk_widget_show_all(JanelaPrincipal); // para testar

    g_signal_connect(JanelaGerenciamento, "delete-event", G_CALLBACK(on_gercn_del), NULL);
    g_signal_connect(JanelaFiltros, "delete-event", G_CALLBACK(fechar_filtro), NULL);
    gtk_builder_connect_signals(builder, NULL); // conecta todos os sinais do glade

    g_object_unref(builder);
    gtk_widget_show(JanelaLogin); // abre a tela de login
    gtk_main();

    return 0;
}

