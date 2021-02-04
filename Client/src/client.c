#include "../inc/header.h"

int client_socket = 0;
int STATE = 0;

int main(int argc, char *argv[])
{
    prepare();
    Socket();
    
    //checking_local_storage(); // Проверка локального хранилища на сохранненый пароль с именем
    
    main_style = gtk_css_provider_new ();
    sign_style = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(main_style,"Client/css/style.css", NULL);
    gtk_css_provider_load_from_path(sign_style,"Client/css/main.css", NULL);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("Client/glade/new.glade");
    
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    Main = GTK_CONTAINER(gtk_builder_get_object(builder, "Main"));
    entering();    

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_style), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window);   

    gtk_main();

    return 0;
}

