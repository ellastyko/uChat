#include "../inc/header.h"

void *reading() {

    char buf[BUFSIZ]; ssize_t result;
    while(1) {
        if ( (result = recv(client_socket, buf, sizeof(buf), 0)) == -1) { 
            perror("Fail recieve\n");
            close(client_socket);
            no_connection();
            break;
            
        }
        if ( result == 0 ) {
            perror("\nDisconnect!\n"); // Перестаем читать сервер
            close(client_socket);
            no_connection();
            break;
        }
        else {

            strcpy(buf, decoding(buf));
            write(2, buf, strlen(buf));
            struct info *res = parse(buf);
            
            type_of_response(res);    
        }
        memset(&buf, 0, sizeof(buf));
    }
    pthread_exit(NULL);    
}


void type_of_response(struct info *res) {
    
    if (res->status == 0) {

        write(2, res->message, strlen(res->message));
        if (strcmp(res->action, "availability_of_login") == 0) {
            gtk_widget_show (hint);
            gtk_label_set_text(GTK_LABEL(hint), res->message);
        }
        else if ( strcmp(res->action, "auto_sign") == 0 ) {
            STATE = 0; 
        }
        else if (strcmp(res->action, "sign_in") == 0) {

            if (!update_localdata(&cl_info, LD_PATH)) {
                printf("Cant save localdata\n");
            }
            else {
                printf("Localdata is saved\n");
            }

            gtk_widget_show (hint);
            gtk_label_set_text(GTK_LABEL(hint), res->message);

        }
        else if (strcmp(res->action, "sign_up") == 0) {
            gtk_widget_show (hint);
            gtk_label_set_text(GTK_LABEL(hint), res->message);
        }
        else if (strcmp(res->action, "is_user_exists") == 0) {
            write(2, "User not exists\n", 17);
        }
    }
    else if (res->status == 1){
        if ( strcmp(res->action, "auto_sign") == 0 ) {

            reading_thread();
            cl_info.id = res->id;
            strcpy(cl_info.login, res->login);
            strcpy(cl_info.password, res->password);
            strcpy(cl_info.key, res->key);
            friend_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_container_add(GTK_CONTAINER(fbox), friend_box);
            get_chats_info();
            STATE = 2;
        }
        else if (strcmp(res->action, "sign_up") == 0) {           
            to_log_in();
        }
        else if (strcmp(res->action, "sign_in") == 0) {

            cl_info.id = res->id;
            strcpy(cl_info.login, res->login);
            strcpy(cl_info.password, res->password);
            strcpy(cl_info.key, res->key);

            friend_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_container_add(GTK_CONTAINER(fbox), friend_box);
            get_chats_info();

            if (!update_localdata(&cl_info, LD_PATH)) {
                printf("Cant save localdata\n");
            }

            gtk_label_set_text(GTK_LABEL(hint), "");
            open_main();      
        }
        else if (strcmp(res->action, "add_chat") == 0) {

            push_chat(res->chat_id, res->friend_id, res->login);
            create_chat(res->chat_id, res->login);  
        }
        else if (strcmp(res->action, "get_chats_info") == 0) {
            // Запись полученных данных в структуру
            
            push_chat(res->chat_id, res->friend_id, res->login);
            create_chat(res->chat_id, res->login);            
        }
        else if (strcmp(res->action, "get_message") == 0) {
            char *str = malloc(sizeof(char));
            char *m = malloc(sizeof(char));

            // Find your local time
            time_t local_time = res->time;
            struct tm lt = {0};
            localtime_r(&local_time, &lt);
            
            res->time += lt.tm_gmtoff; 

            // Converting to hours and minutes
            res->time %= 86400;
            int hours = res->time / 3600;
            int minutes = (res->time % 3600) / 60;

            if (minutes < 10) {
                sprintf(str, "%d", hours);
                sprintf(m, "%d", minutes);
                strcat(str, ":"); 
                strcat(str, "0"); 
                strcat(str, m); 
            }
            else {
                sprintf(str, "%d", hours);
                sprintf(m, "%d", minutes);
                strcat(str, ":"); 
                strcat(str, m);  
            }   

            create_message(res->id, res->message, str);
            free(m);
            free(str);
        }
        else if (strcmp(res->action, "send_message") == 0) {
            

        }
        else if (strcmp(res->action, "delete_message") == 0) {
            
        }
        else if (strcmp(res->action, "availability_of_login") == 0) {
            
             if (strcmp(gtk_label_get_text (GTK_LABEL(hint)), "This login isn`t available") == 0) {
                gtk_label_set_text(GTK_LABEL(hint), "");
                gtk_widget_hide (hint);         
            }
        }
        else if (strcmp(res->action, "load_messages") == 0) {
            
            char *str = malloc(sizeof(char));
            char *m = malloc(sizeof(char));

            // Find your local time
            time_t local_time = res->time;
            struct tm lt = {0};
            localtime_r(&local_time, &lt);
            
            res->time += lt.tm_gmtoff; 

            // Converting to hours and minutes
            res->time %= 86400;
            int hours = res->time / 3600;
            int minutes = (res->time % 3600) / 60;

            if (minutes < 10) {
                sprintf(str, "%d", hours);
                sprintf(m, "%d", minutes);
                strcat(str, ":"); 
                strcat(str, "0"); 
                strcat(str, m); 
            }
            else {
                sprintf(str, "%d", hours);
                sprintf(m, "%d", minutes);
                strcat(str, ":"); 
                strcat(str, m);  
            }     

            create_message(res->id, res->message, str);
            free(m);
            free(str);
        }
        else if (strcmp(res->action, "is_user_exists") == 0) {
            write(2, "User exists!\n", 16);
            
        }
        else if (strcmp(res->action, "open_chat") == 0) {
            create_status(res->time);
            
        }
    }
}


