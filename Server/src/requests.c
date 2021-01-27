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
            send_response(client_socket, req);       
        }
        else  { 
            if (add_user(req->login, req->password, key()) == true) {
                
                req->status = 1;
                send_response(client_socket, req);  
            }
            else {
                req->status = 0; // error status
                strcpy(req->message, "Data aren`t inserted");
                send_response(client_socket, req);  
            }
        }     
    }
    else if (strcmp(req->action, "sign_in") == 0)
    {
        write(2, "You want to sign in!\n", 22);
        if(verification(req->login, req->password) == true) {

            get_id_and_key(client_socket, req);
            req->status = 1; // Successful
            send_response(client_socket, req);
            to_be_online(client_socket, req);
            print_all();   
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "Login or parol isn`t correct!");
            send_response(client_socket, req);  
        }
    }
    else if (strcmp(req->action, "get_login_by_id") == 0) {
        get_login_by_id(req);
    }
    else if (strcmp(req->action, "add_chat") == 0) {
        if (check_login(req->login) == false) {    // Если такой пользователь существует

            req->friend_id = get_id_by_login(req->login); // Записываем id пользователя по имени
            get_chat_id_by_users(req);    // Возвращает id чата 
            if (req->chat_id == -1) { // Если чата нет то ...
                write(2, "There is no such chat", 22);
                if (add_chat(req) == true) { // Добавляем чат
            
                    req->status = 1; // Успешно
                    get_chat_id_by_users(req);
                    send_response(client_socket, req);     
                }
                else {
                    req->status = 0; // error status
                    strcpy(req->message, "User hasn`t added to your frinds");  
                    send_response(client_socket, req);   
                }
            }  
            else {   
                req->status = 0; // error status
                strcpy(req->message, "Chat already exists");
                send_response(client_socket, req);  
            }    
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "User isn`t exists");
            send_response(client_socket, req);          
        }
    }
    else if (strcmp(req->action, "send_message") == 0)  {

        if (save_message(req) == true) { 
            //get_message(req);
            int new_socket = check_online(req->friend_id);
            if (new_socket != -1) { 
                strcpy(req->action, "get_message");
                req->status = 1;
                send_response(new_socket, req);
            } 
        }
        else {
            req->status = 0; // error status
            send_response(client_socket, req);
        }    
    }
    else if (strcmp(req->action, "delete_message") == 0) {
        
        if (delete_message(req) == true) {
            //get_message(req);
            req->status = 1;
            send_response(client_socket, req);
        }
        else {
            req->status = 0;
            send_response(client_socket, req);
        }
    }
    else if (strcmp(req->action, "delete_user") == 0)
    {
        write(2, "You want to delete user!\n", 30);
    }
    else if (strcmp(req->action, "change_passpord") == 0)
    {
        write(2, "You want to change settings!\n", 30);
    }
    // Updating local db after sign in
    else if (strcmp(req->action, "get_chats_info") == 0) {

        get_chats_info(client_socket, req);
    }
    else if (strcmp(req->action, "update_chats")) {


    }
    else {       
        write(2, "Unknown command!\n", 18);
        return 0;
    }
    return 0;
}

void send_response(int client_socket, struct info *res) {
    ssize_t result;
    char *temp;
    char response[BUFSIZ];

    temp = stringify(res);
    strcpy(response, temp);

    if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
        write(2, "Fail send\n", 11);
    }     
}
