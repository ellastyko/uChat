#include "../inc/header.h"


// Главная функция обработки запросов //
void type_of_request(char *str, int client_socket)
{
    ssize_t result;
    char response[250];
    struct info *req = parse(str);
    if (strcmp(req->action, "sign_up") == 0)
    {
        if (check_login(req->login) == false) {      
            strcpy(response, "Login already exists!\n");
            if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                write(2, "Fail send\n", 11);
            }
            
        }
        else  { 
            write(2, "Login valid!\n", 14);  
            db_add_user(req->login, req->password, key()); 
        }
        
    }
    else if (strcmp(req->action, "sign_in") == 0)
    {
        write(2, "You want to sign in!\n", 22);
        if(verification(req->login, req->password) == true) {
            get_id_and_key(client_socket, req->login);
        }
        else {
            strcpy(response, "Login or parol error!\n");
            if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
                write(2, "Fail send\n", 11);
            }
        }
    }
    else if (strcmp(req->action, "add_chat") == 0) {
        
    }
    else if (strcmp(req->action, "send_message") == 0)
    {
        write(2, "You want to end message\n", 25);
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
    else if (strcmp(req->action, "update")) {

    }
    else if (strcmp(req->action, "delete_bd")) {

    }
    else {       
        write(2, "Unknown command!\n", 18);
        write(2, req->action, sizeof(req->action));
    }
    memset(&response, 0, sizeof(result));
    memset(&req->action, 0, sizeof(req->action)); 
    memset(&req->login, 0, sizeof(req->login)); 
    memset(&req->password, 0, sizeof(req->password)); 
    memset(&req->key, 0, sizeof(req->key)); 
    memset(&req->message, 0, sizeof(req->message)); 
    memset(&req->time, 0, sizeof(req->time)); 
    memset(&req->receiver, 0, sizeof(req->receiver)); 
}

