#include "../inc/header.h"

void *reading() {
    char buf[BUFSIZ]; ssize_t result;
    while(1) {
        if ( (result = recv(3, buf, sizeof(buf), 0)) == -1) { 
            write(2, "Fail recieve\n", 14);
        }
        else {
            write(STDOUT_FILENO, buf, strlen(buf));
            struct info *res = parse(buf);
            type_of_response(res);    
        }
    }
}


void type_of_response(struct info *res) {
    
    if (res->status != 1) {
        write(2, "Request isn`t executed\n", 24);
        write(2, res->message, strlen(res->message));
    }
    else {
        if (strcmp(res->action, "sign_up") == 0) {
            write(2, "Successful registration\n", 25);
        }
        else if (strcmp(res->action, "sign_in") == 0) {
            write(2, "Successful sign in\n", 20);
            cl_info.id = res->id;
            strcpy(cl_info.login, res->login);
            strcpy(cl_info.password, res->password);
            strcpy(cl_info.key, res->key);
            // saving(res.login, res.password) save login and parol in local storage
            get_chats_info();           
        }
        else if (strcmp(res->action, "get_login_by_id") == 0) {
            // Получаем имя собеседника
            write(2, res->login, strlen(res->login));
        }
        else if (strcmp(res->action, "add_chat") == 0) {

            printf("\nChat %d added\n", res->chat_id);
            printf("Friend id%d\n", res->friend_id);
            printf("Login %s\n", res->login);
            push_chat(res->chat_id, res->friend_id, res->login);
            //print_all();
        }
        else if (strcmp(res->action, "get_chats_info") == 0) {
            // Запись полученных данных в структуру
            push_chat(res->chat_id, res->friend_id, res->login);
            //print_all();
        }
        else if (strcmp(res->action, "send_message") == 0) {
            write(2, "Message sended\n", 12);
        }

    }
}

