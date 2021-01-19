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
#include "cJSON.h"
#include <malloc.h>
#define PORT 8000
#define ADDR "localhost"



//parsing
char *type_of_request(char *str);
// database 
void sign_up(char *login,char *password);
void sign_in(char *login,char *password);
bool send_message(char *login1, char *login2);
bool delete_user(char *login);
bool change_password(char *login, char *password);