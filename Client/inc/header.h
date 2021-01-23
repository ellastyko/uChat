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
#define PORT 8028
#define ADDR "localhost"
#include "../../lib/cJSON.h"
#include <malloc.h>
#include <pthread.h>


char _id_[20]; // id которое мы получаем после регистрации
char _key_[10];

char _login_[20];
char _password_[20];


// universal structure for all types of send and receive
struct info {
    /* Request */
    char action[20]; //
    char login[20]; // user or sender of message
    char password[25]; 
    char message[500];
    char time[50]; // time when message was sended
    char receiver[20]; // receiver of message
    char key[10];
    /* Response */
    char status[1]; // Y or N
    char response[50];  
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
int validation(char *login, char *password);
struct info *parse(const char *const msg);
char *stringify(struct info *info);
int time_converter(int time);

void *reading();
