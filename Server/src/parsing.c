#include "../inc/header.h"


// Главная функция обработки запросов //
int type_of_request(char *str, int client_socket)
{
    ssize_t result;
    char *temp;
    char response[BUFSIZ];
    
    struct info *req = parse(str);

    if (strcmp(req->action, "sign_up") == 0)
    {
        if (check_login(req->login) == false) {      

            req->status = 0; // error status
            strcpy(req->message, "This login isn`t available");
            temp = stringify(req);
            strcpy(response, temp);

            if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                write(2, "Fail send\n", 11);
            }        
        }
        else  { 
            if (add_user(req->login, req->password, key()) == true) {
                
                req->status = 1;
                temp = stringify(req);
                strcpy(response, temp);
                write(2, response, strlen(response));
                if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                    write(2, "Fail send\n", 11);
                }   
            }
            else {
                req->status = 0; // error status
                strcpy(req->message, "Data aren`t inserted");
                temp = stringify(req);
                strcpy(response, temp);

                if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                    write(2, "Fail send\n", 11);
                }   
            }
        }     
    }
    else if (strcmp(req->action, "sign_in") == 0)
    {
        write(2, "You want to sign in!\n", 22);
        if(verification(req->login, req->password) == true) {
            get_id_and_key(client_socket, req);
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "Login or parol isn`t correct!");
            temp = stringify(req);
            strcpy(response, temp);
            if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                write(2, "Fail send\n", 11);
            }
        }
    }
    else if (strcmp(req->action, "get_login_by_id") == 0) {
        get_login_by_id(client_socket, req->id);
    }
    else if (strcmp(req->action, "add_chat") == 0) {
        if (check_login(req->login) == false) {    // Если такой пользователь существует

            req->friend_id = get_id_by_login(req->login); // Записываем id пользователя по имени
            req->chat_id = get_chat_id_by_users(req);    // Возвращает id чата 
            if (req->chat_id == -1) { // Если чата нет то ...
                write(2, "There is no such chat", 22);
                if (add_chat(req) == true) { // Добавляем чат
            
                    req->status = 1; // Успешно
                    req->chat_id = get_chat_id_by_users(req);
                    temp = stringify(req);
                    strcpy(response, temp);

                    if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                        write(2, "Fail send\n", 11);
                    }     
                }
                else {
                    req->status = 0; // error status
                    strcpy(req->message, "User hasn`t added to your frinds");
                    temp = stringify(req);
                    strcpy(response, temp);

                    if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                        write(2, "Fail send\n", 11);
                    }     
                }
            }  
            else {
                req->status = 0; // error status
                strcpy(req->message, "Chat already exists");
                temp = stringify(req);
                strcpy(response, temp);

                if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                    write(2, "Fail send\n", 11);
                }    
            }    
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "User isn`t exists");
            temp = stringify(req);
            strcpy(response, temp);

            if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                write(2, "Fail send\n", 11);
            }     
        }
    }
    else if (strcmp(req->action, "get_chats_info") == 0) {
        //get_chats_info(req->login);
    }
    else if (strcmp(req->action, "send_message") == 0)  {
        write(2, "You want to send message\n", 26);
        if (1) { // Если 2 пользователь онлайн то
             // мы обратимся отошлем ему сообщение
             // 
        }
        // само сообщение сохранится в бд
    }
    else if (strcmp(req->action, "delete_message") == 0) {
        write(2, "You want to delete message\n", 28);
        if (1) { // Если 2 пользователь онлайн то
             // мы обратимся отошлем ему сообщение
             // 
        }
        // само сообщение сохранится в бд
    }
    else if (strcmp(req->action, "delete_user") == 0)
    {
        write(2, "You want to delete user!\n", 30);
    }
    else if (strcmp(req->action, "change_passpord") == 0)
    {
        write(2, "You want to change settings!\n", 30);
    }
    // Loading of messages
    else if (strcmp(req->action, "open_chat")) {

    }
    else {       
        write(2, "Unknown command!\n", 18);
        return 0;
    }
    return 0;
}

//send_error_message()