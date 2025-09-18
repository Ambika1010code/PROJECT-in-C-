#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char user_name[50];
    char password[20];
};

struct Diary {
    char user_name[50];
    char Date[60];
    char Title[100];
    char content[500];
};

char userName[50];

int register_user() {
    struct user u;
    FILE *fp;

    printf("Enter User name :- \n");
    scanf("%s", u.user_name);
    printf("Enter password :- \n");
    scanf("%s", u.password);

    fp = fopen("user.txt", "a");
    if (fp == NULL) {
        printf("Error opening file !\n");
        return 0;
    }
    fprintf(fp, "%s %s\n", u.user_name, u.password);
    fclose(fp);

    printf("\n \t Register successfully :) \n");
    return 1;
}

int login_user() {
    struct user u;
    FILE *fp;
    char user_name[50], password[50];
    int success = 0;

    printf("Enter user_name :- \n");
    scanf("%s", user_name);
    printf("Enter password :- \n");
    scanf("%s", password);

    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        printf("No user found! Please register first. \n");
        return 0;
    }
    while (fscanf(fp, "%s %s", u.user_name, u.password) != EOF) {
        if (strcmp(u.user_name, user_name) == 0 && strcmp(u.password, password) == 0) {
            success = 1;
            strcpy(userName, user_name); // save logged in username
            break;
        }
    }
    fclose(fp);
    if (success) {
        printf("\n \t Login successful! Welcome %s \n", user_name);
        return 1;
    } else {
        printf("Invalid user_name or password.\n");
        return 0;
    }
}

void add_entry() {
    struct Diary d;
    FILE *fp;

    fp = fopen("Diary.txt", "a");
    if (fp == NULL) {
        printf("Error opening Diary file! \n");
        return;
    }
    strcpy(d.user_name, userName);
    printf("Enter Date (DD/MM/YYYY) : ");
    scanf(" %[^\n]", d.Date);

    printf("Enter TITLE : ");
    scanf(" %[^\n]", d.Title);

    printf("Enter content : ");
    scanf(" %[^\n]", d.content);

    fprintf(fp, "%s,%s,%s,%s\n", d.user_name, d.Date, d.Title, d.content);
    fclose(fp);

    printf("Entry Saved :) \n");
}

void view_entry() {
    struct Diary d;
    FILE *fp;

    fp = fopen("Diary.txt", "r");
    if (fp == NULL) {
        printf("No Diary Entry found! \n");
        return;
    }

    printf("Enter Username to view diary: ");
    scanf("%s", userName);

    printf("\n ||------ WELCOME TO MINDVAULT DIARY ------||\n");

    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n",
                  d.user_name, d.Date, d.Title, d.content) != EOF) {
        if (strcmp(d.user_name, userName) == 0) {
            printf("\n\n DATE:- [%s] \n", d.Date);
            printf("TITLE:- %s\n", d.Title);
            printf("CONTENT:- %s\n", d.content);
        }
    }
    fclose(fp);
}

void search_entry() {
    struct Diary d;
    FILE *fp;
    char search_date[50];
    int found = 0;

    fp = fopen("Diary.txt", "r");
    if (fp == NULL) {
        printf("No diary entries found!\n");
        return;
    }
    printf("Enter Date to search :-  \n");
    scanf("%s", search_date);
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n",
                  d.user_name, d.Date, d.Title, d.content) != EOF) {
        if (strcmp(d.Date, search_date) == 0 && strcmp(d.user_name, userName) == 0) {
            printf("\n\n[%s] %s - %s\n\n", d.Date, d.Title, d.content);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No Entry found! \n");
    }
    fclose(fp);
}

void edit_entry() {
    struct Diary d;
    FILE *fp, *temp;
    char search_date[50];
    int found = 0;

    fp = fopen("Diary.txt", "r");
    temp = fopen("Temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Date of entry to EDIT (DD/MM/YYYY): ");
    scanf("%s", search_date);

    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n",
                  d.user_name, d.Date, d.Title, d.content) != EOF) {
        if (strcmp(d.user_name, userName) == 0 && strcmp(d.Date, search_date) == 0) {
            found = 1;
            printf("Editing entry on [%s]\n", d.Date);
            printf("Enter new TITLE: ");
            scanf(" %[^\n]", d.Title);
            printf("Enter new CONTENT: ");
            scanf(" %[^\n]", d.content);
        }
        fprintf(temp, "%s,%s,%s,%s\n", d.user_name, d.Date, d.Title, d.content);
    }

    fclose(fp);
    fclose(temp);

    remove("Diary.txt");
    rename("Temp.txt", "Diary.txt");

    if (found)
        printf("Entry updated successfully!\n");
    else
        printf("No entry found on that date.\n");
}

void delete_entry() {
    struct Diary d;
    FILE *fp, *temp;
    char search_date[50];
    int found = 0;

    fp = fopen("Diary.txt", "r");
    temp = fopen("Temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Date of entry to DELETE (DD/MM/YYYY): ");
    scanf("%s", search_date);

    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n",
                  d.user_name, d.Date, d.Title, d.content) != EOF) {
        if (strcmp(d.user_name, userName) == 0 && strcmp(d.Date, search_date) == 0) {
            found = 1;
            printf("Entry on [%s] deleted.\n", d.Date);
            continue;
        }
        fprintf(temp, "%s,%s,%s,%s\n", d.user_name, d.Date, d.Title, d.content);
    }

    fclose(fp);
    fclose(temp);

    remove("Diary.txt");
    rename("Temp.txt", "Diary.txt");

    if (!found)
        printf("No entry found on that date.\n");
}

int main() {
    int choice, loggedIN = 0;
    while (!loggedIN) {
        printf("\n||------ Welcome to MINDVAULT ------||\n");
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            register_user();
            break;
        case 2:
            loggedIN = login_user();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! Choose valid option \n");
            return 1;
        }
    }
    while (1) {
        printf("\n||------ MINDVAULT DIARY ------||\n");
        printf(" 1. Add Entry\n 2. View Entries\n 3. Search Entry\n 4. Edit Entry\n 5. Delete Entry\n 6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
            edit_entry();
            break;
        case 5:
            delete_entry();
            break;
        case 6:
            printf("Goodbye! See you again :)\n Author By :- AMBIKA\tALISHA\tANKITA");
            exit(0);
        default:
            printf("Invalid choice! Try again\n");
        }
    }
    return 0;
}
