#ifndef LIBRARY_MANAGEMENT_H
#define LIBRARY_MANAGEMENT_H

#define MAXBOOKS 100
#define MAXLOANS 100
#define BOOKSFILE "books.dat"
#define LOANSFILE "loans.dat"

typedef struct
{
  char isbn[20];
  char title[100];
  char author[50];
  int year;
  int quantity;
  int available;
} Book;

typedef struct
{
  char studentID[20];
  char isbn[20];
} Loan;


void loadBooksNloans();
void saveBooksNloans();
void AddBook();
void deleteBook();
void updateBook();
void searchBook();
void showAllBooks();
void borrowBook(int stuI);
void returnBook(int stuI);
int BookIsLoaned(const char* isbn);
void adminMenu();
void convertLcase(char *str, int index);

#endif