void create_status(int ttime) {
    if (ttime == 0) {
        gtk_label_set_text(GTK_LABEL(friend_status), "online");
    }
    else {
        int current_time = time(NULL);

        time_t local_time = ttime;
        struct tm lt = {0};
        localtime_r(&local_time, &lt);
                
        ttime += lt.tm_gmtoff; 
        current_time += lt.tm_gmtoff;

        ttime %= 86400;
        current_time %= 86400;
        int diff = current_time - ttime;
        if (diff < 86400) {

            char *str = malloc(sizeof(char));
            char *min = malloc(sizeof(char));

            
            if (diff < 60)  {  
                diff /= 60;
                sprintf(str, "last seen just now", diff);
                gtk_label_set_text(GTK_LABEL(friend_status), str);
            }
            if (diff < 3600)  {  
                diff /= 60;
                sprintf(str, "last seen %d minutes ago", diff);
                gtk_label_set_text(GTK_LABEL(friend_status), str);
            }
            else if (diff < 21600) {
                diff /= 3600;
                sprintf(str, "last seen %d hours ago", diff);
                gtk_label_set_text(GTK_LABEL(friend_status), str);
            }
            else { 
                int hours = diff / 3600;
                int minutes = (diff % 3600) / 60;
                if (minutes < 10) {
                    sprintf(str, "last seen in %d", hours);
                    sprintf(min, "%d", minutes);
                    strcat(str, ":"); 
                    strcat(str, "0"); 
                    strcat(str, min); 
                    gtk_label_set_text(GTK_LABEL(friend_status), str);
                }
                else {
                    sprintf(str, "last seen in %d", hours);
                    sprintf(min, "%d", minutes);
                    strcat(str, ":"); 
                    strcat(str, min); 
                    gtk_label_set_text(GTK_LABEL(friend_status), str); 
                }   
            }
            free(min);
            free(str);
        }
        else if (diff < 259200) {
            gtk_label_set_text(GTK_LABEL(friend_status), "last seen a few days ago");
        }
        else if (diff > 259200) {
            gtk_label_set_text(GTK_LABEL(friend_status), "last seen long ago");
        }
        
    }
    
}