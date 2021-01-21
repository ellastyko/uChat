#include "../inc/header.h"


int validation(char *login, char *password) { 
    char banned_symbols[35] = {'!', '@', '#', '$', '^', '&', '*', '(', ')', '-', '+',
                             '=', '[', '{', '}', ']', '`', '`', '|', '/','1', '2', '3',
                             '4', '5', '6', '7', '8', '9', '0'};
    for (int i = 0; i < strlen(login); i++) {
        for (int j = 0; j < strlen(banned_symbols); j++) { 
            if (login[i] == banned_symbols[j]) {
                write(2, "Banned symbol used\n", 9);
                return 1;
            } 
        }
    }
    return 0;
}  

char *stringify(struct info *req)
{
    char *string = NULL;

    cJSON *json_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(json_msg, "action", req->action);
    cJSON_AddStringToObject(json_msg, "login", req->login);
    cJSON_AddStringToObject(json_msg, "password", req->password);
    cJSON_AddStringToObject(json_msg, "message", req->message);
    cJSON_AddStringToObject(json_msg, "time", req->time);
    cJSON_AddStringToObject(json_msg, "receiver", req->time);
    cJSON_AddStringToObject(json_msg, "key", req->key);
    string = cJSON_Print(json_msg);

    cJSON_Delete(json_msg);
    return string;
}

struct info *parse(const char *const msg)
{
    struct info *res = malloc(sizeof(struct info));
    
    const cJSON *status = NULL;
    const cJSON *response = NULL;
    const cJSON *time = NULL;

    cJSON *msg_json = cJSON_Parse(msg);

    status = cJSON_GetObjectItemCaseSensitive(msg_json, "status");
    if (status == NULL || status->valuestring == NULL)
        return NULL;

    response = cJSON_GetObjectItemCaseSensitive(msg_json, "response");
    if (response == NULL || response->valuestring == NULL)
        return NULL;

    time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
    if (time == NULL || time->valuestring == NULL)
        return NULL;
    
    strcpy(res->status, status->valuestring);
    strcpy(res->response, response->valuestring);
    strcpy(res->time, time->valuestring);
    
    cJSON_Delete(msg_json);

    return res;
}


//TODO
int time_converter(int time) {

    return 0;
}


