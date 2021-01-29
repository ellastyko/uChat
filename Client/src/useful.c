#include "../inc/header.h"


bool validation(char *login, char *password) { 

    int ok = 0;
    char symbols[40] = { '_', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 
                         'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '1', 
                         '2', '3', '4', '5', '6', '7', '8', '9', '0'};
                         
    for (int i = 0; i < strlen(login); i++) {
        for (int j = 0; j < strlen(symbols); j++) { 
            if (login[i] == symbols[j]) {
                ok++;
            } 
        }
        if (ok != 1) {
            write(2, "Banned symbol used in password\n", 32);
            return false;
        }
        ok = 0;
    }
    for (int i = 0; i < strlen(password); i++) {
        for (int j = 0; j < strlen(symbols); j++) { 
            if (password[i] == symbols[j]) {
                ok++;
            } 
        }
        if (ok != 1) {
            write(2, "Banned symbol used in password\n", 32);
            return false;
        }
        ok = 0;
    }

    return true;
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