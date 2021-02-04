#include "../inc/header.h"

int client_socket = 0;

int main(int argc, char *argv[])
{
    prepare();
    Socket();
    pthread_t reads;
    pthread_create(&reads, NULL, reading, NULL);
    //checking_local_storage(); // Проверка локального хранилища на сохранненый пароль с именем
    
    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider,"Client/css/style.css", NULL);
    

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("Client/glade/new.glade");
    
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    entering();    

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);   

    gtk_main();

    return 0;
}



/*int action;
    while(1) {
        printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n");
        scanf("%d",&action);
        switch(action) {
            case 1: sign_up(); break;
            case 2: sign_in(); break;  
            default: break;
            

        }
        sleep(1);
        while(cl_info.id != -1 && strcmp(cl_info.key, "-1") != 0) {
            printf("\nWhat do you want:\n 1 - Add chat\n 2 - Open chat\n 3 - Send message\n 4 - Delete message\n 5 - Change Password\n 6 - Delete account\n");
            scanf("%d",&action);
            switch(action) {
                case 1: add_chat(); break;
                case 2: open_chat(); break; // load messages
                case 3: send_message(); break;
                case 4: delete_message(); break;
                case 5: change_password(); break;
                case 6: delete_user(); break;
                
                default: break;
            }
        }
    }*/