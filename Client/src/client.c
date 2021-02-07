#include "../inc/header.h"

int client_socket = 0;
int STATE = 0;

int main(int argc, char *argv[])
{
    
    Socket();
    //if (local_storage(0) == 0) {// Проверка локального хранилища на сохранненый пароль с именем 
    //}
    prepare();

    style = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(style,"Client/css/style.css", NULL);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("Client/glade/new.glade");
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    
    SIGN_BOXES();
    MAIN_BOXES();
    NO_CONNECTION_BOX();   


    gtk_widget_hide ( GTK_WIDGET(Connection_lost) );
    //gtk_widget_hide ( GTK_WIDGET(SignLog) );
    gtk_widget_hide ( GTK_WIDGET(Main) );



    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(style), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window);   

    gtk_main();

    return 0;
}

