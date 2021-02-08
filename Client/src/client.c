#include "../inc/header.h"

int client_socket = 0;
int STATE = 0;

int main(int argc, char *argv[])
{
    
    if (Socket() == 1) {
        STATE = 3;
    }
    prepare();
    if (auto_sign() == EXIT_FAILURE) {
        STATE = 0;
    }
    
    gtk_init(&argc, &argv);

    style = gtk_css_provider_new ();
    style_dark = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(style,"Client/css/style.css", NULL);
    gtk_css_provider_load_from_path(style_dark,"Client/css/dark.css", NULL);

    
    builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("Client/glade/main.glade");
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    notification = GTK_WIDGET(gtk_builder_get_object(builder, "notification"));
    

    SIGN_BOXES();
    MAIN_BOXES();
    NO_CONNECTION_BOX();   


    if (config() == 0) {
        if (Config.theme != 1) {
            
            gtk_switch_set_state (GTK_SWITCH(Theme), true);
            theme();
        }
        else {
            
            gtk_switch_set_state (GTK_SWITCH(Theme), false);
            theme();
        }
    }
    else {
        gtk_switch_set_state (GTK_SWITCH(Theme), true);
        theme();
    }
    

    gtk_builder_connect_signals(builder, NULL);

    if (STATE == 0) {
        reading_thread();
        gtk_widget_hide ( GTK_WIDGET(Main) );
        gtk_widget_hide ( GTK_WIDGET(Connection_lost) );
    } 
    else if (STATE == 2) {
        gtk_widget_hide ( GTK_WIDGET(Connection_lost) );
        gtk_widget_hide ( GTK_WIDGET(SignLog) );
    }
    else if (STATE == 3) {
        gtk_widget_hide ( GTK_WIDGET(Main) );
        gtk_widget_hide ( GTK_WIDGET(SignLog) );
    }
    
    

    gtk_widget_show(window);   

    gtk_main();

    return 0;
}

