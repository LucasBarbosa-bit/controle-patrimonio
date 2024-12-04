G_MODULE_EXPORT void criar_conta()
{

}

G_MODULE_EXPORT void mudar_pin()
{

}



G_MODULE_EXPORT void gerenciar_contas()
{
    gtk_widget_show(JanelaGerenciamento);
}

gboolean on_gercn_del(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaGerenciamento);
    return TRUE;
}
