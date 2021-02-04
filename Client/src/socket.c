#include "../inc/header.h"


int Socket() {
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons( PORT );
    inet_pton(AF_INET, ADDR, &adr.sin_addr);
    if (connect(client_socket, (struct sockaddr *) &adr, sizeof adr) == -1) {
        printf("No connection with server!\n");
        close(client_socket); 
        return 1;  
    }
    int error = 0;
    socklen_t len = sizeof (error);
    int retval = getsockopt(client_socket, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
    if (retval != 0) {
        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
        close(client_socket); 
        return 1;
    }
     if (error != 0) {
        fprintf(stderr, "socket error: %s\n", strerror(error));
        close(client_socket); 
        return 1;
    }
    pthread_t reads;
    pthread_create(&reads, NULL, reading, NULL);
    return 0;
}