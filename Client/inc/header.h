#define _GNU_SOURCE

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
#include <locale.h>

#define PORT 8230
#define ADDR "localhost"
#define LD_PATH "Client/storage/data.txt"
#define CONFIG_PATH "Client/storage/config.txt"

int client_socket;
int FOCUS;
typedef struct client_info
{
    int id; 
    char key[16];
    char login[20];
    char password[30];
} client_info_t;
struct client_info cl_info;

client_info_t *parse_localdata(const char *const data);
client_info_t *get_local_data(char *ld_path);
int update_localdata(client_info_t *data, const char *const ld_path);
char *localdata_to_json(client_info_t *data);

/* CONFIG */
typedef struct config
{
    int theme; // 0 - day | 1 - dark
    int notifications; // 0 - no | 1 - yes
    int localization; // 0 - en | 1 - ru
} config_t;
config_t Config;

int config();
config_t *parse_config(const char *const data);
config_t *get_config(char *config_path);
int update_config(config_t *data, const char *const config_path);
char *config_to_json(config_t *data);



// universal structure for all types of send and receive
struct info {

    char action[25]; 
    int status; // 0 or 1

    int id;
    char login[40]; 
    char password[40]; 
    char key[20];

    int chat_id; 
    int friend_id;
    char message[BUFSIZ];
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
int send_to_server_and_get(char *buf);
void send_to_server(char *buf);

void sign_up();
void sign_in();

void add_chat();
void open_chat(GtkButton *button, gpointer *user_data);
void delete_user();
void change_password();
void send_message();
void delete_message();
void get_chats_info();
void availability_of_login();
void search_friend();


// socket
int Socket();
void reading_thread();


// useful
int auto_sign();
bool validation();
bool validation_of_new_password();
void valid_of_log_in();
struct info *parse(const char *const msg);
char *stringify(struct info *info);
//char time_converter(int time);
char *decoding(char *str);
char *encoding(char *str);
void create_status(int ttime);

// reading
void *reading();
void type_of_response(struct info *res);

// GTK
void SIGN_BOXES();
void MAIN_BOXES();
void NO_CONNECTION_BOX();  

void destroy();
void no_connection();
void to_sign_up();
void to_log_in();
void valid();
void open_settings();
void search_friend();
void open_main();
void theme ();
void *pre_update_config();
void create_chat(int chat_id, char *login);
void create_message(int id, char *message, int message_id, char* time);
void scrolling();

void change_lang();
void notify();
void attach_file();

// structs
void push_chat(int chat_id, int friend_id, char*login);
void print_all();
int get_free();
int search_chat_id(char *login);
int search(char *name);
int friend_id();
char *search_login(int chat_id);

int STATE; // 0 - sign in  / 1 - sign up / 2 - main / 3 - reconnect

void *notific();
GtkWidget *notification_name;
GtkWidget *notification_message;

// Widgets
GtkBuilder *builder;

GtkWidget *window;
GtkWidget *notification;
GtkWidget *Confirm;

// Style
GtkCssProvider *style;
GtkCssProvider *style_dark;

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
    GtkOverlay      *sidebar_overlay;
        GtkContainer      *friends;
            GtkWidget       *Open_settings;
            GtkWidget       *Search_Friends;
                GtkWidget       *error_box1;
                GtkWidget       *error_message1;
            GtkWidget       *fbox;
                GtkWidget       *friend_box;

        GtkContainer       *settings;
            GtkWidget       *Open_Friends;
            GtkWidget       *Change_password;
                GtkWidget       *new_password;
                GtkWidget       *error_box2;
                GtkWidget       *error_message2;

        GtkWidget       *Log_out;
        GtkWidget       *Theme;
        GtkWidget       *Localization;
        GtkWidget       *Notifications;

    // your chat
    GtkContainer        *header_box;
    GtkContainer       *your_chat;
        GtkWidget       *your_friend;
        GtkWidget       *friend_status;

        GtkWidget       *Message_Box;
        GtkWidget       *Edit_button;   
        GtkWidget       *Delete_button;
        GtkWidget       *Send_button;
        
        GtkWidget       *Scroll;
            GtkWidget       *cbox;
                GtkWidget       *chat_box;

///////////////////////////////

// No connection window
GtkContainer *Connection_lost;    
    GtkWidget *Reconnect_button; 

