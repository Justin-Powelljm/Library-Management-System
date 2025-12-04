#ifndef user-management_h
#define user-management_h

#define MAXSTUDENTS 50

typedef struct 
{
  char firstName[50];
  char lastName[50];
  char password[50];
  int firstLogin;
  char studentID[20];
} Student;

void loadStudents();
void saveStudents();
void registerStudent();
int loginStudent();
void changePassword(int studentIndex)
void adminChangePassword();
void forgotPassword();
void studentMenu(int studentIndex);
void getTudentID(int studentIndex), char *id);
int countStudents(int i);

#endif
