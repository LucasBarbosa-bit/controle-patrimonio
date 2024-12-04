
gboolean fechar_filtro(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_widget_hide(JanelaFiltros);
    return TRUE;
}

G_MODULE_EXPORT void abrir_filtros()
{
    gtk_widget_show(JanelaFiltros);
}

//    F_Ma = GTK_ENTRY(gb("F_Ma"));
//    F_Mo = GTK_ENTRY(gb("F_Mo"));
//    F_No = GTK_ENTRY(gb("F_No"));
//    F_De = GTK_ENTRY(gb("F_De"));
//    F_Ti = GTK_ENTRY(gb("F_Ti"));
//    F_NS = GTK_ENTRY(gb("F_NS"));
//    F_NP = GTK_ENTRY(gb("F_NP"));
//    F_Al = GTK_ENTRY(gb("F_Al"));
//    F_St = GTK_ENTRY(gb("F_St"));
//        "Tipo",
//        "Marca",
//        "Modelo",
//        "Descricao",
//        "Novo",
//        "N. Serie",
//        "N. Patrimonio Poli-UPE",
//        "Alocacao",
//        "Status"

G_MODULE_EXPORT void click_filtros()
{
    strcpy(filtros[0], gte(F_Ti));
    strcpy(filtros[1], gte(F_Ma));
    strcpy(filtros[2], gte(F_Mo));
    strcpy(filtros[3], gte(F_De));
    strcpy(filtros[4], gte(F_No));
    strcpy(filtros[5], gte(F_NS));
    strcpy(filtros[6], gte(F_NP));
    strcpy(filtros[7], gte(F_Al));
    strcpy(filtros[8], gte(F_St));
    aplicarFiltros();
}
