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
#define PORT 9092
#define ADDR "localhost"



// server
void *user_connect(void *cl_socket);

// database 
void sign_up(char *login,char *password);
void sign_in(char *login,char *password);
void delete_user(char *login);
void change_password(char *password);