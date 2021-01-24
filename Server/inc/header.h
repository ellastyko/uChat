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

#define PORT 8035
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
    char message[500];
    int message_id;
    int time; 
    
    int status; // 0 - err // 1 -ok
};


extern sqlite3 *db;

//parsing
char *stringify(struct info *req);
struct info *parse(const char *const msg);
int type_of_request(char *str, int client_socket);
int key();

// database
int db_init(char *db_name);
void create_db(char* statement, sqlite3* db);

bool check_login(char *login);
bool db_add_user(char *login, char *password, int key);

bool verification(char *login, char *password);
void get_id_and_key(int client_socket, struct info *res);
void get_login_by_id(int client_socket, int id);

void db_print_all();
