#include "../inc/header.h"

// universal structure for all types of send
struct info {
    char action[10]; //
    char login[20]; // user or sender of message
    char password[20]; 
    char message[500];
    char time[50]; // time when message was sended
    char receiver[20]; // receiver of message
};

char *stringify(struct info *req)
{
    char *string = NULL;

    cJSON *json_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(json_msg, "action", req->action);
    cJSON_AddStringToObject(json_msg, "login", req->login);
    cJSON_AddStringToObject(json_msg, "password", req->password);
    cJSON_AddStringToObject(json_msg, "message", req->message);
    cJSON_AddStringToObject(json_msg, "time", req->time);

    string = cJSON_Print(json_msg);

    cJSON_Delete(json_msg);
    return string;
}

struct info *parse(const char *const msg)
{
    struct info *res = malloc(sizeof(struct info));
    const cJSON *action = NULL;
    const cJSON *login = NULL;
    const cJSON *password = NULL;
    const cJSON *message = NULL;
    const cJSON *time = NULL;

    cJSON *msg_json = cJSON_Parse(msg);

    action = cJSON_GetObjectItemCaseSensitive(msg_json, "action");
    if (action == NULL || action->valuestring == NULL)
        return NULL;

    login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
    if (login == NULL || login->valuestring == NULL)
        return NULL;

    password = cJSON_GetObjectItemCaseSensitive(msg_json, "password");
    if (password == NULL || password->valuestring == NULL)
        return NULL;

    message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
    if (message == NULL || message->valuestring == NULL)
        return NULL;

    time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
    if (time == NULL || time->valuestring == NULL)
        return NULL;

    strcpy(res->action, action->valuestring);
    strcpy(res->login, login->valuestring);
    strcpy(res->password, password->valuestring);
    strcpy(res->message, message->valuestring);
    strcpy(res->time, time->valuestring);
    cJSON_Delete(msg_json);

    return res;
}

//  Функция регистрации
void sign_up(int client_socket) {

    struct info req; char repeat_password[20];

    strcpy(req.action, "sign_up");    
    printf("Enter username: "); scanf("%s", req.login);
    printf("Enter password: "); scanf("%s", req.password);
    printf("Repeat password: "); scanf("%s", repeat_password);
    strcpy(req.message, "");
    strcpy(req.time, "");
    strcpy(req.receiver, "");

    if(strcmp(req.login, repeat_password) != 0) {
        write(2, "Parols are different\n", 22);
    }
    if((validation(req.login, req.password)) == 0) {
        write(2, "Successful validation\n", 23);
    }
    char *buf = stringify(&req); // To JSON

    int result;
    if ((result = write(client_socket, buf, strlen(buf))) == -1) {
        write(2, "Fail send\n", 11);
        //return false;
    }
    if ( (result = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else {
        write(STDOUT_FILENO, buf, strlen(buf));
        // struct info *res = parse(buf);
        // printf("%s, %s\n", res->login, res->password);
    }
}

//  Функция входа
void sign_in(int client_socket) {
    struct info req;
    strcpy(req.action, "sign_in");
    printf("Enter username: "); scanf("%s", req.login);
    printf("Enter password: "); scanf("%s", req.password);
    strcpy(req.message, "");
    strcpy(req.time, "");
    strcpy(req.receiver, "");

    char *buf = stringify(&req);

    int result;
    if ((result = write(client_socket, buf, strlen(buf))) == -1) {
        write(2, "Fail send\n", 11);
    }
    if ( (result = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else {
        write(STDOUT_FILENO, buf, strlen(buf));
        //struct info *res = parse(buf);
        //printf("%s, %s\n", res->login, res->password);      
    }
}

//  Функция отправки сообщения
/*bool send_message(int client_socket) {
    struct info req;
    strcpy(req.action, "send_message");
    strcpy(req.login, _user_);
    strcpy(req.password, "")  
    printf("Enter message: "); scanf("%s", req.message);
    strcpy(req.time, ""); //TODO
    printf("Send to: "); scanf("%s", req.receiver);
    
    char *buf = stringify(&req);

    int result;
    if ((result = write(client_socket, buf, strlen(buf))) == -1) {
        write(2, "Fail send\n", 11);
    }
    if ( (result = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else {
        write(STDOUT_FILENO, buf, strlen(buf));
    }
}

//  Функция удаления пользователя
bool delete_user(int client_socket) {
    struct info req;
    strcpy(req.action, "delete_user");
    strcpy(req.login, _user_);
    strcpy(req.password, "")  
    strcpy(req.message, "");
    strcpy(req.time, ""); 
    strcpy(req.receiver, "");

    char *buf = stringify(&req);

    int result;
    if ((result = write(client_socket, buf, strlen(buf))) == -1) {
        write(2, "Fail send\n", 11);
    }
    if ( (result = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else {
        write(STDOUT_FILENO, buf, strlen(buf));
    }
}


//  Функция изменения пароля
bool change_password(int client_socket) {
    struct info req;
    strcpy(req.action, "change_password");
    strcpy(req.login, _user_);
    strcpy(req.password, "")  
    strcpy(req.message, "");
    strcpy(req.time, ""); 
    strcpy(req.receiver, "");

    char *buf = stringify(&req);

    int result;
    if ((result = write(client_socket, buf, strlen(buf))) == -1) {
        write(2, "Fail send\n", 11);
    }
    if ( (result = read(client_socket, buf, strlen(buf))) == -1) { 
        write(2, "Fail recieve\n", 14);
    }
    else {
        write(STDOUT_FILENO, buf, strlen(buf));
    }
}*/

/* Блок нуждается в сокращении объема кода*/
