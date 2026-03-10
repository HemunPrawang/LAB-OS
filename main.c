#include <stdio.h>
#include "admin.h"
#include "user.h"
#include "account.h"

int main() {

    int choice;

    while(1) {

        printf("\n===== BANK SYSTEM =====\n");
        printf("1.Admin Login\n");
        printf("2.User Login\n");
        printf("3.Exit\n");
        printf("Choose: ");
        scanf("%d",&choice);

        if(choice==1) {

            if(adminLogin()) {

                int c;

                do {

                    printf("\n--- Admin Menu ---\n");
                    printf("1.Add User\n");
                    printf("2.Delete User\n");
                    printf("3.Edit User\n");
                    printf("4.Show Users\n");
                    printf("5.Logout\n");
                    printf("Choose: ");
                    scanf("%d",&c);

                    switch(c) {

                        case 1:addUser();break;
                        case 2:deleteUser();break;
                        case 3:editUser();break;
                        case 4:showUsers();break;

                    }

                }while(c!=5);

            }

        }

        else if(choice==2) {

            if(userLogin()) {

                int c;

                do {

                    printf("\n--- User Menu ---\n");
                    printf("1.Add Account\n");
                    printf("2.Delete Account\n");
                    printf("3.Show Accounts\n");
                    printf("4.Search Account\n");
                    printf("5.Deposit\n");
                    printf("6.Withdraw\n");
                    printf("7.Logout\n");
                    printf("Choose: ");
                    scanf("%d",&c);

                    switch(c) {

                        case 1:addAccount();break;
                        case 2:deleteAccount();break;
                        case 3:showAccounts();break;
                        case 4:searchAccount();break;
                        case 5:deposit();break;
                        case 6:withdraw();break;

                    }

                }while(c!=7);

            }

        }

        else if(choice==3) {

            printf("Exit program\n");
            break;

        }

    }

    return 0;
}