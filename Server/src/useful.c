#include "../inc/header.h"

// Сделать ответы сервера в формате JSON
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

int key() {
    srand(time(NULL));
    return rand() % 100000;
}
