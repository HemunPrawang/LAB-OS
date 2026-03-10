#include <stdio.h>
#include "data.h"
#include "account.h"

void addAccount() {

    printf("\nAccount Number: ");
    scanf("%d",&accounts[accCount].accNumber);

    printf("First Name: ");
    scanf("%s",accounts[accCount].name);

    printf("Last Name: ");
    scanf("%s",accounts[accCount].lastname);

    printf("Phone Number: ");
    scanf("%s",accounts[accCount].phone);

    printf("Account Type (saving/fixed): ");
    scanf("%s",accounts[accCount].type);

    printf("Initial Balance: ");
    scanf("%f",&accounts[accCount].balance);

    accCount++;

    printf("Account created\n");
}

void showAccounts() {

    printf("\n--- Account List ---\n");

    for(int i=0;i<accCount;i++) {

        printf("Acc#: %d\n",accounts[i].accNumber);
        printf("Name: %s %s\n",accounts[i].name,accounts[i].lastname);
        printf("Phone: %s\n",accounts[i].phone);
        printf("Type: %s\n",accounts[i].type);
        printf("Balance: %.2f\n",accounts[i].balance);
        printf("----------------------\n");
    }
}

void searchAccount() {

    int acc;

    printf("Enter account number: ");
    scanf("%d",&acc);

    for(int i=0;i<accCount;i++) {

        if(accounts[i].accNumber==acc) {

            printf("Name: %s %s\n",accounts[i].name,accounts[i].lastname);
            printf("Balance: %.2f\n",accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void deleteAccount() {

    int acc;

    printf("Enter account number to delete: ");
    scanf("%d",&acc);

    for(int i=0;i<accCount;i++) {

        if(accounts[i].accNumber==acc) {

            for(int j=i;j<accCount-1;j++)
                accounts[j]=accounts[j+1];

            accCount--;

            printf("Account deleted\n");
            return;
        }
    }

    printf("Account not found\n");
}

void deposit() {

    int acc;
    float money;

    printf("Account number: ");
    scanf("%d",&acc);

    printf("Deposit amount: ");
    scanf("%f",&money);

    for(int i=0;i<accCount;i++) {

        if(accounts[i].accNumber==acc) {

            accounts[i].balance += money;

            printf("New Balance: %.2f\n",accounts[i].balance);
            return;
        }
    }

    printf("Account not found\n");
}

void withdraw() {

    int acc;
    float money;

    printf("Account number: ");
    scanf("%d",&acc);

    printf("Withdraw amount: ");
    scanf("%f",&money);

    for(int i=0;i<accCount;i++) {

        if(accounts[i].accNumber==acc) {

            if(accounts[i].balance >= money) {

                accounts[i].balance -= money;

                printf("Remaining Balance: %.2f\n",accounts[i].balance);

            } else {

                printf("Insufficient balance\n");
            }

            return;
        }
    }

    printf("Account not found\n");
}