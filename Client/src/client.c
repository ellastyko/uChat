#include "../inc/header.h"

int main(int argc, char *argv[])
{
    strcpy(_id_, "default"); // id которое мы получаем после регистрации
    strcpy(_login_, "default");
    strcpy(_password_, "default");
    strcpy(_key_, "default");
    Socket(); // Socket initialization

    //checking_local_storage(); //TODO Проверка локального хранилища на сохранненый пароль с именем
    pthread_t reads[1];
    pthread_create(&reads[0], NULL, reading, NULL);
    sleep(1);
    int action;
    while(1) {
        printf("\nWhat do you want:\n 1 - Sign up\n 2 - Sign in\n 3 - Send message\n 4 - Change Password\n 5 - Delete account\n");
        scanf("%d",&action);
        switch(action) {
            case 1: sign_up(); break;
            case 2: sign_in(); break;
            case 3: send_message(); break;
            case 4: change_password(); break;
            default: break;

        }
    }
    return 0;
}
