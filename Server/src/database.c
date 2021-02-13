#include "../inc/header.h"

// Из числа в строку itoa()
// Из строки в число atoi()

int db_init(char *db_name)
{
    int ret;

    if (SQLITE_OK != (ret = sqlite3_initialize()))
    {
        printf("Failed to initialize library: %d\n", ret);
        return -1;
        sqlite3_close(db);
    }
    // open connection to a DB
    if (SQLITE_OK != (ret = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READWRITE, NULL)))
    {
        printf("Failed to open conn: %d\n", ret);
        return -1;
    }

    return create_db("Server/db/db_up.sql");
}

//создает таблицы в базе, если они еще не созданы. Вызывается в db_init
int create_db(const char *up_script_path)
{
    FILE *fp;
    char *error = 0;
    char buff[BUFSIZ];
    char ch;
    int i;

    fp = fopen(up_script_path, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open script file\n");
        return -1;
    }

    for (i = 0; (ch = fgetc(fp)) != EOF; i++)
    {
        buff[i] = ch;
    }

    buff[i + 1] = '\0';

    int rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, 0, &error);

    rc = sqlite3_exec(db, buff, NULL, 0, &error);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
        return -1;
    }
    return 0;
}


bool add_user(char *login, char *password, int key)
{
    sqlite3_stmt *stmt = NULL;
    int ttime = time(NULL);
    char *query_f = sqlite3_mprintf("INSERT INTO users VALUES(NULL,'%s','%s','%i', '%i')",
                                    login,
                                    password,
                                    key, 
                                    ttime);

    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_free(query_f);  
        return true;
    }
    else {
        sqlite3_free(query_f);  
        return false;
    }   
}


bool update_time(int id, int ttime)
{
    sqlite3_stmt *stmt = NULL;

    char *query_f = sqlite3_mprintf("UPDATE users SET TIME = '%d' WHERE USER_ID = '%d';", ttime, id);

    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_free(query_f);  
        sqlite3_finalize(stmt);
        
        return true;
    }
    else {
        sqlite3_free(query_f);  
        sqlite3_finalize(stmt);
        return false;
    }   
}


bool take_time(struct info *res) {
    
    sqlite3_stmt *stmt = NULL;
    char *query_f = sqlite3_mprintf("SELECT TIME FROM users WHERE USER_ID = '%d';", res->friend_id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, NULL);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        res->time = sqlite3_column_int(stmt, 0);  
        return true;   
	} 
    sqlite3_free(query_f);
    sqlite3_finalize(stmt);
    return false;
}


bool check_login(char *login) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT LOGIN FROM users", -1, &stmt, NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char*login2 = (const char *)sqlite3_column_text(stmt, 0);
        if (strcmp(login, login2) == 0) {
            sqlite3_finalize(stmt);
            return false;
        }
	}	
    sqlite3_finalize(stmt);
    return true;
}


bool verification(char *login, char *password) {

    sqlite3_stmt *stmt = NULL;
    char *query_f = sqlite3_mprintf("SELECT PASSWORD FROM users WHERE LOGIN = '%s';", login);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, NULL);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char*pass = (const char *)sqlite3_column_text(stmt, 0);
        if (strcmp(password, pass) == 0) {   
            sqlite3_free(query_f);
            sqlite3_finalize(stmt);
            return true;
        }
	} 
    sqlite3_free(query_f);
    sqlite3_finalize(stmt);
    return false;
}


void get_id_and_key(struct info *res) {


    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT USER_ID, KEY FROM users WHERE LOGIN = '%s';", res->login);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int cols = sqlite3_column_count(stmt); 
        for (int i = 0; i < cols; i++) {
            if (strcmp(sqlite3_column_name(stmt, i), "USER_ID") == 0) {
                res->id = sqlite3_column_int(stmt, i);
            }
            else if (strcmp(sqlite3_column_name(stmt, i), "KEY") == 0) {
                strcpy(res->key, (char *)sqlite3_column_text(stmt, i));
            }
        }

    }
    sqlite3_free(query_f);  
    sqlite3_finalize(stmt);
}


void get_login_by_id(struct info *res) {

    sqlite3_stmt *stmt = NULL;
    char *query_f = sqlite3_mprintf("SELECT LOGIN FROM users WHERE USER_ID = '%d';", res->friend_id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(res->login, (char *)sqlite3_column_text(stmt, 0));
    }
    sqlite3_free(query_f);  
    sqlite3_finalize(stmt);
}


int get_id_by_login(char*login) {
    int id;
    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT USER_ID FROM users WHERE LOGIN = '%s';", login);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);   
    }
    sqlite3_finalize(stmt);
    sqlite3_free(query_f);  
    return id;
}


bool add_chat(struct info *res) {

    sqlite3_stmt *stmt = NULL;
    char *query_f = sqlite3_mprintf("INSERT INTO chats VALUES(NULL,'%i','%i')",
                                    res->id,
                                    res->friend_id); // id of your friend 

    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);  
        return true;
    }
    else {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);  
        return false;
    }   
}


void get_chat_id_by_users(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_1 = sqlite3_mprintf("SELECT CHAT_ID FROM chats WHERE USER1 = '%d' AND USER2 = '%d';", res->id, res->friend_id);
    sqlite3_prepare_v2(db, query_1, -1, &stmt, 0);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
		res->chat_id = sqlite3_column_int(stmt, 0);         
	}
    stmt = NULL;
    if (res->chat_id == -1) { 
        char *query_2 = sqlite3_mprintf("SELECT CHAT_ID FROM chats WHERE USER2 = '%d' AND USER1 = '%d';", res->id, res->friend_id);
        sqlite3_prepare_v2(db, query_2, -1, &stmt, 0);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            res->chat_id = sqlite3_column_int(stmt, 0);   
        }
        sqlite3_free(query_2);
    }
    sqlite3_free(query_1);  
	sqlite3_finalize(stmt);
}


