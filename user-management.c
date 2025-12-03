#include <stdio.h>
#include <string.h>
#include "usermanagement.h"

// SAFE INPUT FUNCTION
int getIntInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Enter a number: ");
        while (getchar() != '\n'); // clear buffer
    }
    return value;
}

// ADMIN LOGIN
void adminLogin() {
    char username[20], password[20];

    printf("\n===== ADMIN LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "root") == 0 && strcmp(password, "hello") == 0) {
        printf("\n✔ Admin logged in successfully!\n");
        // TODO: call admin menu
    } else {
        printf("\n✘ Invalid admin credentials.\n");
    }
}

// STUDENT LOGIN
void studentLogin() {
    printf("\n===== STUDENT LOGIN =====\n");
    printf("Feature not fully implemented yet.\n");
}

// REGISTER STUDENT
void registerStudent() {
    printf("\n===== STUDENT REGISTRATION =====\n");
    printf("Feature not fully implemented yet.\n");
}

// RESET PASSWORD
void resetPassword() {
    printf("\n===== RESET PASSWORD =====\n");
}

char* hashPassword(const char *plain) {
    // temporary fake hash
    return "HASHED123";
}
