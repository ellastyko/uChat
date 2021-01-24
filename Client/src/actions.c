#include "../inc/header.h"

void send_to_server(char *buf) {
    ssize_t result;
    if ((result = send(3, buf, strlen(buf), 0)) == -1) {
        write(2, "Fail send\n", 11);
    }
}

//  Функция регистрации
void sign_up() {

    struct info req; char repeat_password[20];

    strcpy(req.action, "sign_up");  
    req.id = 0;
    printf("Enter username: "); scanf("%s", req.login);
    printf("Enter password: "); scanf("%s", req.password);
    printf("Repeat password: "); scanf("%s", repeat_password);
    strcpy(req.key, "");

    req.chat_id = 0;
    strcpy(req.message, "");
    req.time = 123123;
    
    
    if(strcmp(req.password, repeat_password) != 0) {
        write(2, "Parols are different\n", 22);
    }
    if((validation(req.login, req.password)) == true) {
        write(2, "Successful validation\n", 23);
    } 
    char *buf = stringify(&req); // To JSON
    send_to_server(buf);
}

//  Функция входа
void sign_in() {
    struct info req;

    strcpy(req.action, "sign_in");
    req.id = 0;
    printf("Enter username: "); scanf("%s", req.login);
    printf("Enter password: "); scanf("%s", req.password);

    req.chat_id = 0;
    strcpy(req.message, "");
    req.time = 123123;
    
    char *buf = stringify(&req);
    send_to_server(buf);
}

//  Функция отправки сообщения
bool send_message() {
    struct info req;

    strcpy(req.action, "send_message");

    req.id = cl_info.id;
    strcpy(req.login, "");
    strcpy(req.password, "");  
    strcpy(req.key, cl_info.key);

    printf("Send to: "); scanf("%d", &req.chat_id);
    printf("Enter message: "); scanf("%s", req.message);
    req.time = 123123; 
    
    

    char *buf = stringify(&req);
    send_to_server(buf);
}

//  Функция удаления пользователя
bool delete_user() {
    struct info req;
    
    strcpy(req.action, "delete_user");

    req.id = cl_info.id;
    strcpy(req.login, "");
    strcpy(req.password, "");  
    strcpy(req.key, "");

    req.chat_id = 0;
    strcpy(req.message, "");
    req.time = 0; 
    
    

    char *buf = stringify(&req);
    send_to_server(buf);
}

//  Функция изменения пароля
bool change_password() {
    struct info req;

    strcpy(req.action, "change_password");

    req.id = cl_info.id;
    strcpy(req.login, "");
    strcpy(req.password, "new password"); 
    strcpy(req.key, cl_info.key);

    req.chat_id = 0;
    strcpy(req.message, "");
    req.time = 123123; 
    

    char *buf = stringify(&req);
    send_to_server(buf);
}

/*char *checking_local_storage(int act) {
    char*line; 
    if (act == 0) { // READ BEFORE SIGN IN
        // cache
        FILE *file = fopen("data.txt", "r");
        fgets(line, 255, file);
        printf("%s", line);
        fclose(file);
        if (strcmp(line, "") == 0) {
            write(2, "There is nothing!\n", 19);
            return 1;
        }
        else {
            struct info *req;
            strcpy(req->action, "signin");
            strcpy(req.login, _id_);
            strcpy(req.password, _password_);  
            strcpy(req.message, "");
            strcpy(req.time, ""); 
            strcpy(req.receiver, "");
            char *buf = stringify(&req);
            send_to_server(buf);
        }

    }
    else if (act == 0) { // WRITE AFTER SIGN UP
        FILE *file = fopen("data.txt", "r");
        fgets(line, 255, file);
        printf("%s", line);
        fclose(file);
        if (strcmp(line, "") == 0) {
            write(2, "There is nothing!\n", 19);
            return 1;
        }
    }
    else if { // LOGOUT
        write(2, "Error", 6)
    }
}*/
//bool delete_message();

