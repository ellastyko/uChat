#include "../inc/header.h"

int online = 0;
// sqlite3 *users;
// sqlite3 *online_users;
// sqlite3 *chats;
void *connection(void *cl_socket) {
    int *temp = cl_socket;
    int client_socket = *temp;
    char message[2000];
    while(1) {
        read(client_socket , message , sizeof(message));
        printf("%s", message);
        write(client_socket, message, strlen(message));
        memset( &message, 0, sizeof(message));
    }
    printf("User lefted!");
    pthread_exit(NULL);
}

int main()
{
    
    // sqlite3_open("../databases/users.db", &users);
    // sqlite3_open("../databases/online_users.db", &online_users);
    // sqlite3_open("../databases/chats.db", &chats);
//START:
    //Create socket
    int server_socket, client_socket;

    server_socket = socket(AF_INET , SOCK_STREAM , 0);
    if (server_socket == -1) {
        printf("Could not create socket!\n");
        return 1;
    }
    printf("Socket created\n");


    struct sockaddr_in server = {0}, client = {0};
    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = INADDR_ANY; //inet_addr("0.0.0.0")
    server.sin_port = htons( PORT );
    if (bind(server_socket, (struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("bind failed\n");
        return 1;
    }
    printf("Bind done\n");


    if (listen(server_socket, 5) != 0) {
        printf("Listen failed\n");
        return 1;
    }
    printf("Listening...\n");
    //memset(a ,0 ,sizeof(a)); Clean a


    pthread_t pthreads[1]; // 5 threads
    int lenth = sizeof(client);
    // Cycle of acception users
    while(1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client, &lenth);
        if (client_socket < 0) {
            printf("Accept failed\n");
        }
        printf("Connection accepted: \n");   
        online++; 
        printf("Online: %i\n", online);        
        if ((pthread_create(&pthreads[0], NULL, connection, &client_socket)) == 1) {
            printf("Failed thread\n");
        }
    }
    close(server_socket);
    //goto START;
    return 0;  
}