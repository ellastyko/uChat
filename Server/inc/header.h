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

#define PORT 8039
#define ADDR "localhost"

struct info
{
    /* Request */
    char action[15];

    int id;
    char login[20];
    char password[25];
    char key[20];

    int chat_id;
    int friend_id;
    char message[500];
    int message_id;
    int time; 
    
    int status; // 0 - err // 1 -ok
};


extern sqlite3 *db;

//parsing
int type_of_request(char *str, int client_socket);
void send_response(int client_socket, struct info *res);


// database
int db_init(char *db_name);
void create_db(char* statement, sqlite3* db);

// sign up
bool check_login(char *login);
bool add_user(char *login, char *password, int key);

// Sign in
bool verification(char *login, char *password);
void get_id_and_key(int client_socket, struct info *res);
void get_chat_id_by_users(struct info *res);

// Get login by id
void get_login_by_id(struct info *res);

// Add chat
int get_id_by_login(char*login);
bool add_chat(struct info *res);


// get_chat_info
void get_chats_info(int client_socket, struct info *res);

// useful
char *stringify(struct info *req);
struct info *parse(const char *const msg);
int key();