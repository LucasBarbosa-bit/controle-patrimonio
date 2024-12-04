G_MODULE_EXPORT void login_destroy()
{
    gtk_main_quit();
}

G_MODULE_EXPORT void tentaiva_login(GtkButton *b, gpointer user_data) {
    //GtkEntry *entry = GTK_ENTRY(user_data); // Cast user_data to GtkEntry
    const char *usr = gtk_entry_get_text(Ent_Usr);
    const char *pin = gtk_entry_get_text(Ent_PIN);
    int pinInt;
    if (sscanf(pin, "%d", &pinInt) == 1) {
            if (initLogin(usr, pinInt)==1){
                gtk_widget_hide(GTK_WIDGET(LgnInc));
                gtk_entry_set_text(Ent_Usr, "");
                gtk_entry_set_text(Ent_PIN, "");
                gtk_widget_hide(JanelaLogin);
                gtk_widget_show(JanelaPrincipal);

            } else {
                gtk_widget_show(GTK_WIDGET(LgnInc));
            }


    } else {
        gtk_widget_show(GTK_WIDGET(LgnInc));
    }
}


