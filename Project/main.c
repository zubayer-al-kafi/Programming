#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "reg.h"


int main()
{
    system("color 0B");
    int opt;
    printf("\t\t\t---Welcome to the student management system---\n");
    printf("\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n");
    printf("\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        system("cls");
        registration(); //calling the registration function
        break;
    case 2:
        system("cls");
        login(); //calling the login function
        break;
    case 3:
        system("cls");
        printf("\t\t\t---Exiting---\n");
        usleep(2000000);
        exit(0); //exiting the program
        break;
    default:
        printf("\t\t\t---Invalid choice---\n");
        break;
    }
}

