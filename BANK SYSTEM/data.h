#ifndef DATA_H
#define DATA_H

#define MAX_USERS 50
#define MAX_ACCOUNTS 100

struct User {
    int id;
    char username[50];
    char password[50];
};

struct Account {
    int accNumber;
    char name[50];
    char lastname[50];
    char phone[20];
    char type[20];
    float balance;
};

extern struct User users[MAX_USERS];
extern struct Account accounts[MAX_ACCOUNTS];

extern int userCount;
extern int accCount;

#endif