#include "../inc/header.h"

char _user_[20];
bool _access_ = false; // Доступ к данным пользователя

int main(int argc, char *argv[])
{
    strcpy(_user_,"HELLO\n");
    _access_ = true;
    int client_socket = Socket(); // Socket initialization
    //checking_local_storage(); //TODO Проверка локального хранилища на сохранненый пароль с именем
    int action;
    while(1) {
        printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Delete account\n");
        scanf("%d",&action);
        switch(action) {
            case 1: sign_up(client_socket); break;
            case 2: sign_in(client_socket); break;
            default: close(client_socket); break;
        }
        // access == true После входа в аккаунт
        // Если access == true Открывается доступ к всем функциям аккаунта идущие после входа
        /*if (access == true) {
                printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Delete account\n");
                scanf("%d",&action);
                switch(action) {
                    case 1: send_message(client_socket); break;
                    case 2: delete_user(client_socket); break;
                    case 3: change_password(client_socket); break;
                    default: close(client_socket); break;
            }   
        }*/
    }
    close(client_socket);
    return 0;
}
