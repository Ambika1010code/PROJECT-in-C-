#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct user
{
    char email[50];
    char password[20];
};

struct Diary
{
    char Date[60];
    char Title[100];
    char content[500];
};

int register_user()
{
    struct user u;
    FILE *fp;

    printf("Enter Email :- \n");
    scanf("%s", u.email);
    printf("Enter password :- \n");
    scanf("%s", u.password);

    fp = fopen("user.txt", "a");
    if (fp == NULL)
    {
        printf("Eroor opening file !\n");
        return 0;
    }
    fprintf(fp, "%s %s\n", u.email, u.password);
    fclose(fp);
    printf("Register sucessfully :) \n");
    return 1;
}

int login_user()
{
    struct user u;
    FILE *fp;
    char email[50], password[50];
    int success = 0;

    printf("Enter email :- \n");
    scanf("%s", email);
    printf("Enter password :- \n");
    scanf("%s", password);

    fp = fopen("user.txt", "r");
    if (fp == NULL)
    {
        printf("NO,user found! please register first. \n");
        return 0;
    }
    while (fscanf(fp, "%s %s", u.email, u.password) != EOF)
    {
        if (strcmp(u.email, email) == 0 && strcmp(u.password, password) == 0)
        {
            success = 1;
            break;
        }
    }
    fclose(fp);
    if (success)
    {
        printf("login is successfull! welcome %s \n", email);
        return 1;
    }
    else
    {
        printf("invalid email or password.\n");
        return 0;
    }
}

void add_entry()
{
    struct Diary d;
    FILE *fp;

    fp = fopen("Diary.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening Diary file! \n");
        return;
    }

    printf("Enter Date (DD/MM/YYYY) : ");
    scanf(" %[^\n]", d.Date);

    printf("Enter TITLE : ");
    scanf(" %[^\n]", d.Title);

    printf("Enter content : ");
    scanf(" %[^\n]", d.content);

    fprintf(fp, "%s, %s, %s \n", d.Date, d.Title, d.content);

    fclose(fp);

    printf("Entry Saved :) \n");
}

void view_entry()
{
    struct Diary d;
    FILE *fp;

    fp = fopen("Diary.txt", "r");
    if (fp == NULL)
    {
        printf("NO Diary Entry found! \n");
        return;
    }

    printf("\n ||------ WELCOME TO MINDVAULT DIARY ------||\n");

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", d.Date, d.Title, d.content) != EOF)
    {
        printf("\n\n");
        printf("[%s] \n", d.Date);
        printf("%s - \n", d.Title);
        printf("%s\n", d.content);
        printf("\n\n");
    }
    fclose(fp);
}
void search_entry()
{
    struct Diary d;
    FILE *fp;
    char search_date[50];
    int found = 0;

    fp = fopen("Diary.txt", "r");
    if (fp == NULL)
    {
        printf("No diary entries found!\n");
        return;
    }
    printf("Enter Date to search :-  \n");
    scanf("%s", search_date);
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", d.Date, d.Title, d.content) != EOF)
    {
        if (strcmp(d.Date, search_date) == 0)
        {
            printf("\n\n");
            printf("[%s] ", d.Date);
            printf("%s - ", d.Title);
            printf("%s", d.content);
            printf("\n\n");

            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("No Entry found! \n");
    }
    fclose(fp);
}

int main()
{
    int choice, loggedIN = 0;
    while (!loggedIN)
    {
        printf("\n||------ Welcome to MINDVAULT ------||\n");
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            loggedIN = login_user();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! choice view option \n");
        }
    }
    while (1)
    {
        printf("\n||------ MINDVAULT DIARY ------||\n");
        printf("1. Add Entry\n2. View Entries\n3. Search by Date\n4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_entry();
            break;
        case 2:
            view_entry();
            break;
        case 3:
            search_entry();
            break;
        case 4:
            printf("Goodbye! see you again :)\n Auther By :- AMBIKA\tALISHA\tANKITA");
            exit(0);
        default:
            printf("Invalid choice! Try again\n");
        }
    }
    return 0;
}