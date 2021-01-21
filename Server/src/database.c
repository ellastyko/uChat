#include "../inc/header.h"

char* concat(char* s1, char* s2) {
   int len1 = strlen(s1);
   int len2 = strlen(s2);                      
   char *result = malloc(len1 + len2 + 1);
   if (!result) {
      fprintf(stderr, "malloc() failed: insufficient memory!\n");
      return NULL;
   }
   memcpy(result, s1, len1);
   memcpy(result + len1, s2, len2 + 1);    
   return result;
}
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



int db_add_user(db_user_t user)
{
    sqlite3_stmt *res = NULL;
    int rc;
    char *query_f = sqlite3_mprintf("INSERT INTO users VALUES(NULL,'%s','%s','%i')",
                                    user.login,
                                    user.password,
                                    user.auth_key);

    rc = sqlite3_prepare_v2(db, query_f, -1, &res, 0);
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
        printf("Inserter!\n");
    }
    else {
        printf("Not inserter!\n");
        return 0;
    }
    return 1;
}

// int db_print_all() { //db_user_t user

// }

/*int db_add_chat(db_chats_t chat)
{
    sqlite3_stmt *res = NULL;
    int rc;

    char *query_f = sqlite3_mprintf("INSERT INTO chats VALUES(NULL,'%s','%s')",
                                    chat.name,
                                    chat.type);

    rc = sqlite3_prepare_v2(db, query_f, -1, &res, 0);

    rc = sqlite3_step(res);

    if (rc == SQLITE_DONE)
    {
        printf("Inserter!\n");
    }
    else
    {
        printf("Not inserter!\n");
        return 0;
    }

    rc = sqlite3_finalize(res);
    return 1;
}

int db_add_message(db_messages_t message)
{
    sqlite3_stmt *res = NULL;
    int rc;

    char *query_f = sqlite3_mprintf("INSERT INTO messages VALUES(NULL, %d,%d,'%s',%d)",
                                    message.chat_id,
                                    message.user_id,
                                    message.message,
                                    message.time);

    rc = sqlite3_prepare_v2(db, query_f, -1, &res, 0);

    rc = sqlite3_step(res);

    if (rc == SQLITE_DONE)
    {
        printf("Inserter!\n");
    }
    else
    {
        printf("Not inserter!\n");
        return 0;
    }

    rc = sqlite3_finalize(res);

    return 1;
}

int db_add_user_chat(db_users_chats_t user_chat)
{
    return 1;
}*/

/*int update_user()
{
}

bool sign_up(char *login, char *password)
{
    //Sign up
    return true;
}

bool sign_in(char *login, char *password)
{
    // Sign in
    return true;
}

bool delete_user(char *login)
{
    // Delete user
    return true;
}

bool send_message(char *login, char *time, char *receiver)
{
    // Send message from login1 to login2
    return true;
}

// Делать в последнюю очередь
bool change_password(char *login, char *password)
{
    // Change of password for login(пользователь с таким логином)
}
bool delete_message(char *login)
{
    // Delete message
}*/

/* 
CREATE TABLE `users`
(
 `user_id`           integer,
 `username`          varchar(50) NOT NULL ,
 `password`          varchar(50) NOT NULL ,
 `registration_time` datetime NOT NULL ,
 `auth_key`          varchar(50) NOT NULL ,
 `auth_key_exp`      datetime NOT NULL ,

PRIMARY KEY (`user_id`)
);

 */