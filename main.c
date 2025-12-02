#include "user-management.h"
#include "library-management.h"
#include <stdio.h>
#include <stdlib.h>

Void mainmenu();
int Adminlogin();
void Adminmenu();
void Studentmenu(int sid);
void Save_all_data();


int main () {
    srand(time(NULL));
    load_books_from_file();
    rebuild_books_pstr();

    
    return 0;
}

void mainmenu {
    int choice;

while (1){ 
   printf("\n-------------------------\n");
   printf("    Academic Archives Library system   ");
   printf("\n-------------------------\n");
   printf("1. Admin login\n ");
   printf("2. Student login\n");
   printf("3. Registering as student\n ");
   printf("4. Forgot password\n");
   printf("5. Exit\n");
   printf("------------------------------\n");
   printf("Please select\n");
   scanf("%d, &choice);

       switch (choice) {

case :1 
    if (Adminlogin()) {
        Adminmenu ();
} else { 
  printf("Invalid Admin credentials\n.");
}
break;

case 2: {
int sid = studentlogin();
if (sid >=0) {
 
  StudentMenu(sid);
            } else {
                printf("Invalid student login.\n");
            }
            break;
        }

case 3:
registerStudent();
break;

        case 4:
            forgotPassword();
            break;

        case 5:
            printf("Saving new data...\n");
            save_all_data();
            printf("Exisitng...\n");
            return;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}


// -------------------- DATA SAVE WRAPPER --------------------

void save_all_data() {
    saveBooksToFile();
    saveStudentsToFile();
}

// -------------------- ADMIN LOGIN --------------------

int AdminLogin() {
    char username[50], password[50];

    printf("Admin username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Admin password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, "root") == 0 && strcmp(password, "hello") == 0) {
        return 1;
    }
    return 0;
}








