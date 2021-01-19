#include "../inc/header.h"

struct info {
    char action[10];
    char login[20];
    char password[25];
    char message[500];
    char time[50];
};

// Сделать ответы сервера в формате JSON
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

// Передает запрос из JSON в структуру
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

// Главная функция обработки запросов
char* type_of_request(char *str) { 
    struct info *req = parse(str);
    if (strcmp(req->action, "sign_up") == 0) { 
        write(2, "You want to sign up!\n", 22);
        return "signup";
    }
    else if (strcmp(req->action, "sign_in") == 0) {
        write(2, "You want to sign in!\n", 22);
        return "signup";
    }
    else if (strcmp(req->action, "send_message") == 0) {
        write(2, "You want to end message\n", 25);
        return "send_message";
    }
    else if (strcmp(req->action, "delete_user") == 0) {
        write(2, "You want to change settings!\n", 30);
        return "settings";
    }
    else if (strcmp(req->action, "change_passpord") == 0) {
        write(2, "You want to change settings!\n", 30);
        return "change_password";
    }
    else {
        write(2,"Something wrong!\n", 18);
        write(2, req->action, sizeof(req->action)); 
        return "error";
    }   
}