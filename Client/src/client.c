#include "../inc/header.h"

int main(int argc, char *argv[])
{
    strcpy(_id_, "default"); // id которое мы получаем после регистрации
    strcpy(_login_, "default");
    strcpy(_password_, "default");
    strcpy(_key_, "default");
    Socket(); // Socket initialization

    //checking_local_storage(); //TODO Проверка локального хранилища на сохранненый пароль с именем
    int action;
    while(1) {
        printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Send message\n 4 - Change Password\n 5 - Delete account\n");
        scanf("%d",&action);
        switch(action) {
            case 1: sign_up(); break;
            case 2: sign_in(); break;
            case 3: send_message(); break;
            case 4: change_password(); break;
            default: close(3); break;
                
                //close(client_socket); break;
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
    return 0;
}
