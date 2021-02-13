#include "../inc/header.h"


char *stringify(struct info *req)
{
    char *string = NULL;

    cJSON *json_msg = cJSON_CreateObject();
    cJSON_AddStringToObject(json_msg, "action", req->action);

    cJSON_AddNumberToObject(json_msg, "id", req->id);
    cJSON_AddStringToObject(json_msg, "login", req->login);
    cJSON_AddStringToObject(json_msg, "password", req->password);
    cJSON_AddStringToObject(json_msg, "key", req->key);

    cJSON_AddNumberToObject(json_msg, "chat_id", req->chat_id);
    cJSON_AddNumberToObject(json_msg, "friend_id", req->friend_id);
    cJSON_AddStringToObject(json_msg, "message", req->message);
    cJSON_AddNumberToObject(json_msg, "message_id", req->message_id);
    cJSON_AddNumberToObject(json_msg, "time", req->time);  
    
    string = cJSON_Print(json_msg);

    cJSON_Delete(json_msg);
    string = encoding(string);
    return string;
}


struct info *parse(const char *const msg)
{

    struct info *res = malloc(sizeof(struct info));
    const cJSON *action = NULL;
    const cJSON *status = NULL;

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
    strcpy(res->action, action->valuestring);

    status = cJSON_GetObjectItemCaseSensitive(msg_json, "status");
    if (status == NULL || !cJSON_IsNumber(status))
        return NULL;
    res->status = status->valueint;

    if (res->status == 0) { // Message in case of error
        message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
        if (message == NULL || message->valuestring == NULL)
            return NULL;
        strcpy(res->message, message->valuestring);
    }
    else if (res->status == 1) { // If everything ok
        
        if ((strcmp(res->action, "sign_in") == 0) || strcmp(res->action, "auto_sign") == 0) {
            
            id = cJSON_GetObjectItemCaseSensitive(msg_json, "id");
            if (id == NULL || !cJSON_IsNumber(id))
                return NULL;
            res->id = id->valueint;
            login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
            if (login == NULL || login->valuestring == NULL)
                return NULL;
            strcpy(res->login, login->valuestring);
            password = cJSON_GetObjectItemCaseSensitive(msg_json, "password");
            if (password == NULL || password->valuestring == NULL)
                return NULL;
            strcpy(res->password, password->valuestring);
            key = cJSON_GetObjectItemCaseSensitive(msg_json, "key");
            if (key == NULL || key->valuestring == NULL)
                return NULL;            
            strcpy(res->key, key->valuestring);
        }
        else if (strcmp(res->action, "get_login_by_id") == 0) {

            login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
            if (login == NULL || login->valuestring == NULL)
                return NULL;
            strcpy(res->login, login->valuestring);
        }
        else if (strcmp(res->action, "get_chats_info") == 0) {
            
            chat_id = cJSON_GetObjectItemCaseSensitive(msg_json, "chat_id");
            if (chat_id == NULL || !cJSON_IsNumber(chat_id))
                return NULL;             
            res->chat_id = chat_id->valueint;
            login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
            if (login == NULL || login->valuestring == NULL)
                return NULL;
            strcpy(res->login, login->valuestring);
            friend_id = cJSON_GetObjectItemCaseSensitive(msg_json, "friend_id");
            if (friend_id == NULL || !cJSON_IsNumber(friend_id))
                return NULL;    
            res->friend_id = friend_id->valueint;
        }
        else if (strcmp(res->action, "add_chat") == 0) {

            chat_id = cJSON_GetObjectItemCaseSensitive(msg_json, "chat_id");
            if (chat_id == NULL || !cJSON_IsNumber(chat_id))
                return NULL;    
            res->chat_id = chat_id->valueint;
            login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");
            if (login == NULL || login->valuestring == NULL)
                return NULL;
            strcpy(res->login, login->valuestring);
            friend_id = cJSON_GetObjectItemCaseSensitive(msg_json, "friend_id");
            if (friend_id == NULL || !cJSON_IsNumber(friend_id))
                return NULL;    
            res->friend_id = friend_id->valueint;
        }
        else if (strcmp(res->action, "get_message") == 0) {
            
            id = cJSON_GetObjectItemCaseSensitive(msg_json, "id");
            if (id == NULL || !cJSON_IsNumber(id))
                return NULL;
            res->id = id->valueint;
            message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
            if (message == NULL || message->valuestring == NULL)
                return NULL;
            strcpy(res->message, message->valuestring); 
            message_id = cJSON_GetObjectItemCaseSensitive(msg_json, "message_id");
            if (message_id == NULL || !cJSON_IsNumber(message_id))
                return NULL;
            res->message_id = message_id->valueint;
            time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
            if (time == NULL || !cJSON_IsNumber(time))
                return NULL;
            res->time = time->valueint;
            chat_id = cJSON_GetObjectItemCaseSensitive(msg_json, "chat_id");
            if (chat_id == NULL || !cJSON_IsNumber(chat_id))
                return NULL;
            res->chat_id = chat_id->valueint;   
        }
        else if (strcmp(res->action, "edit_message") == 0) {
            message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
            if (message == NULL || message->valuestring == NULL)
                return NULL;
            strcpy(res->message, message->valuestring); 
        }  
        else if (strcmp(res->action, "load_messages") == 0) {

            id = cJSON_GetObjectItemCaseSensitive(msg_json, "id");
            if (id == NULL || !cJSON_IsNumber(id))
                return NULL;
            res->id = id->valueint;
            message = cJSON_GetObjectItemCaseSensitive(msg_json, "message");
            if (message == NULL || message->valuestring == NULL)
                return NULL;
            strcpy(res->message, message->valuestring); 
            message_id = cJSON_GetObjectItemCaseSensitive(msg_json, "message_id");
            if (message_id == NULL || !cJSON_IsNumber(message_id))
                return NULL;
            res->message_id = message_id->valueint;
            time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
            if (time == NULL || !cJSON_IsNumber(time))
                return NULL;
            res->time = time->valueint;
            chat_id = cJSON_GetObjectItemCaseSensitive(msg_json, "chat_id");
            if (chat_id == NULL || !cJSON_IsNumber(chat_id))
                return NULL;
            res->chat_id = chat_id->valueint;     
        }
        else if (strcmp(res->action, "open_chat") == 0) {

            time = cJSON_GetObjectItemCaseSensitive(msg_json, "time");
            if (time == NULL || !cJSON_IsNumber(time))
                return NULL;
            res->time = time->valueint;

        }
        else if (strcmp(res->action, "change_password") == 0) {
            
            password = cJSON_GetObjectItemCaseSensitive(msg_json, "password");
            if (password == NULL || password->valuestring == NULL)
                return NULL;
            strcpy(res->password, password->valuestring);
        }
    }

    
    cJSON_Delete(msg_json);

    return res;
}
