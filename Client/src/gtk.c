#include "../inc/header.h"

void destroy()
{
    gtk_main_quit();
}

void entering() {

    Box = GTK_CONTAINER(gtk_builder_get_object(builder, "Box"));



    login = GTK_ENTRY(gtk_builder_get_object(builder, "Login"));
    password = GTK_ENTRY(gtk_builder_get_object(builder, "Password"));
    repeat = GTK_ENTRY(gtk_builder_get_object(builder, "Repeat"));

    To_Sign = GTK_BUTTON(gtk_builder_get_object(builder, "To_sign"));
    Log_in = GTK_BUTTON(gtk_builder_get_object(builder, "Log_in"));

    To_Log = GTK_BUTTON(gtk_builder_get_object(builder, "To_log"));
    Sign_up = GTK_BUTTON(gtk_builder_get_object(builder, "Sign_up"));

    gtk_container_remove (Box, repeat);
    gtk_container_remove (Box, To_Log);
    gtk_container_remove (Box, Sign_up);

}

void no_connection() {
    gtk_widget_hide(Box);
}
void to_sign_up() {

    gtk_container_remove (Box, To_Sign);
    gtk_container_remove (Box, Log_in);
    gtk_container_add (Box, repeat);
    gtk_container_add (Box, To_Log);
    gtk_container_add (Box, Sign_up);   
}

void to_log_in() {

    gtk_container_remove (Box, repeat);
    gtk_container_remove(Box, To_Log);
    gtk_container_remove (Box, Sign_up);
    gtk_container_add (Box, To_Sign);
    gtk_container_add (Box, Log_in);
}