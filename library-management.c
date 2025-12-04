#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "user-management.h"
#include "library-management.h"

// Global pointer arrays
Book *books[MAXBOOKS];
Loan *loans[MAXLOANS];
int bookCount = 0;
int loanCount = 0;

void clearInput()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//Recursion (Function to convert string to lowercase)
void convertLcase(char *str, int index)
{
    if(str[index] == '\0')
    {
        return;
    }
    str[index] = tolower(str[index]);
    convertLcase(str, index + 1)
}

//load books from the binary file
void loadBooks()
{
    FILE *fp = fopen("books.dat", "rb");
    if(file != NULL)
    {
        fread(&bookCount, sizeof(int), 1, fp);
        for(int j = 0; j < bookCount; j++)
        {
            books[j] = (Book*)malloc(sizeof(Book));
            fread(books[j], sizeof(Book), 1 ,fp);
        }
        fclose(fp);
    } 
    else
    {
        bookCount = 0;
    }
}

// Save books to binary file
void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    if (fp != NULL) {
        fwrite(&bookCount, sizeof(int), 1, fp);
        for(int i = 0; i < bookCount; i++) {
            fwrite(books[i], sizeof(Book), 1, fp);
        }
        fclose(fp);
    }
}

//load loans from the binary file
void loadLoans()
{
    FILE *fp5 = fopen("loans.dat, "rb");
    if(fp != NULL)
    {
        fread(&loanCount, sizeof(int), 1, fp);
        for(int j = 0; j < loanCont;  j++)
        {
            loans[j] = (Loan*)malloc(sizeof(Loan));
            fread(loans[j], sizeof(Loan), 1, fp);
        }
        fclose(fp);
    }
    else
    {
        loanCount = 0;
    }
}

void saveloans()
{
    FILE *fp = fopen("loans.dat", "wb");
    if (fp != NULL)
    {
        fwrite(&loanCount, sizeof(int, 1, fp);
        for(int i = 0; i < loanCount; i++)
        {
            fwrite(loans[i], sizeof(Loan), 1, fp);
        }
        fclose(fp);
    }
}

// ADD BOOK
void AddBook() {
    if(bookCount >= MAXBOOKS) {
        printf("Library is full!\n");
        return;
    }

    //Allocate memory for new book(s)
    books[bookCount] = (Book*)malloc(sizeof(Book));

    printf("\n----- ADD NEW BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %s", books[bookCount].isbn);
    clearInput();

    printf("Enter Title: ");
    fgets(books[bookCount].title, 100, stdin);
    books[bookCount].title[strcspn(books[bookCount].title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(books[bookCount].author, 50, stdin);
    books[bookCount].author[strcspn(books[bookCount].author, "\n")] = 0;

    printf("Enter Publication Year: ");
    scanf("%d", &books[bookCount].year);

    printf("Enter Quantity: ");
    scanf("%d", &books[bookCount].quantity);

    if(books[bookCount].quantity > 0) {
        books[bookCount].available = 1;
    }
    else {
        books[bookCount].available = 0;
    }

    bookCount++;

    printf("\n✔ Book added successfully!\n");
    saveBooks();
}

// LIST ALL BOOKS
void showAllBooks() {
    printf("\n----- LIST OF BOOKS -----\n");

    if (bookCount == 0) {
        printf("No books in the system.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        printf("\nBook #%d\n", i + 1);
        printf("ISBN: %s\n", books[i].ISBN);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Year: %d\n", books[i].year);
        printf("Quantity: %d\n", books[i].quantity);
        printf("Status: %s\n", books[i].available ? "Available" : "Unavailable");
    }
}

// SEARCH BOOK
void searchBook() {
    char search[100];
    char temp[100];
    int choice;
    int found = 0;

    printf("\n--- Search Book ---\n");
    printf("1. By Title\n");
    printf("2. By Author\n");
    printf("Choice: ");
    scanf("%d", &choice);
    clearInput();

    printf("Search: ");
    fgets(search, 100, stdin);
    search[strcspn(search, "\n")] = 0;
    
    //recursive function to convert to lowercase
    convertLowercase(search, 0);
    
    for (i = 0; i < bookCount; i++) {
        int match = 0;
        
        if (choice == 1) {
            strcpy(temp, books[i].title);
            convertLowercase(temp, 0);
            if (strstr(temp, search) != NULL) {
                match = 1;
            }
        } else if (choice == 2) {
            strcpy(temp, books[i].author);
            convertLowercase(temp, 0);
            if (strstr(temp, search) != NULL) {
                match = 1;
            }
        }
        if (match) {
            printf("%-15s %-30s %-20s %-6d %-8d %-10s\n",
                   books[i].isbn, books[i].title, books[i].author,
                   books[i].year, books[i].quantity,
                   books[i].available ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) {
        printf("\n✘ No matching book found.\n");
    }
}

// DELETE BOOK
void deleteBook() {
    char isbn[20];
    printf("\n----- DELETE BOOK -----\n");

    printf("Enter ISBN of book to delete: ");
    scanf(" %s", isbn);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            int found = 1;
            //Check if book is loaned
            for(int j = 0; j < loanCount; j++) {
                if(strcmp(loans[j].isbn, isbn)== 0) {
                    printf("CANNOT DELETE!! BOOK IS BORROWED\n");
                    return;
                }
            }
            //Shift down
            for(j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("✔ Book deleted successfully.\n");
            saveBooks();
            return;
        }
            
    }
    if(!found) {
        printf("✘ Book not found.\n");
    }
}

// UPDATE BOOK
void updateBook() {
    char isbn[20];
    printf("\n----- UPDATE BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %s", isbn);
    clearInput();

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            int found = 1
            printf("\nBook: %s by %s\n", books[i].title, books[i].author);
            printf("\n1. Change Title\n");
            printf("2. Change Author\n");
            printf("3. Change Year\n");
            printf("4. Change Quantity\n");
            printf("Choice: ");
            scanf("%d", &choice);
            clearInput();

            if(choice ==1) {
                printf("New title: ");
                fgets(books[i].title, 100, stdin);
                books[i].title[strcspn(books[i].title, "\n")] = 0;
            } else if (choice == 2) {
                printf("New author: ");
                fgets(books[i].author, 50, stdin);
                books[i].author[strcspn(books[i].author, "\n")] = 0;
            } else if (choice == 3) {
                printf("New year: ");
                scanf("%d", &books[i].year);
            } else if (choice == 4) {
                printf("New quantity: ");
                scanf("%d", &books[i].quantity);
                if (books[i].quantity > 0) {
                    books[i].available = 1;
                } else {
                    books[i].available = 0;
                }
            } else {
                printf("Invalid choice.\n");
                return;
            }
            
            printf("✔ Book updated successfully.\n");
            saveBooks();
            return;

        }
    }
    if(!found) {
        printf("✘ Book not found.\n");
    }
}

// BORROW BOOK
void borrowBook() {
    char isbn[20];
    printf("\n----- BORROW BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %s", isbn);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, isbn) == 0) {

            if (books[i].quantity == 0) {
                printf("✘ This book is unavailable.\n");
                return;
            }

            books[i].quantity--;
            books[i].available = books[i].quantity > 0;

            saveBooks();
            printf("✔ Book borrowed successfully.\n");
            return;
        }
    }

    printf("✘ Book not found.\n");
}

// RETURN BOOK
void returnBook() {
    char isbn[20];
    printf("\n----- RETURN BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %[^\n]", isbn);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, isbn) == 0) {

            books[i].quantity++;
            books[i].available = 1;

            saveBooks();
            printf("✔ Book returned successfully.\n");
            return;
        }
    }

    printf("✘ Book not found.\n");
}




