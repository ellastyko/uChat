#include "../inc/header.h"

int online = 0;
// sqlite3 *users;
// sqlite3 *online_users;
// sqlite3 *chats;

void *connection(void *cl_socket) {
    int *temp = cl_socket;
    int client_socket = *temp;
    char request[1000];
    char response[1000];
    while(1) {
        if(read(client_socket , request , sizeof(request)) == -1 ) { 
            write(2, "Resieve failed\n", 16);
        }
        write(2, request, strlen(request));
        strcpy(response, request);
        *response = *type_of_request(request);
        write(client_socket, response, strlen(response));
        memset( &request, 0, sizeof(request));
        memset( &response, 0, sizeof(response));
    }
    // Make exit of cycle
    //printf("User lefted!");
    //pthread_exit(NULL);
}

int main()
{
    
    // sqlite3_open("../databases/users.db", &users);
    // sqlite3_open("../databases/online_users.db", &online_users);
    // sqlite3_open("../databases/chats.db", &chats);
    //Create socket
      
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
        printf("Listen failed\n");
        return 1;
    }
    printf("Listening...\n");
    
    pthread_t pthreads[1]; 
    int lenth = sizeof(client);
    // Cycle of acception users
    while(1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client, &lenth);
        if (client_socket < 0) {
            printf("Accept failed\n");
        }
        write(2, "Connection accepted\n", 21);   
        online++; 
        printf("Online: %i\n", online);        
        if ((pthread_create(&pthreads[0], NULL, connection, &client_socket)) == 1) {
            write(2, "Failed thread\n", 15);
        }
    }
    close(server_socket);
    return 0;  
}