#include <stdio.h>
#include <string.h>
#include "data.h"
#include "user.h"

int userLogin() {

    char user[50],pass[50];

    printf("\nUsername: ");
    scanf("%s",user);

    printf("Password: ");
    scanf("%s",pass);

    for(int i=0;i<userCount;i++) {

        if(strcmp(user,users[i].username)==0 &&
           strcmp(pass,users[i].password)==0) {

           return 1;
        }
    }

    printf("Login failed\n");
    return 0;
}