#include "../inc/header.h"

int auto_sign() {
     
    client_info_t *ld;
    ld = get_local_data(LD_PATH);

    if (ld) {
        strcpy(cl_info.login, ld->login);
        strcpy(cl_info.password, ld->password);
        //sign_in();
        return 0;
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