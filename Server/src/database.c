#include "../inc/header.h"

// Из числа в строку itoa()
// Из строки в число atoi()

int db_init(char *db_name)
{
    int ret;
    if (SQLITE_OK != (ret = sqlite3_initialize())) {
        printf("Failed to initialize library: %d\n", ret);
        return -1;
        sqlite3_close(db);
    }
    // open connection to a DB
    if (SQLITE_OK != (ret = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READWRITE, NULL))) {
        printf("Failed to open conn: %d\n", ret);
        return -1;
    }
    return 1;
}

void create_db(char* statement, sqlite3* db) {
   char* error = 0; 
   int rc = sqlite3_exec(db, statement, NULL, 0, &error);
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", error);
      sqlite3_free(error);
   } 
} 


bool add_user(char *login, char *password, int key)
{
    sqlite3_stmt *stmt = NULL;
    int rc;
    char *query_f = sqlite3_mprintf("INSERT INTO users VALUES(NULL,'%s','%s','%i')",
                                    login,
                                    password,
                                    key);

    rc = sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        return true;
    }
    else {
        return false;
    }   
}


bool check_login(char *login) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT LOGIN FROM users", -1, &stmt, NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char*login2 = sqlite3_column_text(stmt, 0);
        if (strcmp(login, login2) == 0) {
            sqlite3_finalize(stmt);
            return false;
        }
	}	
    sqlite3_finalize(stmt);
    return true;
}


bool verification(char *login, char *password) {

    sqlite3_stmt *stmt;
    int state = 0; // Need to equel 2
    sqlite3_prepare_v2(db, "SELECT LOGIN FROM users", -1, &stmt, NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char*login2 = sqlite3_column_text(stmt, 0);
        if (strcmp(login, login2) == 0) {   
            state += 1;    // +1 if login correct
        }
	}
    stmt = NULL;
    sqlite3_prepare_v2(db, "SELECT PASSWORD FROM users", -1, &stmt, NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char*password2 = sqlite3_column_text(stmt, 0);
        if (strcmp(password, password2) == 0) {
            state += 1; //+1 if password correct
        }
	}
    if (state == 2) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        sqlite3_finalize(stmt);
        return false;
    }  
}


void get_id_and_key(int client_socket, struct info *res) {

    ssize_t result;
    char response[BUFSIZ];
    char *temp;
    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT ID, KEY FROM users WHERE LOGIN = '%s';", res->login);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int cols = sqlite3_column_count(stmt); 
        for (int i = 0; i < cols; i++) {
            if (strcmp(sqlite3_column_name(stmt, i), "ID") == 0) {
                res->id = sqlite3_column_int(stmt, i);
            }
            else if (strcmp(sqlite3_column_name(stmt, i), "KEY") == 0) {
                strcpy(res->key, (char *)sqlite3_column_text(stmt, i));
            }
        }

    }
}


void get_login_by_id(struct info *res) {

    sqlite3_stmt *stmt = NULL;
    char *query_f = sqlite3_mprintf("SELECT LOGIN FROM users WHERE ID = '%d';", res->friend_id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(res->login, (char *)sqlite3_column_text(stmt, 0));
    }
}


int get_id_by_login(char*login) {
    int id;
    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT ID FROM users WHERE LOGIN = '%s';", login);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);   
    }
    sqlite3_finalize(stmt);
    return id;
}


bool add_chat(struct info *res) {

    sqlite3_stmt *stmt = NULL;
    int rc;
    char *query_f = sqlite3_mprintf("INSERT INTO chats VALUES(NULL,'%i','%i')",
                                    res->id,
                                    res->friend_id); // id of your friend 

    rc = sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        sqlite3_finalize(stmt);
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
    }
	sqlite3_finalize(stmt);
}


