#include "../inc/header.h"

int validation(char *login, char *password) { 
    char banned_symbols[35] = {'!', '@', '#', '$', '^', '&', '*', '(', ')', '-', '+',
                             '=', '[', '{', '}', ']', '`', '`', '|', '/','1', '2', '3',
                             '4', '5', '6', '7', '8', '9', '0'};
    for (int i = 0; i < strlen(login); i++) {
        for (int j = 0; j < strlen(banned_symbols); j++) { 
            if (login[i] == banned_symbols[j]) {
                write(2, "Banned symbol used\n", 9);
                return 1;
            } 
        }
    }
    return 0;
}  


