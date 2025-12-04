#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <"user-management.h>
#include "library management.h"

// Global array of books
Book *books[MAXBOOKS];
Loan *loans[MAXLOANS]
int bookCount = 0;
int loanCount = 0;


// Save books to binary file
void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("Error saving books!\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

// Load books from binary file
void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) return; // file doesn't exist yet

    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

// ADD BOOK
void addBook() {
    Book b;

    printf("\n----- ADD NEW BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %[^\n]", b.ISBN);

    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);

    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);

    printf("Enter Publication Year: ");
    scanf("%d", &b.year);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    b.available = (b.quantity > 0);

    books[bookCount++] = b;

    saveBooks();
    printf("\n✔ Book added successfully!\n");
}

// LIST ALL BOOKS
void listBooks() {
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
    char keyword[100];
    int found = 0;

    printf("\n----- SEARCH BOOK -----\n");
    printf("Enter Title or Author: ");
    scanf(" %[^\n]", keyword);

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
            printf("\nFound Book:\n");
            printf("ISBN: %s\n", books[i].ISBN);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("Quantity: %d\n", books[i].quantity);
            printf("Status: %s\n", books[i].available ? "Available" : "Unavailable");
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
    scanf(" %[^\n]", isbn);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, isbn) == 0) {
            if (books[i].quantity != books[i].available) {
                printf("✘ Cannot delete a book that is loaned out!\n");
                return;
            }

            // Shift left
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }

            bookCount--;
            saveBooks();

            printf("✔ Book deleted successfully.\n");
            return;
        }
    }

    printf("✘ Book not found.\n");
}

// UPDATE BOOK
void updateBook() {
    char isbn[20];
    printf("\n----- UPDATE BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %[^\n]", isbn);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, isbn) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &books[i].quantity);

            books[i].available = books[i].quantity > 0;

            saveBooks();
            printf("✔ Book updated successfully.\n");
            return;
        }
    }

    printf("✘ Book not found.\n");
}

// BORROW BOOK
void borrowBook() {
    char isbn[20];
    printf("\n----- BORROW BOOK -----\n");

    printf("Enter ISBN: ");
    scanf(" %[^\n]", isbn);

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


