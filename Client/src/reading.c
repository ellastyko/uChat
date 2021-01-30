#include "../inc/header.h"

void *reading() {
    char buf[BUFSIZ]; ssize_t result;
    while(1) {
        if ( (result = recv(3, buf, sizeof(buf), 0)) == -1) { 
            write(2, "Fail recieve\n", 14);
            
        }
        if ( result == 0 ) {
            write(2, "\nDisconnect!\n", 14); // Перестаем читать сервер
            close(3);
            break;
        }
        else {
            //write(STDOUT_FILENO, buf, strlen(buf));
            strcpy(buf, decoding(buf));
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
            // saving(res.login, res.password) save login and parol in local storage
            get_chats_info();           
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

