#include <stdio.h>
#include <string.h>
#include "data.h"
#include "admin.h"

int adminLogin() {

    char user[50], pass[50];

    printf("\nAdmin Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if(strcmp(user,"admin")==0 && strcmp(pass,"1234")==0)
        return 1;

    printf("Login failed\n");
    return 0;
}

void addUser() {

    printf("\nUser ID: ");
    scanf("%d",&users[userCount].id);

    printf("Username: ");
    scanf("%s",users[userCount].username);

    printf("Password: ");
    scanf("%s",users[userCount].password);

    userCount++;

    printf("User added successfully\n");
}

void showUsers() {

    printf("\n--- User List ---\n");

    for(int i=0;i<userCount;i++) {

        printf("ID: %d\n",users[i].id);
        printf("Username: %s\n",users[i].username);
        printf("-----------------\n");
    }
}

void deleteUser() {

    int id;

    printf("Enter ID to delete: ");
    scanf("%d",&id);

    for(int i=0;i<userCount;i++) {

        if(users[i].id==id) {

            for(int j=i;j<userCount-1;j++)
                users[j]=users[j+1];

            userCount--;

            printf("User deleted\n");
            return;
        }
    }

    printf("User not found\n");
}

void editUser() {

    int id;

    printf("Enter ID to edit: ");
    scanf("%d",&id);

    for(int i=0;i<userCount;i++) {

        if(users[i].id==id) {

            printf("New Username: ");
            scanf("%s",users[i].username);

            printf("New Password: ");
            scanf("%s",users[i].password);

            printf("User updated\n");
            return;
        }
    }

    printf("User not found\n");
}