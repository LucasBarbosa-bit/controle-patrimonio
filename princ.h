G_MODULE_EXPORT void princ_destroy()
{
    gtk_main_quit();
}

G_MODULE_EXPORT void sair_princ()
{
    gtk_widget_hide(JanelaPrincipal);
    gtk_widget_show(JanelaLogin);
}


GtkWidget* criar_cabecalho(){
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(box, 1280, 40);

    const char *slot_texts[9] = {
        "Tipo",
        "Marca",
        "Modelo",
        "Descricao",
        "Novo",
        "N. Serie",
        "N. Patrimonio Poli-UPE",
        "Alocacao",
        "Status"
    };

    for (int i = 0; i < 9; i++) {
        GtkWidget *label = gtk_label_new(slot_texts[i]);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        gtk_widget_set_size_request(label, tamanhos[i], 40);  //
        gtk_widget_show(label);
    }
    gtk_widget_show(box);


    return box;
}


