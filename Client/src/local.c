#include "../inc/header.h"

int auto_sign() {
     
    client_info_t *ld;
    ld = get_local_data(LD_PATH);

    if (ld) {

        struct info req;

        strcpy(req.action, "auto_sign");
        req.id = 0;
        strcpy(req.login, ld->login);
        strcpy(req.password, ld->password);
        strcpy(req.key, "");

        req.chat_id = 0;
        req.friend_id = -1;
        strcpy(req.message, "");
        req.message_id = -1;
        req.time = -1;
        char *buf = stringify(&req);
        if (send_to_server_and_get(buf) == 1) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else { 
        printf("Cannt read localdata");
        return EXIT_FAILURE;
    }
}


int update_localdata(client_info_t *data, const char *const ld_path)
{
    if (!data) {
        return 0;
    }

    char *data_json = localdata_to_json(data);
    FILE *fp;

    fp = fopen(ld_path, "w");

    if (fp) {
        fprintf(fp, "%s", data_json);
        fclose(fp);
    }
    else {
        printf("Error while opening the file\n");
        return 0;
    }

    return 1;
}

client_info_t *get_local_data(char *ld_path)
{
    client_info_t *res;
    char *fcontent = NULL;
    long fsize = 0;
    FILE *fp;

    fp = fopen(ld_path, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fcontent = malloc(fsize);
        fread(fcontent, 1, fsize, fp);

        if (fcontent) {
            res = parse_localdata(fcontent);

            if (!res) {
                printf("Cann`t parse localdata\n");
                return NULL;
            }

            free(fcontent);
            fclose(fp);

            return res;
        }
        else {
            printf("Data is null\n");
            return NULL;
        }
    }
    else {
        printf("File doesn`t exists\n");
        return NULL;
    }

    return NULL;
}


client_info_t *parse_localdata(const char *const data)
{
    client_info_t *res = malloc(sizeof(client_info_t));
    const cJSON *login = NULL;
    const cJSON *password = NULL;

    cJSON *msg_json = cJSON_Parse(data);

    login = cJSON_GetObjectItemCaseSensitive(msg_json, "login");

    if (login == NULL || login->valuestring == NULL)
        return NULL;

    password = cJSON_GetObjectItemCaseSensitive(msg_json, "password");

    if (password == NULL || login->valuestring == NULL)
        return NULL;

    strcpy(res->login, login->valuestring);
    strcpy(res->password, password->valuestring);

    cJSON_Delete(msg_json);

    return res;
}


char *localdata_to_json(client_info_t *data)
{
    char *string = NULL;

    cJSON *json_data = cJSON_CreateObject();

    cJSON_AddStringToObject(json_data, "login", data->login);

    cJSON_AddStringToObject(json_data, "password", data->password);

    string = cJSON_Print(json_data);

    cJSON_Delete(json_data);

    return string;
}


/* Config */

int config() {
     
    config_t *ld;
    ld = get_config(CONFIG_PATH);

    if (ld) {
        Config.theme = ld->theme;
        Config.notifications = ld->notifications;
        Config.localization = ld->localization;
        return 0;
    }
    else { 
        // Config.theme = 0;
        // Config.notifications = 0;
        // Config.localization = 0;
        pre_update_config();
        printf("Cann`t read config");
        return EXIT_FAILURE;
    }
}



int update_config(config_t *data, const char *const config_path)
{
    if (!data) {
        return 0;
    }

    char *config_json = config_to_json(data);
    FILE *fp;

    fp = fopen(config_path, "w");

    if (fp) {
        fprintf(fp, "%s", config_json);
        fclose(fp);
    }
    else {
        printf("Error while opening the file\n");
        return 0;
    }

    return 1;
}

config_t *get_config(char *config_path) {

    config_t *res;
    char *fcontent = NULL;
    long fsize = 0;
    FILE *fp;

    fp = fopen(config_path, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fcontent = malloc(fsize);
        fread(fcontent, 1, fsize, fp);

        if (fcontent) {
            res = parse_config(fcontent);

            if (!res) {
                printf("Cann`t parse config\n");
                return NULL;
            }

            free(fcontent);
            fclose(fp);

            return res;
        }
        else {
            printf("Data is null\n");
            return NULL;
        }
    }
    else {
        printf("File doesn`t exists\n");
        return NULL;
    }

    return NULL;
}


config_t *parse_config(const char *const data)
{
    config_t *res = malloc(sizeof(config_t));
    const cJSON *theme = NULL;
    const cJSON *notifications = NULL;
    const cJSON *localization = NULL;

    cJSON *msg_json = cJSON_Parse(data);

    theme = cJSON_GetObjectItemCaseSensitive(msg_json, "theme");
    if (theme == NULL || !cJSON_IsNumber(theme))
        return NULL;


    notifications = cJSON_GetObjectItemCaseSensitive(msg_json, "notifications");
    if (notifications == NULL || !cJSON_IsNumber(notifications))
        return NULL;

    localization = cJSON_GetObjectItemCaseSensitive(msg_json, "localization");
    if (localization == NULL || !cJSON_IsNumber(localization))
        return NULL;

    res->theme = theme->valueint;
    res->notifications = notifications->valueint;
    res->localization = localization->valueint;

    cJSON_Delete(msg_json);

    return res;
}


char *config_to_json(config_t *data)
{
    char *string = NULL;

    cJSON *json_data = cJSON_CreateObject();

    cJSON_AddNumberToObject(json_data, "theme", data->theme);

    cJSON_AddNumberToObject(json_data, "notifications", data->notifications);

    cJSON_AddNumberToObject(json_data, "localization", data->localization);

    string = cJSON_Print(json_data);

    cJSON_Delete(json_data);

    return string;
}


