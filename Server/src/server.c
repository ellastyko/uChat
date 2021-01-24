#include "../inc/header.h"

sqlite3 *db;
int online = 0;

void *connection(void *cl_socket)
{
    int *temp = cl_socket;
    int client_socket = *temp;
    printf("User %d connected\n", client_socket);
    char request[BUFSIZ];
    while (1) {

        ssize_t res = recv(client_socket, request, sizeof(request), 0);
        if (res == 0) {
            write(2, "User disconnected\n", 19);
            close(client_socket);
            break;
        }
        else if (res == -1) {
            write(2, "Resieve failed\n", 16);
        }
        write(2, request, strlen(request));
        type_of_request(request, client_socket);
        memset(&request, 0, sizeof(request));
    }
    write(2, "Close thread\n", 14);
    online--;
    pthread_exit(NULL);   
}


int main()
{
    
    if (db_init("Server/db/database.db") == -1) {
        perror("Саnnot init db\n");
        exit(EXIT_FAILURE);
    }
    create_db("CREATE TABLE users("\
           "ID             INTEGER PRIMARY KEY AUTOINCREMENT,"\
           "LOGIN          TEXT                NOT NULL,"\
           "PASSWORD       TEXT                NOT NULL,"\
           "KEY            INTEGER             NOT NULL);", db);

    create_db("CREATE TABLE chats("\
           "CHAT_ID             INTEGER PRIMARY KEY AUTOINCREMENT,"\
           "USER1          INTEGER                NOT NULL,"\
           "USER2          INTEGER                NOT NULL);", db);

    create_db("CREATE TABLE messages("\
           "MESSAGE_ID             INTEGER PRIMARY KEY AUTOINCREMENT,"\
           "SENDER          INTEGER                NOT NULL,"\
           "MESSAGE         TEXT                   NOT NULL,"\
           "TIME            INTEGER                NOT NULL, "\
           "CHAT_ID         INTEGER                NOT NULL);", db);
           
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

    return 0;
}