#include "../inc/header.h"

void *reading() {
    char buf[BUFSIZ]; ssize_t result;
    while(1) {
        if ( (result = recv(client_socket, buf, sizeof(buf), 0)) == -1) { 
            write(2, "Fail recieve\n", 14);
            close(client_socket);
            no_connection();
            break;
            
        }
        if ( result == 0 ) {
            write(2, "\nDisconnect!\n", 14); // Перестаем читать сервер
            close(client_socket);
            no_connection();
            break;
        }
        else {
            //write(STDOUT_FILENO, buf, strlen(buf));
            strcpy(buf, decoding(buf));
            //write(2, buf, strlen(buf));
            struct info *res = parse(buf);
            type_of_response(res);    
        }
    }
    pthread_exit(NULL);    
}


void type_of_response(struct info *res) {
    
    if (res->status != 1) {
        write(2, "Request isn`t executed\n", 24);
        write(2, res->message, strlen(res->message));
        if (strcmp(res->action, "availability_of_login") == 0) {
            gtk_widget_show (hint);
            gtk_label_set_text(hint, res->message);
        }
        else if (strcmp(res->action, "sign_in") == 0) {
            gtk_widget_show (hint);
            gtk_label_set_text(hint, res->message);
        }
        else if (strcmp(res->action, "sign_up") == 0) {
            gtk_widget_show (hint);
            gtk_label_set_text(hint, res->message);
        }
    }
    else {
        if (strcmp(res->action, "sign_up") == 0) {
            write(2, "\nSuccessful registration\n", 26);
        }
        else if (strcmp(res->action, "sign_in") == 0) {

            cl_info.id = res->id;
            strcpy(cl_info.login, res->login);
            strcpy(cl_info.password, res->password);
            strcpy(cl_info.key, res->key);
            gtk_label_set_text(hint, "");
            // saving(res.login, res.password) save login and parol in local storage
            get_chats_info();   
            gtk_container_remove(Main, GTK_WIDGET(Box) );
            gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(sign_style), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
        else if (strcmp(res->action, "add_chat") == 0) {

            push_chat(res->chat_id, res->friend_id, res->login);
        }
        else if (strcmp(res->action, "get_chats_info") == 0) {
            // Запись полученных данных в структуру
            push_chat(res->chat_id, res->friend_id, res->login);
        }
        else if (strcmp(res->action, "get_message") == 0) {
            write(2, "\n", 2);
            write(2, res->message, strlen(res->message));
        }
        else if (strcmp(res->action, "send_message") == 0) {
            write(2, "Message sended\n", 16);
        }
        else if (strcmp(res->action, "delete_message") == 0) {
            write(2, "Message deleted\n", 17);
        }
        else if (strcmp(res->action, "availability_of_login") == 0) {
            //gtk_label_set_text(hint, "");
             if (strcmp(gtk_label_get_text (hint), "This login isn`t available") == 0) {
                gtk_widget_hide (hint);
            }
        }
        else if (strcmp(res->action, "load_messages") == 0) {

            if (res->id == cl_info.id) {
                write(2, "---------", 10);
                write(2, res->message, strlen(res->message));
            }
            else {
                write(2, res->message, strlen(res->message));
                write(2, "---------", 10);
            }   
            printf("\n");
        }

    }
}

