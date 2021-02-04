#include "../inc/header.h"

sqlite3 *db;

void *connection(void *cl_socket)
{
    int *temp = cl_socket;
    int client_socket = *temp;
    printf("User %d connected\n", client_socket);
    char request[BUFSIZ];
    while (1) {

        ssize_t res = recv(client_socket, request, sizeof(request), 0);
        if (res == 0) {
            delete_online(client_socket);
            write(2, "User disconnected\n", 19);          
            close(client_socket);
            break;
        }
        else if (res == -1) {
            write(2, "Resieve failed\n", 16);
        }
        strcpy(request, decoding(request));
        write(2, request, strlen(request));
        type_of_request(request, client_socket);
        memset(&request, 0, sizeof(request));
    }
    write(2, "Close thread\n", 14);
    pthread_exit(NULL);   
}

int Socket() {

    int server_socket, client_socket;
    server_socket = socket(AF_INET , SOCK_STREAM , 0);
    if (server_socket == -1) {
        perror("Could not create socket!\n");
        return 1;
    }
    printf("Socket created\n");
    struct sockaddr_in server = {0}, client = {0};
    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons( PORT );
    int flag = 1;  
    if (-1 == setsockopt(server_socket, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag))) {  
        perror("setsockopt fail");
    }
    if (bind(server_socket, (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Bind failed\n");
        return 1;
    }
    printf("Bind done\n");
    if (listen(server_socket, 5) != 0) {
        perror("Listen failed\n");
        return 1;
    }
    printf("Listening...\n");
    
    pthread_t pthread; 
    int lenth = sizeof(client);
    while(1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client, &lenth);
        if (client_socket < 0) {
            perror("Accept failed\n");
        }
        write(2, "Connection accepted\n", 21);   
        online++; 
        printf("Online: %i\n", online);        
        if ((pthread_create(&pthread, NULL, connection, &client_socket)) == 1) {
            perror("Failed thread\n");
        }
    }
    sqlite3_close(db);
    close(server_socket);
}

int main()
{
    
    if (db_init("Server/db/database.db") == -1) {
        perror("Саnnot init db\n");
        exit(EXIT_FAILURE);
    }
    to_empty_online();     
    Socket();
    return 0;
}