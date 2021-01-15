// #include "../inc/client.h"
#include <gtk/gtk.h>
#include <stdio.h>
void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World!");
    gtk_widget_show (window);

    /* Connect the main window to the destroy */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

    gtk_widget_show(window);

    gtk_main();
}


// static void activate (GtkApplication* app, gpointer user_data)
// {
//   GtkWidget *window
//   window = gtk_application_window_new (app);
//   input = gtk_
//   gtk_window_set_title (GTK_WINDOW (window), "Aest");
//   gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
//   gtk_widget_show_all (window);


// }

// int main (int argc, char **argv)
// {
//   GtkApplication *app;
//   int status;

//   app = gtk_application_new ("aest", G_APPLICATION_FLAGS_NONE);
//   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
//   status = g_application_run (G_APPLICATION (app), argc, argv);
//   g_object_unref (app);

//   return status;
// }