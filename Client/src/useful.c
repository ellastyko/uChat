#include "../inc/header.h"

// Validation when you wanna sign up
bool validation() { 

    int ok = 0;
    char symbols[40] = { '_', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 
                         'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1', 
                         '2', '3', '4', '5', '6', '7', '8', '9', '0' };


        char log[20]; char pass[25];
        strcpy(log, gtk_entry_get_text( GTK_ENTRY(login) ));          
        strcpy(pass, gtk_entry_get_text( GTK_ENTRY(password) ));  
                            
        for (size_t i = 0; i < strlen(log); i++) {
            for (size_t j = 0; j < strlen(symbols); j++) { 
                if (log[i] == symbols[j]) {
                    ok++;
                } 
            }
            if (ok != 1) {
                gtk_widget_show (hint);
                gtk_label_set_text(GTK_LABEL(hint), "Banned symbol used in login");

                return false;
            }
            ok = 0;
        }
        if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "Banned symbol used in login") == 0) {
            gtk_label_set_text(GTK_LABEL(hint), "");
        }
        for (size_t i = 0; i < strlen(pass); i++) {
            for (size_t j = 0; j < strlen(symbols); j++) { 
                if (pass[i] == symbols[j]) {
                    ok++;
                } 
            }
            if (ok != 1) {
                gtk_widget_show (hint);
                gtk_label_set_text(GTK_LABEL(hint), "Banned symbol used in password");
                return false;
            }
            ok = 0;
        }
        if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "Banned symbol used in password") == 0) {
            gtk_label_set_text(GTK_LABEL (hint), "");
        }
        if (strcmp(pass, gtk_entry_get_text( GTK_ENTRY(repeat) )) == 0) {
                    
            if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "Passwords are different") == 0) {
                gtk_label_set_text(GTK_LABEL(hint), "");
            }
        }
   
    return true; 
}  

// Function that delete unactual warnings when you wanna log in
void valid_of_log_in() {

    char log[20]; char pass[25];
    strcpy(log, gtk_entry_get_text( GTK_ENTRY(login) ));          
    strcpy(pass, gtk_entry_get_text( GTK_ENTRY(password) ));       

    if ((strcmp(log, "") != 0) || (strcmp(pass, "") != 0)) {
        if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "Input fields are empty") == 0) {

            gtk_widget_hide (hint);
            gtk_label_set_text(GTK_LABEL(hint), "");
        }       
    }
    
        if (strcmp(log, "") != 0) {
            
            if (strcmp(gtk_label_get_text (GTK_LABEL (hint)), "Input login") == 0) {
                    gtk_widget_hide (hint);
                    gtk_label_set_text(GTK_LABEL(hint), "");
            }
        }
           
        if (strcmp(pass, "") != 0) {
            
            if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "Input password") == 0) {
                    gtk_widget_hide (hint);
                    gtk_label_set_text(GTK_LABEL(hint), "");
            }                    
        }
}


void prepare() {

    // Вносим стандартные значения в главную структуру
    cl_info.id = -1; 
    strcpy(cl_info.login, "-1");
    strcpy(cl_info.password, "-1");
    strcpy(cl_info.key, "-1");
    // Вносим стандартные значения в структуру с чатами
    for (int i = 0; i < 100; i++) {

        chat[i].chat_id = -1;
        chat[i].friend_id = -1;
        strcpy(chat[i].login, "-1");
    }
}


char time_converter(int time) {
    
    char str[8];
    char m[3]; 

    // Find your local time
    time_t local_time = time;
    struct tm lt = {0};
    localtime_r(&local_time, &lt);
    
    time -= lt.tm_gmtoff; 

    // Converting to hours and minutes
    time %= 86400;
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;

    // Converting to char
    sprintf(str, "%d", hours);
    sprintf(m, "%d", minutes);
    strcat(str, ":"); 
    strcat(str, m); 

    return *str;
}


void push_chat(int chat_id, int friend_id, char*login) {

    int i = get_free();
    chat[i].chat_id = chat_id;
    chat[i].friend_id = friend_id;
    strcpy(chat[i].login, login); 
}


int get_free() {

    for (size_t i = 0; i < 100; i++) {

        if (chat[i].chat_id == -1 || chat[i].friend_id == -1 || strcmp(chat[i].login, "-1") == 0) {
            return i;
        }
    }
    return -1;
}

void print_all() {

    for (int i = 0; i < get_free(); i++) {
        
        printf("\n- %d -", chat[i].chat_id);
        printf(" %d -", chat[i].friend_id);
        printf(" %s -", chat[i].login);
    }
}

int search(char *name) {

    for (int i = 0; i < get_free(); i++) {

        if (strcmp(name, chat[i].login) == 0) {
            return i;
        }
    }
    return -1;
}

char *decoding(char *str) {

    for (size_t i = 0; i < strlen(str); i++) {
        str[i] -= 2;
    }
    return str;
}

char *encoding(char *str) {

    for (size_t i = 0; i < strlen(str); i++) {
        str[i] += 2;
    }
    return str;
}


void valid_login() {
    if (STATE == 1)  {
        availability_of_login();
        validation();
    } 
    else {
        valid_of_log_in();
    }
    
}

void valid_password() {
    if (STATE == 1) {
        availability_of_login();
        validation();
    } 
    else {
        valid_of_log_in();
    }
}