void get_chats_info(int client_socket, struct info *res) {

    sqlite3_stmt *stmt;
    char *query_1 = sqlite3_mprintf("SELECT CHAT_ID, USER1 FROM chats WHERE USER2 = '%d';", res->id);
    sqlite3_prepare_v2(db, query_1, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        
		res->chat_id = sqlite3_column_int(stmt, 0);      
		res->friend_id = sqlite3_column_int(stmt, 1);
        get_login_by_id(res); // Login
        if (res->chat_id != -1 && res->friend_id != -1 && strcmp(res->login, "") != 0)	{
            
            res->status = 1; 
            send_response(client_socket, res);
        }
    }
    stmt = NULL;
    char *query_2 = sqlite3_mprintf("SELECT CHAT_ID, USER2 FROM chats WHERE USER1 = '%d';", res->id);
    sqlite3_prepare_v2(db, query_2, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        res->chat_id = sqlite3_column_int(stmt, 0);      
		res->friend_id = sqlite3_column_int(stmt, 1);
        get_login_by_id(res); // Login
        if (res->chat_id != -1 && res->friend_id != -1 && strcmp(res->login, "") != 0)	{

            res->status = 1; 
            send_response(client_socket, res);
        }
    }

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
        char *query_2 = sqlite3_mprintf("SELECT max(MESSAGE_ID) FROM messages WHERE SENDER = '%d';", res->id);
        sqlite3_prepare_v2(db, query_2, -1, &stmt, 0);
        while (sqlite3_step(stmt) != SQLITE_DONE) {
            
            res->message_id = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        strcpy(res->message, "Message hasn`t added!");
        return false;
    }
    sqlite3_finalize(stmt);
}


bool delete_message(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("DELETE FROM messages WHERE MESSAGE_ID = '%d' AND SENDER = '%d';", res->message_id, res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        strcpy(res->message, "Message hasn`t deleted");
        sqlite3_finalize(stmt);
        return false;
    }
}

void get_message(struct info *res) {

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
			case (SQLITE_FLOAT):
				printf("%g, ", sqlite3_column_double(stmt, i));
				break;
                
			default:
				break;
			}
		}
		printf("\n");
     }
}

bool key_checking(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("SELECT KEY WHERE ID = '%d';", res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        if (strcmp(res->key, sqlite3_column_text(stmt, 0)) == 0) { 
            sqlite3_finalize(stmt);
            return true;
        }
    }
    sqlite3_finalize(stmt);
    return false;
}

bool delete_user(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("DELETE FROM users WHERE ID = '%d';", res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        strcpy(res->message, "User isn`t deleted");
        sqlite3_finalize(stmt);
        return false;
    }
}

bool change_password(struct info *res) {

    sqlite3_stmt *stmt;
    char *query_f = sqlite3_mprintf("UPDATE users SET PASSWORD = '%s' WHERE ID = '%d';", res->password, res->id);
    sqlite3_prepare_v2(db, query_f, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        strcpy(res->message, "Password hasn`t changed");
        sqlite3_finalize(stmt);
        return false;
    }
}

void load_messages(int client_socket, struct info *res) {

    sqlite3_stmt *stmt;
    char *query_1 = sqlite3_mprintf("SELECT MESSAGE_ID, SENDER, MESSAGE, TIME FROM messages WHERE CHAT_ID = '%d' ORDER BY TIME ASC;", res->chat_id);
    sqlite3_prepare_v2(db, query_1, -1, &stmt, 0);
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        res->message_id = sqlite3_column_int(stmt, 0);
        res->id = sqlite3_column_int(stmt, 1);
        strcpy(res->message, sqlite3_column_text(stmt, 2));
        res->time = sqlite3_column_int(stmt, 3);

        if (res->chat_id != -1 || res->id != -1 || strcmp(res->login, "") != 0)	{
            
            res->status = 1; 
            send_response(client_socket, res);
        }
    }
    sqlite3_finalize(stmt);
}

/*
void db_print_all() { //db_user_t user
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT * FROM users", -1, &stmt, NULL);
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
			case (SQLITE_FLOAT):
				printf("%g, ", sqlite3_column_double(stmt, i));
				break;
                
			default:
				break;
			}
		}
		printf("\n");

	}

	sqlite3_finalize(stmt);

	sqlite3_close(db);


}*/

