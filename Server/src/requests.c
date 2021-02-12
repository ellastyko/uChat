#include "../inc/header.h"


// Главная функция обработки запросов //
void type_of_request(char *str, int client_socket)
{
    
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

                req->friend_id = get_id_by_login(req->login);
                req->id = req->friend_id; 
                get_chat_id_by_users(req);    // Возвращает id чата 
                if (add_chat(req) == true) { // Добавляем чат

                    req->status = 1; // Успешно

                    send_response(client_socket, req);     
                }
                else {
                    req->status = 0; // error status
                    strcpy(req->message, "Chat with saved messages not created");  
                    send_response(client_socket, req);  
                     
                }
            }
            else {
                req->status = 0; // error status
                strcpy(req->message, "Data aren`t inserted");
                send_response(client_socket, req);  
            }
        }     
    }
    else if ( (strcmp(req->action, "sign_in") == 0) || (strcmp(req->action, "auto_sign") == 0) )
    {
        
        if(verification(req->login, req->password) == true) {
            
            get_id_and_key(req);
            req->status = 1; // Successful
            send_response(client_socket, req);
            to_be_online(client_socket, req);
            

            update_time(req->id, 0);            
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "Login or password isn`t correct");
            send_response(client_socket, req);  
        }
    }
    else if (strcmp(req->action, "is_user_exists") == 0) {

        if (check_login(req->login) == false) {    // Если такой пользователь существует
           
            req->status = 1; // Успешно
            get_chat_id_by_users(req);
            send_response(client_socket, req);     
               
        }
    }
    else if (strcmp(req->action, "add_chat") == 0) {

        if (check_login(req->login) == false) {    // Если такой пользователь существует
           
            req->friend_id = get_id_by_login(req->login); // Записываем id пользователя по имени
            if (req->friend_id != req->id) {
          
                get_chat_id_by_users(req);    // Возвращает id чата 
                if (req->chat_id == -1) { // Если чата нет то ...

                    if (add_chat(req) == true) { // Добавляем чат
                
                        req->status = 1; // Успешно
                        get_chat_id_by_users(req);
                        send_response(client_socket, req);     
                    }
                    else {
                        req->status = 0; // error status
                        strcpy(req->message, "Dialog hasn`t added");  
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
                strcpy(req->message, "You can`t add yourself");
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
            get_message();
            int new_socket = find_friend(req->friend_id);
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
    else if (strcmp(req->action, "delete_message") == 0) { // Успешно даже когда сообщение не удалено
        
        if (delete_message(req) == true) {
            get_message(req);
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
        if (delete_user(req) == true) {

            req->status = 1;
            send_response(client_socket, req);
        }
        else {
            req->status = 0;
            send_response(client_socket, req);
        }
    }
    else if (strcmp(req->action, "change_password") == 0)
    {
        if (change_password(req) == true) {

            req->status = 1;
            send_response(client_socket, req);
        }
        else {
            req->status = 0;
            send_response(client_socket, req);
        }
    }
    else if (strcmp(req->action, "open_chat") == 0) {
        if (req->id != req->friend_id) {
            if (take_time(req) == true) {
                req->status = 1; 
                send_response(client_socket, req);
            }
            else {
                req->status = 1; 
                strcpy(req->message, "Time hasn`t taken");
                send_response(client_socket, req);
            }
        }
        strcpy(req->action, "load_messages"); 
        load_messages(client_socket, req);  
    }
    else if (strcmp(req->action, "get_chats_info") == 0) {

        get_chats_info(client_socket, req);
    }
    else if (strcmp(req->action, "availability_of_login") == 0) {

        if (check_login(req->login) == false) {      

            req->status = 0; // error status
            strcpy(req->message, "This login isn`t available");
            send_response(client_socket, req);       
        }
        else {
            req->status = 1; 
            send_response(client_socket, req);    
        }
    }   
    else if (strcmp(req->action, "log_out") == 0) {

        if (delete_online(client_socket) == 1) {      

            req->status = 1; 
            send_response(client_socket, req);       
        }
        else {
            req->status = 0; // error status
            strcpy(req->message, "You havn`t loged out");
            send_response(client_socket, req);    
        }
    } 
}

void send_response(int client_socket, struct info *res) {

    ssize_t result;
    char *temp;
    char response[BUFSIZ];
    temp = stringify(res);
    strcpy(response, temp);

    if ((result = send(client_socket, response, sizeof(response), 0)) == -1) {
        perror("Fail send");
    }     
}
