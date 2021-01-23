#include "../inc/header.h"

// Сделать ответы сервера в формате JSON
char *stringify(struct info *req)
{
    char *string = NULL;

    cJSON *json_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(json_msg, "status", req->status);
    cJSON_AddStringToObject(json_msg, "response", req->response);
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
    const cJSON *receiver = NULL;
    const cJSON *key = NULL;

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

    receiver = cJSON_GetObjectItemCaseSensitive(msg_json, "receiver");
    if (receiver == NULL || receiver->valuestring == NULL)
        return NULL;

    key = cJSON_GetObjectItemCaseSensitive(msg_json, "key");
    if (key == NULL || key->valuestring == NULL)
        return NULL;

    strcpy(res->action, action->valuestring);
    strcpy(res->login, login->valuestring);
    strcpy(res->password, password->valuestring);
    strcpy(res->message, message->valuestring);
    strcpy(res->time, time->valuestring);
    strcpy(res->receiver, receiver->valuestring);
    strcpy(res->key, key->valuestring);
    cJSON_Delete(msg_json);

    return res;
}


int key() {
    srand(time(NULL));
    return rand() % 10000;
}