void get_chats_info(int client_socket, struct info *res) {

    sqlite3_stmt *stmt;
    char *query_1 = sqlite3_mprintf("SELECT CHAT_ID, USER1 FROM chats WHERE USER2 = '%d';", res->id);
    sqlite3_prepare_v2(db, query_1, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        
		res->chat_id = sqlite3_column_int(stmt, 0);      
		res->friend_id = sqlite3_column_int(stmt, 1);
        get_login_by_id(res); 
        if (res->chat_id != -1 && res->friend_id != -1 && strcmp(res->login, "") != 0)	{
            
            res->status = 1; 
            send_response(client_socket, res);
        }
    }  
    stmt = NULL;
    sqlite3_free(query_1);
    
    
    char *query_2 = sqlite3_mprintf("SELECT CHAT_ID, USER2 FROM chats WHERE USER1 = '%d';", res->id);
    sqlite3_prepare_v2(db, query_2, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        res->chat_id = sqlite3_column_int(stmt, 0);      
		res->friend_id = sqlite3_column_int(stmt, 1);
        if (res->id == res->friend_id) 
            continue;
        get_login_by_id(res); 
        if (res->chat_id != -1 && res->friend_id != -1 && strcmp(res->login, "") != 0)	{

            res->status = 1; 
            send_response(client_socket, res);
        }
    }
    sqlite3_free(query_2);
	sqlite3_finalize(stmt);
}


bool save_message(struct info *res)
{
    sqlite3_stmt *stmt = NULL;

    char *query_f = sqlite3_mprintf("INSERT INTO messages VALUES(NULL, '%d','%s', '%d' , '%d')",
                                    res->id,
                                    res->message,
                                    res->time,
                                    res->chat_id);

    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        printf("Message added!\n");
        stmt = NULL;
        char *query_2 = sqlite3_mprintf("SELECT max(MESSAGE_ID) FROM messages WHERE USER_ID = '%d';", res->id);
        sqlite3_prepare_v2(db, query_2, -1, &stmt, 0);
        while (sqlite3_step(stmt) != SQLITE_DONE) {
            
            res->message_id = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return true;
    }
    else {
        strcpy(res->message, "Message hasn`t added!");
        sqlite3_free(query_f);
        return false;
    }
    sqlite3_finalize(stmt);
}


bool delete_message(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("DELETE FROM messages WHERE MESSAGE_ID = '%d';", res->message_id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return true;
    }
    else {
        strcpy(res->message, "Message hasn`t deleted");
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return false;
    }
}

bool edit_message(struct info *res) {

    sqlite3_stmt *stmt; 
    char *query_f = sqlite3_mprintf("UPDATE messages SET MESSAGE = '%s' WHERE MESSAGE_ID = '%d' AND USER_ID = '%d';", res->message, res->message_id, res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return true;
    }
    else {
        strcpy(res->message, "Message hasn`t deleted");
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return false;
    }
}

void get_all() {

    sqlite3_stmt *stmt = NULL;

    char *query_f = sqlite3_mprintf("SELECT * FROM messages;");

    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);

    while (sqlite3_step(stmt) != SQLITE_DONE) {

        int i;
		int num_cols = sqlite3_column_count(stmt);

        for (i = 0; i < num_cols; i++)
		{
			switch (sqlite3_column_type(stmt, i))
			{
			case (SQLITE3_TEXT):
				printf("%s, ", sqlite3_column_text(stmt, i));
				break;
			case (SQLITE_INTEGER):
				printf("%d, ", sqlite3_column_int(stmt, i));
				break;
			default:
				break;
			}
		}
		printf("\n");
     }
     sqlite3_free(query_f);
}

bool key_checking(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT KEY WHERE USER_ID = '%d';", res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        if (strcmp(res->key, (char *)sqlite3_column_text(stmt, 0)) == 0) { 
            sqlite3_finalize(stmt);
            return true;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_free(query_f);
    return false;
}

bool delete_user(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("DELETE FROM users WHERE USER_ID = '%d';", res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return true;
    }
    else {
        strcpy(res->message, "User isn`t deleted");
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return false;
    }
}

bool change_password(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("UPDATE users SET PASSWORD = '%s' WHERE USER_ID = '%d';", res->password, res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return true;
    }
    else {
        strcpy(res->message, "Password hasn`t changed");
        sqlite3_finalize(stmt);
        sqlite3_free(query_f);
        return false;
    }
}

void load_messages(int client_socket, struct info *res) {

    sqlite3_stmt *stmt;
    char *query_1 = sqlite3_mprintf("SELECT MESSAGE_ID, USER_ID, MESSAGE, TIME FROM messages WHERE CHAT_ID = '%d' ORDER BY TIME ASC;", res->chat_id);
    sqlite3_prepare_v2(db, query_1, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        res->message_id = sqlite3_column_int(stmt, 0);
        res->id = sqlite3_column_int(stmt, 1);
        strcpy(res->message, (char *)sqlite3_column_text(stmt, 2));
        res->time = sqlite3_column_int(stmt, 3);

        if (res->chat_id != -1 || res->id != -1 || strcmp(res->login, "") != 0)	{
            
            res->status = 1; 
            send_response(client_socket, res);
        }
    }
    sqlite3_free(query_1);
    sqlite3_finalize(stmt);
}

