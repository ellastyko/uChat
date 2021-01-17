#include "../inc/header.h"

/*static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
}

int main (int    argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}*/

int sign_up(int client_socket) {

    char login[20], password[20];
    printf("Enter username: "); scanf("%s", login);
    printf("Enter password: "); scanf("%s", password);
    char *buf = strcat(login, password);
    int res;
    if (res = write(client_socket, buf, strlen(buf)) == -1) {
        write(2, "Fail send\n", 11);
    }
    else
    {
        printf("%i\n", res);
    }  
    if ( (res = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else 
    {
        write(STDOUT_FILENO, buf, strlen(buf));
    }
}

int main(int argc, char *argv[])
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);

    inet_pton(AF_INET, ADDR, &adr.sin_addr);
    if (connect(client_socket, (struct sockaddr *) &adr, sizeof adr) == -1) {
        client_socket = -1;
        printf("DISCONNECT\n");
    }

    int action, result;
    while(1) {
        printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Delete account\n");
        scanf("%d",&action);
        switch(action) {
            case 1: result = sign_up(client_socket); break;
            //case 2: sign_in(); break;
            //case 3: delete_user(); break;
            //case 4: printf("%i", client_socket); write(client_socket, "a", 2);
            default: break;
        }
    }

    /*GtkWidget *window;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World!");
    gtk_widget_show (window);

    //Connect the main window to the destroy 
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

    gtk_widget_show(window);

    gtk_main();*/
    close(client_socket);
    return 0;
}

