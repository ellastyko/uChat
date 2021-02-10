#include "../inc/header.h"

void prepare() {

    // Вносим стандартные значения в главную структуру
    cl_info.id = -1; 
    strcpy(cl_info.login, "-1");
    strcpy(cl_info.password, "-1");
    strcpy(cl_info.key, "-1");
    FOCUS = -1;
    // Вносим стандартные значения в структуру с чатами
    for (int i = 0; i < 100; i++) {

        chat[i].chat_id = -1;
        chat[i].friend_id = -1;
        strcpy(chat[i].login, "-1");
    }
    
}


void push_chat(int chat_id, int friend_id, char*login) {

    int i = get_free();
    chat[i].chat_id = chat_id;
    chat[i].friend_id = friend_id;
    strcpy(chat[i].login, login); 
}


int get_free() {

    for (size_t i = 0; i < 100; i++) {

        if ((chat[i].chat_id == -1) && (chat[i].friend_id == -1) && (strcmp(chat[i].login, "-1") == 0)) {
            return i;
        }
    }
    return -1;
}




int search(char *name) {

    for (int i = 0; i < get_free(); i++) {

        if (strcmp(name, chat[i].login) == 0) {
            return i;
        }
    }
    return -1;
}

// useless
int search_chat_id(char *login) {

    for (int i = 0; i < get_free(); i++) {

        if (strcmp(login, chat[i].login) == 0) {
            return chat[i].chat_id;
        }
    }
    return -1;
}

int friend_id () {
    for (int i = 0; i < get_free(); i++) {

        if (FOCUS == chat[i].chat_id) {
            return chat[i].friend_id;
        }
    }
    return -1;
}

char *search_login(int chat_id) {
    char *login = "";

    for (int i = 0; i < get_free(); i++) {

        if (chat_id == chat[i].chat_id) {
            return chat[i].login;
        }
    }
    return login;
}