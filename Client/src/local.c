#include "../inc/header.h"


// 0 - reading
// 1 - write 
// 2 - delete

//int local_storage(int act) {

    // char *line; 
    // if (act == 0) { // READ BEFORE SIGN IN
    //     // cache
    //     FILE *file = fopen("Client/storage/data.txt", "r");
    //     fgets(line, 255, file);
    //     printf("%s", line);
    //     fclose(file);
    //     if (strcmp(line, "") == 0) {
    //         write(2, "There is nothing!\n", 19);
    //         return 0;
    //     }
    //     else {


    //         struct info *req;
    //         strcpy(req->action, "signin");
    //         strcpy(req.login, );
    //         strcpy(req.password, );  
    //         strcpy(req.message, "");
    //         strcpy(req.time, ""); 
    //         strcpy(req.receiver, "");
    //         char *buf = stringify(&req);
    //         send_to_server(buf);
    //     }

    // }
    // // Rewrite after sign in
    // else if (act == 1) { 

    //     FILE *file = fopen("data.txt", "r");
    //     fgets(line, 255, file);
    //     printf("%s", line);
    //     fclose(file);
    //     if (strcmp(line, "") == 0) {
    //         write(2, "There is nothing!\n", 19);
    //         return 0;
    //     }
    //     else {

    //     }
    // }
    // // Logout or unsuccessful log in
    // else if (act == 2) { 
        
    //     return 0;
    // }
    //return 0; // error
//}
