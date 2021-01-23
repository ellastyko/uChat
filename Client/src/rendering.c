#include "../inc/header.h"

void *reading() {
    char *buf; ssize_t result;
    while(1) {
        if ( (result = recv(3, buf, 250, 0)) == -1) { 
            write(2, "Fail recieve\n", 14);
        }
        else {
            write(STDOUT_FILENO, buf, strlen(buf));
            //struct info *res = parse(buf);
            //printf("%s, %s, %s\n", res->status, res->response, res->time);      
        }
    }
}