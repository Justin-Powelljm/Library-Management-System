#include "user-management.h"
#include "library-management.h"
#include <sdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 64 // To store the hashed value of the password 

struct Student {
    char full_name[50];
    char user_name[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

struct Admin {
    char user_name[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};


