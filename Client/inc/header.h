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
#define PORT 8035
#define ADDR "localhost"
#include "../../lib/cJSON.h"
#include <malloc.h>
#include <pthread.h>


typedef struct client_info
{
    int id; 
    char key[16];
    char login[20];
    char password[30];
} client_info_t;
struct client_info cl_info;

// universal structure for all types of send and receive
struct info {
    char action[20]; 
    int status; // 0 or 1

    int id;
    char login[20]; 
    char password[25]; 
    char key[20];

    int chat_id; 
    char message[500];
    int message_id; 
    int time; // time when message was sended
};


//actions
void send_to_server(char *buf);
void sign_up();
void sign_in();
bool delete_user();
bool change_password();
bool send_message();
//bool delete_message();


// socket
void Socket();


// useful
char *checking_local_storage();
bool validation(char *login, char *password);
struct info *parse(const char *const msg);
char *stringify(struct info *info);
int time_converter(int time);

void *reading();
void type_of_response(struct info *res);