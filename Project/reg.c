#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    char name[50];
    char email[50];
    char password[50];
    char phone[20];
    char roll[10];
} user;
user s, t;
FILE *fp;
int takepassword(char pass[50]);
int login();

int registration()
{
    int choice;
    printf("\t\t\t---Registration---\n");
    printf("\t\t1. Register as a student\n\t\t2. Register as a teacher\n");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        fp = fopen("stdinfo.txt", "a");
        system("cls");
        printf("\t\t\t---Student Registration---\n");
        printf("\t\tEnter your name: \t");
        fgets(s.name, 50, stdin);
        printf("\t\tEnter your email: \t");
        fgets(s.email, 50, stdin);
        printf("\t\tEnter your number: \t");
        fgets(s.phone, 20, stdin);
        printf("\t\tEnter your roll: \t");
        fgets(s.roll, 10, stdin);
        printf("\t\tEnter your password: \t");
        takepassword(s.password);
        char pass2[50];
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(s.password, pass2) != 0)
        {
            fclose(fp);
            printf("\t\tPasswords do not match\n");
            printf("\a"); // Cross-platform beep sound
            usleep(2000000);
            registration();
        }
        else
        {
            fwrite(&s, sizeof(user), 1, fp);
            fclose(fp);
        }
        login();
        break;
    case 2:
        fp = fopen("teacher.txt", "a");
        system("cls");
        printf("\t\t\t---Teacher Registration---\n");
        printf("\t\tEnter your name: \t");
        fgets(t.name, 50, stdin);
        printf("\t\tEnter your email: \t");
        fgets(t.email, 50, stdin);
        printf("\t\tEnter your number: \t");
        fgets(t.phone, 20, stdin);
        printf("\t\tEnter your password: \t");
        takepassword(t.password);
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(t.password, pass2) != 0)
        {
            fclose(fp);
            printf("\t\tPasswords do not match\n");
            printf("\a"); // Cross-platform beep sound
            usleep(2000000);
            registration();
        }
        else
        {
            fwrite(&t, sizeof(user), 1, fp);
            fclose(fp);
        }
        
        login();
        break;
    default:
        printf("\t\t\t---Invalid choice---\n");
        break;
    }
}

int login()
{
    system("cls");
    int choice;
    printf("\t\t\t---Login---\n");
    printf("\t\t1. Login as a student\n\t\t2. Login as a teacher\n");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    char email[50], password[50];
    switch (choice)
    {
    case 1:
        system("cls");
        printf("\t\t\t---Student login---\n\n");
        printf("\t\tEnter your E-mail: \t");
        fgets(email, 50, stdin);
        printf("\t\tEnter your password: \t");
        takepassword(password);
        fp = fopen("stdinfo.txt", "r");
        while (fread(&s, sizeof(user), 1, fp))
        {
            if (strcmp(email, s.email) == 0)
            {
                if (strcmp(password, s.password) == 0)
                {
                    fclose(fp);
                    printf("\t\tLogging in...\n\n");
                    usleep(2000000);
                    printf("\t\tLogin successful!\n");
                    printf("\t\tWelcome %s\n", s.name);
                    getchar();
                    return 1;
                }
                else
                {
                    fclose(fp);
                    printf("Wrong Password.\n");
                    usleep(2000000);
                    return 0;
                }
            }
        }
        printf("User not found.\n");
        usleep(2000000);
        fclose(fp);
        return 0;
        break;
    case 2:
        system("cls");
        printf("\t\t\t---Teacher Login---\n\n");
        printf("\t\tEnter your username: \t");
        fgets(email, 50, stdin);
        printf("\t\tEnter your password: \t");
        takepassword(password);
        fp = fopen("teacher.txt", "r");

        while (fread(&t, sizeof(user), 1, fp))
        {
            if (strcmp(email, t.email) == 0)
            {
                if (strcmp(password, t.password) == 0)
                {
                    fclose(fp);
                    printf("Login successful!\n");
                    usleep(2000000);
                    return 1;
                }
                else
                {
                    fclose(fp);
                    printf("Wrong Password.\n");
                    usleep(2000000);
                    return 0;
                }
            }
            else
            {
                fclose(fp);
                printf("User not found.\n");
                usleep(2000000);
                return 0;
            }
        }
        break;
    default:
        printf("\t\t\t---Invalid choice---\n");
        break;
    }
}

int takepassword(char pass[50])
{
    char ch;
    int i = 0;
    while (1)
    {
        ch = getchar();
        if (ch == 13)
        {
            pass[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pass[i] = ch;
            i++;
            printf("*");
        }
    }
}