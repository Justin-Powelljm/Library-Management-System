#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "user-management.h"
#include "library-management.h"

//Change from pointer array to object array
Student students[MAXSTUDENTS];
int studentCount = 0;

//Generate OTP
void generateOTP(char *otp)
{
    srand(time(NULL));
    for(int i = 0; i < 6; i++)
    {
        otp[i] = '0' + (rand() % 10);
    }
    otp[6] = '\0';
}

//function to count students
int countStudents(int i) 
{
    if (i >= studentCount) 
    {
        return 0;
    }
    return 1 + countStudents(i + 1);
}

void loadStudents() 
{
    FILE *fp = fopen("students.dat", "rb");
    if (fp != NULL) 
    {
        fread(&studentCount, sizeof(int), 1, fp);
        for (int i = 0; i < studentCount; i++) 
        {
            fread(&students[i], sizeof(Student), 1, fp);
        }
        fclose(fp);
    } 
    else 
    {
        studentCount = 0;
    }
}

void saveStudents() 
{
    FILE *fp = fopen("students.dat", "wb");
    if (fp != NULL) 
    {
        fwrite(&studentCount, sizeof(int), 1, fp);
        for (i = 0; i < studentCount; i++) 
        {
            fwrite(&students[i], sizeof(Student), 1, fp);
        }
        fclose(fp);
    }
}

void registerStudent() 
{
    char otp[7];
    
    if (studentCount >= MAXSTUDENTS) 
    {
        printf("Maximum students reached!\n");
        return;
    }
    
    printf("\n=== Register ===\n");
    printf("First Name: ");
    scanf("%s", students[studentCount].firstName);
    
    printf("Last Name: ");
    scanf("%s", students[studentCount].lastName);
    
    sprintf(students[studentCount].studentId, "STU%04d", studentCount + 1);
    
    generateOTP(otp);
    strcpy(students[studentCount].password, otp);
    students[studentCount].firstLogin = 1;
    
    printf("\n*** Registration Complete ***\n");
    printf("Student ID: %s\n", students[studentCount].studentId);
    printf("Password: %s\n", otp);
    printf("Save this!\n");
    
    studentCount++;
    saveStudents();
}

void forgotPassword() 
{
    char first[50], last[50];
    char newOTP[7];
    int found = 0;
    
    printf("\n=== Forgot Password ===\n");
    printf("First Name: ");
    scanf("%s", first);
    printf("Last Name: ");
    scanf("%s", last);
    
    for (int i = 0; i < studentCount; i++) 
    {
        if (strcasecmp(students[i].firstName, first) == 0 &&
            strcasecmp(students[i].lastName, last) == 0) 
        {
            found = 1;
            
            generateOTP(newOTP);
            strcpy(students[i].password, newOTP);
            students[i].firstLogin = 1;
            
            printf("\nNew password: %s\n", newOTP);
            printf("Change it on next login.\n");
            
            saveStudents();
            return;
        }
    }
    
    if (!found) 
    {
        printf("Student not found!\n");
    }
}

int loginStudent() 
{
    char id[20], pwd[50];
    
    printf("\n=== Student Login ===\n");
    printf("Student ID: ");
    scanf("%s", id);
    
    printf("Password: ");
    scanf("%s", pwd);
    
    for (int i = 0; i < studentCount; i++) 
    {
        if (strcmp(students[i].studentId, id) == 0) 
        {
            if (strcmp(students[i].password, pwd) == 0) 
            {
                if (students[i].firstLogin == 1) 
                {
                    printf("\nFirst login. Change your password.\n");
                    changePassword(i);
                }
                return i;
            } 
            else 
            {
                printf("Wrong password!\n");
                return -1;
            }
        }
    }
    
    printf("Student ID not found!\n");
    return -1;
}

void changePassword(int studentIndex) 
{
    char newPass[50], confirm[50];
    
    printf("\n=== Change Password ===\n");
    printf("New password: ");
    scanf("%s", newPass);
    
    printf("Confirm password: ");
    scanf("%s", confirm);
    
    if (strcmp(newPass, confirm) != 0) 
    {
        printf("Passwords don't match!\n");
        return;
    }
    
    strcpy(students[studentIndex].password, newPass);
    students[studentIndex].firstLogin = 0;
    
    printf("Password changed!\n");
    saveStudents();
}

void adminChangePassword() 
{
    char id[20];
    char newOTP[7];
    int found = 0;
    
    printf("\n=== Change Student Password ===\n");
    printf("Student ID: ");
    scanf("%s", id);
    
    for (int i = 0; i < studentCount; i++) 
    {
        if (strcmp(students[i].studentId, id) == 0) 
        {
            found = 1;
            
            generateOTP(newOTP);
            strcpy(students[i].password, newOTP);
            students[i].firstLogin = 1;
            
            printf("\nPassword reset!\n");
            printf("New password: %s\n", newOTP);
            
            saveStudents();
            return;
        }
    }
    
    if (!found) 
    {
        printf("Student not found!\n");
    }
}

void studentMenu(int studentIndex) 
{
    int choice;
    int total;
    
    printf("\nWelcome %s %s!\n", 
           students[studentIndex].firstName, 
           students[studentIndex].lastName);
    
    //use the recursive function
    total = countStudents(0);
    printf("Total registered students: %d\n", total);
    
    while (1) {
        printf("\n=== Student Menu ===\n");
        printf("1. Search Book\n");
        printf("2. List Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Change Password\n");
        printf("6. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) 
        {
            searchBook();
        } 
        else if (choice == 2) 
        {
            showAllBooks();
        } 
        else if (choice == 3) 
        {
            borrowBook(studentIndex);
        } 
        else if (choice == 4) 
        {
            returnBook(studentIndex);
        } 
        else if (choice == 5) 
        {
            changePassword(studentIndex);
        } 
        else if (choice == 6) 
        {
            break;
        } 
        else 
        {
            printf("Invalid choice!\n");
        }
    }
}

void getStudentId(int studentIndex, char *id) 
{
    strcpy(id, students[studentIndex].studentId);
}
