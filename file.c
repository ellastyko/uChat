#include "stdio.h" 
#include "time.h"
#include <stdint.h>
#include <string.h>

struct chats {
    int chat_id;
    int friend_id;
    char login[20];
};



int main() {
    struct chats mass[20];
    for (int i = 0; i < 20; i++) {
        mass[i].chat_id = 0;
        mass[i].friend_id = 1;
        strcpy(mass[i].login, "LOGIN");
    }
    for (int i = 0; i < 20; i++) {
        printf("%d -", mass[i].chat_id);
        printf("%d -", mass[i].friend_id);
        printf("%s \n", mass[i].login);
    }
    return 0;
}

