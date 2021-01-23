#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
#include "../../lib/cJSON.h"
#include <malloc.h>
#include <time.h>

#define PORT 8025
#define ADDR "localhost"

struct info
{
    /* Request */
    char action[10];
    char login[20];
    char password[25];
    char message[500];
    char time[50]; // use time in request AND response
    char receiver[20];
    char key[10];
    /* Response */
    char status[1]; // Y or N
    char response[500];
};


extern sqlite3 *db;

#pragma region db_entyties
typedef struct db_user_s
{
    int user_id; 
    char *login;
    char *password;
    int auth_key;
} db_user_t;

/*typedef struct db_messages_s
{
    uint64_t message_id; // PK

    uint64_t chat_id; // FK
    uint64_t user_id; // FK

    char message[BUFSIZ];
    time_t time;

} db_messages_t;

typedef struct db_chats_s
{
    uint64_t chat_id; // PK

    char *name;
    char *type;
} db_chats_t;

typedef struct db_users_chats_s
{
    uint64_t user_id; // PK FK
    uint64_t chat_id; // PK FK
} db_users_chats_t;*/
#pragma endregion



//parsing
char *stringify(struct info *req);
struct info *parse(const char *const msg);
void type_of_request(char *str, int client_socket);
int key();
int lenth_of_string(const char *s);

// database
int db_init(char *db_name);
void create_db(char* statement, sqlite3* db);
int db_add_user(db_user_t user);
int db_print_all();
char* concat(char* s1, char* s2);