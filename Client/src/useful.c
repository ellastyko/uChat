#include "../inc/header.h"


bool validation() { 

    int ok = 0;
    char symbols[40] = { '_', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 
                         'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1', 
                         '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    char log[20]; char pass[25];
    strcpy(log, gtk_entry_get_text(login));          
    strcpy(pass, gtk_entry_get_text(password));                      
    for (int i = 0; i < strlen(log); i++) {
        for (int j = 0; j < strlen(symbols); j++) { 
            if (log[i] == symbols[j]) {
                ok++;
            } 
        }
        if (ok != 1) {
            gtk_widget_show (hint);
            gtk_label_set_text(hint, "Banned symbol used in login");
            return false;
        }
        ok = 0;
    }
    if (strcmp(gtk_label_get_text (hint), "Banned symbol used in login") == 0) {
        gtk_label_set_text(hint, "");
    }
    for (int i = 0; i < strlen(pass); i++) {
        for (int j = 0; j < strlen(symbols); j++) { 
            if (pass[i] == symbols[j]) {
                ok++;
            } 
        }
        if (ok != 1) {
            gtk_widget_show (hint);
            gtk_label_set_text(hint, "Banned symbol used in password");
            return false;
        }
        ok = 0;
    }
    if (strcmp(gtk_label_get_text (hint), "Banned symbol used in password") == 0) {
        gtk_label_set_text(hint, "");
    }
    if (strcmp(pass, gtk_entry_get_text(repeat)) == 0) {
                
        if (strcmp(gtk_label_get_text (hint), "Passwords are different") == 0) {
            gtk_label_set_text(hint, "");
        }
    }       
    return true; 
}  


void valid_of_log_in() {

    char log[20]; char pass[25];
        strcpy ( log, gtk_entry_get_text(login));
        strcpy ( pass, gtk_entry_get_text(password));
        

        if ((strcmp(log, "") != 0) || (strcmp(pass, "") != 0)) {
                if (strcmp(gtk_label_get_text (hint), "Input fields are empty") == 0) {

                gtk_widget_hide (hint);
                gtk_label_set_text(hint, "");
            }       
        }
    
        if (strcmp(log, "") != 0) {
            
            if (strcmp(gtk_label_get_text (hint), "Input login") == 0) {
                    gtk_widget_hide (hint);
                    gtk_label_set_text(hint, "");
            }
        }
           
        if (strcmp(pass, "") != 0) {
            
            if (strcmp(gtk_label_get_text (hint), "Input password") == 0) {
                    gtk_widget_hide (hint);
                    gtk_label_set_text(hint, "");
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


int time_converter(int time) {
    char *str;
    time %= 86400;
    int hours = time / 3600;
    int minutes = (time % 3600) / 60;
    return 0;
}


void push_chat(int chat_id, int friend_id, char*login) {

    int i = get_free();
    chat[i].chat_id = chat_id;
    chat[i].friend_id = friend_id;
    strcpy(chat[i].login, login); 
}


int get_free() {

    for (int i = 0; i < 100; i++) {

        if (chat[i].chat_id == -1 || chat[i].friend_id == -1 || strcmp(chat[i].login, "-1") == 0) {
            return i;
        }
    }
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

void code() {
    char text[500];
    char *res;
    printf("Enter text: "); scanf("%s", text);
    res = encoding(text);
    write(2, res, strlen(res));
    res = decoding(text);
    write(2, res, strlen(res));
}

char *decoding(char *str) {

    for (int i = 0; i < strlen(str); i++) {
        str[i] -= 2;
    }
    return str;
}

char *encoding(char *str) {

    for (int i = 0; i < strlen(str); i++) {
        str[i] += 2;
    }
    return str;
}