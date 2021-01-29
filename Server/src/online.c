#include "../inc/header.h"
// Note of online users

void to_empty_online() {

    for (int i = 0; i < 200; i++) {

        user[i].id = -1;
        user[i].client_socket = -1;
    }
}


void to_be_online(int client_socket, struct info *res) {

    int i = get_free();
    user[i].id = res->id;
    user[i].client_socket = client_socket;   
}


int get_free() {

    for (int i = 0; i < 200; i++) {

        if (user[i].id == -1 || user[i].client_socket == -1) {

            return i;
        }
    }
}

void print_all() {
    int size = get_free();
    for (int i = 0; i < size; i++) {

        printf(" %d -", user[i].id);
        printf(" %d -\n", user[i].client_socket);
    }
}

void delete_online(int client_socket) {


    int size = get_free();
    for (int i = 0; i < size; i++) {

        if (client_socket == user[i].client_socket) {

            user[i].id =  user[size-1].id;
            user[i].client_socket = user[size-1].client_socket;
            user[size-1].id = -1;
            user[size-1].client_socket = -1;
            break;
        }
    }

}

int check_online(int friend_id) {

    int size = get_free();
    for (int i = 0; i < size; i++) {

        if (friend_id == user[i].id) {
            return user[i].client_socket;
        }
    }
    return -1;
}