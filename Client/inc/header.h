#define _GNU_SOURCE
#define PORT 8238
#define ADDR "localhost"

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
#include "../../lib/cJSON.h"
#include <malloc.h> // #include <malloc/malloc.h>
#include <pthread.h>
#include <time.h>
int client_socket;


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

    char action[25]; 
    int status; // 0 or 1

    int id;
    char login[20]; 
    char password[25]; 
    char key[20];

    int chat_id; 
    int friend_id;
    char message[500];
    int message_id; 
    int time; // time when message was sended
};

struct chats {
    int chat_id;
    int friend_id;
    char login[20];
};
struct chats chat[100];

// Prepare to work
void prepare();

//actions
void send_to_server(char *buf);
void sign_up();
void sign_in();

void add_chat();
void open_chat();
void delete_user();
void change_password();
void send_message();
void delete_message();
void get_chats_info();
void availability_of_login();
void search_friend();

// socket
int Socket();


// useful
int local_storage();
bool validation();
void valid_of_log_in();
struct info *parse(const char *const msg);
char *stringify(struct info *info);
char time_converter(int time);
void push_chat(int chat_id, int friend_id, char*login);
void print_all();
int get_free();
int search(char *name);
char *decoding(char *str);
char *encoding(char *str);

// reading
void *reading();
void type_of_response(struct info *res);

// GTK
void destroy();
void SIGN_BOXES();
void MAIN_BOXES();
void NO_CONNECTION_BOX();  
void no_connection();
void to_sign_up();
void to_log_in();
void valid_login();
void valid_password();
void open_settings();
void search_friend();


int STATE; // 0 - sign in  / 1 - sign up / 2 - main
// Widgets
GtkBuilder *builder;

GtkWidget *window;

// Style
GtkCssProvider *style;

// Log in and sign up
GtkContainer *SignLog;
GtkContainer *SignBox;

GtkWidget     *login;
GtkWidget     *password;
GtkWidget     *repeat;
GtkWidget     *hint;

// Log in
GtkWidget      *To_Sign;
GtkWidget      *Log_in;
// Sign up
GtkWidget      *To_Log;
GtkWidget      *Sign_up;

/////////////////////////////

// Main
GtkContainer      *Main;

    // Left Sidebar
    GtkContainer       *friends;
        GtkWidget       *Open_settings;
        GtkWidget       *Search_Friends;

    GtkContainer       *settings;
        GtkWidget       *Open_Friends;
        GtkWidget       *Change_password;
        GtkWidget       *Log_out;
        GtkWidget       *Theme;

    // your chat
    GtkContainer       *your_chat;
        GtkWidget       *Message_Box;
        GtkWidget       *Select_file_button;
        GtkWidget       *Send_button;

///////////////////////////////

// No connection window
GtkContainer *Connection_lost;    
GtkWidget *Reconnect_button; 