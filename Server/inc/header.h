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
#include <malloc.h> // #include <malloc/malloc.h>
#include <locale.h>
#define PORT 8230
#define ADDR "localhost"


extern sqlite3 *db;
int online;

struct info
{
    /* Request */
    char action[25];

    int id;
    char login[40];
    char password[40];
    char key[20];

    int chat_id;
    int friend_id;
    char message[BUFSIZ];
    int message_id;
    int time; 
    
    int status; // 0 - err // 1 -ok
};

struct online_users { 

    int client_socket;
    int id;
};
struct online_users user[200];


void *connection(void *cl_socket);

// useful
int get_free();
void to_empty_online();
void print_all();
void to_be_online(int client_socket, struct info *res);
int delete_online(int client_socket);
int find_friend(int friend_id);


// requests
void type_of_request(char *str, int client_socket);
void send_response(int client_socket, struct info *res);
bool key_checking(struct info *res);

// database
int db_init(char *db_name);
int create_db(const char *up_script_path);

// sign up
bool check_login(char *login);
bool add_user(char *login, char *password, int key);

// Sign in
bool verification(char *login, char *password);
void get_id_and_key(struct info *res);
void get_chat_id_by_users(struct info *res);
bool update_time(int id, int ttime);


// Get login by id
void get_login_by_id(struct info *res);

// Add chat
int get_id_by_login(char*login);
bool add_chat(struct info *res);


// get_chat_info
void get_chats_info(int client_socket, struct info *res);

// Send message
bool save_message(struct info *res);
void get_all();

// Delete message
bool delete_message(struct info *res);
// Edit message
bool edit_message(struct info *res);

// Delete user
bool delete_user(struct info *res);

// Change password
bool change_password(struct info *res);

// Open chat and load messages
bool take_time(struct info *res);
void load_messages(int client_socket, struct info *res);

// useful
int key();
char *decoding(char *str);
char *encoding(char *str);

// json
char *stringify(struct info *req);
struct info *parse(const char *const msg);