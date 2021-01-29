#include "../inc/header.h"

// Сделать ответы сервера в формате JSON

int key() {
    srand(time(NULL));
    return rand() % 100000;
}
