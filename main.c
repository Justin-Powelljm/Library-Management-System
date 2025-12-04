#include "user-management.h"
#include "library-management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () 
{
    int choice;
    char username[50];
    password[50];
    int studentIndex;

    loadBooks();
    loadLoans();
    loadStudents();
    while(1)
    {
        printf("\n-------------------------\n");
        printf("    Academic Archives Library system   ");
        printf("\n-------------------------\n");
        printf("1. Admin login\n ");
        printf("2. Student login\n");
        printf("3. Registering as student\n ");
        printf("4. Forgot password\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("\n===Admin Login===\n");
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);

            if (strcmp(username, "root") == 0 && strcmp(password, "hello") == 0) 
            {
                printf("\nLogin successful!\n");
                adminMenu();
            }
            else
            {
                printf("Incorrect username or password!\n");
            }
        }
        else if(choice == 2)
        {
            studentIndex = loginStudent();
            if(studentIndex != -1)
            {
                printf("\nLogin Successful!\n");
                studentMenu(studentIndex);
            }
        }
        else if(choice == 3)
        {
            registerStudent();
        }
        else if(choice == 4)
        {
            forgotPassword();
        }
        else if(choice == 5)
        {
            saveBooks();
            saveLoans();
            saveStudents();

            printf("Thank you •‿•\n");

            //there's no need to free memory since arrays are being used instead of pointers
            return 0;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
