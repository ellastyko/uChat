#include "../inc/header.h"

char *stringify(struct info *res)
{
    char *string = NULL;

    cJSON *json_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(json_msg, "action", res->action);  
    cJSON_AddNumberToObject(json_msg, "status", res->status);  

    if (res->status == 0) {
        cJSON_AddStringToObject(json_msg, "message", res->message);
    }
    else {

        if (strcmp(res->action, "sign_in") == 0) {
    
            cJSON_AddNumberToObject(json_msg, "id", res->id);  
            cJSON_AddStringToObject(json_msg, "login", res->login); 
            cJSON_AddStringToObject(json_msg, "password", res->password);
            cJSON_AddStringToObject(json_msg, "key", res->key);
        }
        else if (strcmp(res->action, "get_message") == 0) {
            cJSON_AddNumberToObject(json_msg, "id", res->id);  
            cJSON_AddNumberToObject(json_msg, "chat_id", res->chat_id); 
            cJSON_AddNumberToObject(json_msg, "message_id", res->message_id); 
            cJSON_AddStringToObject(json_msg, "message", res->message);
            cJSON_AddNumberToObject(json_msg, "time", res->time);
        }
        else if (strcmp(res->action, "get_login_by_id") == 0) {
            cJSON_AddStringToObject(json_msg, "login", res->login); 
        }
        else if (strcmp(res->action, "get_chats_info") == 0) {
            cJSON_AddNumberToObject(json_msg, "chat_id", res->chat_id); 
            cJSON_AddStringToObject(json_msg, "login", res->login); 
            cJSON_AddNumberToObject(json_msg, "friend_id", res->friend_id); 
        }
        else if (strcmp(res->action, "add_chat") == 0) {
            cJSON_AddNumberToObject(json_msg, "chat_id", res->chat_id); 
            cJSON_AddStringToObject(json_msg, "login", res->login); 
            cJSON_AddNumberToObject(json_msg, "friend_id", res->friend_id); 
        }
        else if (strcmp(res->action, "load_messages") == 0) {

            cJSON_AddNumberToObject(json_msg, "id", res->id);  
            cJSON_AddNumberToObject(json_msg, "chat_id", res->chat_id); 
            cJSON_AddNumberToObject(json_msg, "message_id", res->message_id); 
            cJSON_AddStringToObject(json_msg, "message", res->message);
            cJSON_AddNumberToObject(json_msg, "time", res->time);
        }
        else if (strcmp(res->action, "change_password") == 0) {
            cJSON_AddStringToObject(json_msg, "password", res->password);
        }
    }
   
    string = cJSON_Print(json_msg);

    cJSON_Delete(json_msg);

    string = encoding(string);

    return string;
}

// Передает запрос из JSON в структуру
struct info *parse(const char *const msg)
{
    struct info *res = malloc(sizeof(struct info));
    const cJSON *action = NULL;

    const cJSON *id = NULL;
    const cJSON *login = NULL;
    const cJSON *password = NULL;
    const cJSON *key = NULL;

    const cJSON *chat_id = NULL;
    const cJSON *friend_id = NULL;
    const cJSON *message = NULL;
    const cJSON *message_id = NULL;
    const cJSON *time = NULL;

    cJSON *msg_json = cJSON_Parse(msg);

    action = cJSON_GetObjectItemCaseSensitive(msg_json, "action");
    if (action == NULL || action->valuestring == NULL)
        return NULL;
    

    id = cJSON_GetObjectItemCaseSensitive(msg_json, "id");
    if (id == NULL || !cJSON_IsNumber(id))
        return NULL;

    login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
    if (login == NULL || login->valuestring == NULL)
        return NULL;

    password = cJSON_GetObjectItemCaseSensitive(msg_json, "password");
    if (password == NULL || password->valuestring == NULL)
        return NULL;

    key = cJSON_GetObjectItemCaseSensitive(msg_json, "key");
    if (key == NULL || key->valuestring == NULL)
        return NULL;


    chat_id = cJSON_GetObjectItemCaseSensitive(msg_json, "chat_id");
    if (chat_id == NULL || !cJSON_IsNumber(chat_id))
        return NULL;

    friend_id = cJSON_GetObjectItemCaseSensitive(msg_json, "friend_id");
    if (friend_id == NULL || !cJSON_IsNumber(friend_id))
        return NULL;

    message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
    if (message == NULL || message->valuestring == NULL)
        return NULL;
    
    message_id = cJSON_GetObjectItemCaseSensitive(msg_json, "message_id");
    if (message_id == NULL || !cJSON_IsNumber(message_id))
        return NULL;

    time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
    if (time == NULL || !cJSON_IsNumber(time))
        return NULL;

    

    

    strcpy(res->action, action->valuestring);

    res->id = id->valueint;
    strcpy(res->login, login->valuestring);
    strcpy(res->password, password->valuestring);
    strcpy(res->key, key->valuestring);

    res->chat_id = chat_id->valueint;
    res->friend_id = friend_id->valueint;
    strcpy(res->message, message->valuestring);
    res->message_id = message_id->valueint;
    res->time = time->valueint;
    
    cJSON_Delete(msg_json);

    return res;
}

