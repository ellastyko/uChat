#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include<stdbool.h>
#include <netdb.h>
#include <pthread.h>
#include <gtk/gtk.h>
#include<stdlib.h>
#define PORT 8000
#define ADDR "localhost"
#include "cJSON.h"
#include <malloc.h>

//actions
void sign_up(int client_socket);
void sign_in(int client_socket);
//bool delete_user(int client_socket);
//bool change_password(int client_socket);
//bool send_message(int client_socket);

// socket
int Socket();

// useful
int validation(char *login, char *password);
struct info *parse(const char *const msg);
char *stringify(struct info *info);

