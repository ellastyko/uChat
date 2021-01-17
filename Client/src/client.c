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

int sign_up(void* cl_socket) {
    int *temp = cl_socket;
    int client_socket = *temp;
    char login[20], password[20];
    printf("Enter username: "); scanf("%s", login);
    printf("Enter password: "); scanf("%s", password);
    char *buf = strcat(login, password);
    printf("%s", buf);
    write(client_socket, buf, strlen(buf));
}


int main(int argc, char *argv[])
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);

    inet_pton(AF_INET, ADDR, &adr.sin_addr);
    connect(client_socket, (struct sockaddr *) &adr, sizeof adr);
    // Send message
    char *a = "Hello\n";
    write(client_socket, a, strlen(a)); // SEND HELLO
    // Recieve message
    char buf[256];
    ssize_t nread = read(client_socket, buf, 256); //GET HELLO

    if (nread == -1) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("EOF occured\n");
    }
    write(STDOUT_FILENO, buf, nread); //OUTPUT HELLO
    //memset(buf, 0, sizeof(buf));
    

    int action, result;
    while(1) {
        printf("What do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Delete account\n");
        scanf("%d",&action);
        switch(action) {
            case 1: result = sign_up(&client_socket); break;
            //case 2: sign_in(); break;
            //case 3: delete_user(); break;
            case 4: printf("%i", client_socket); write(client_socket, a, strlen(a));
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

