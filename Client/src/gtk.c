#include "../inc/header.h"

void destroy() { gtk_main_quit(); }

void entering() {

    Box = GTK_CONTAINER(gtk_builder_get_object(builder, "Box"));

    login = GTK_WIDGET(gtk_builder_get_object(builder, "Login"));
    password = GTK_WIDGET(gtk_builder_get_object(builder, "Password"));
    repeat = GTK_WIDGET(gtk_builder_get_object(builder, "Repeat"));
    hint = GTK_WIDGET(gtk_builder_get_object(builder, "Hint"));

    To_Sign = GTK_WIDGET(gtk_builder_get_object(builder, "To_sign"));
    Log_in = GTK_WIDGET(gtk_builder_get_object(builder, "Log_in"));

    To_Log = GTK_WIDGET(gtk_builder_get_object(builder, "To_log"));
    Sign_up = GTK_WIDGET(gtk_builder_get_object(builder, "Sign_up"));

    gtk_widget_hide (repeat);
    gtk_widget_hide (To_Log);
    gtk_widget_hide (Sign_up);
    gtk_widget_hide (hint);

    // gtk_container_remove (Box, repeat);
    // gtk_container_remove (Box, To_Log);
    // gtk_container_remove (Box, Sign_up);
    // gtk_container_remove (Box, hint);

}

void no_connection() {
    gtk_container_remove(Main, GTK_WIDGET(Box) );
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(sign_style), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
}

void valid_login() {
    if (STATE == 1)  {
        availability_of_login();
        validation();
    } 
    
}

void valid_password() {
    if (STATE == 1) {
        validation();
    } 
    
}

void to_sign_up() {

    // gtk_container_remove (Box, To_Sign);
    // gtk_container_remove (Box, Log_in);
    // gtk_container_add (Box, repeat);
    // gtk_container_add (Box, To_Log);
    // gtk_container_add (Box, Sign_up);  

    gtk_widget_hide (To_Sign);
    gtk_widget_hide (Log_in); 
    gtk_widget_hide (hint);

    gtk_widget_show (repeat);
    gtk_widget_show (To_Log);
    gtk_widget_show (Sign_up);
    

    
    STATE = 1;
}

void to_log_in() {

    gtk_widget_hide (repeat);
    gtk_widget_hide (To_Log);
    gtk_widget_hide (Sign_up);
    gtk_widget_hide (hint);

    gtk_widget_show (To_Sign);
    gtk_widget_show (Log_in);
    // gtk_container_remove (Box, repeat);
    // gtk_container_remove(Box, To_Log);
    // gtk_container_remove (Box, Sign_up);
    // gtk_container_add (Box, To_Sign);
    // gtk_container_add (Box, Log_in);
    STATE = 0;
}