#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "books.h"

void addBook(Book books[], int *count, Book newBook)
{
    if (*count == 10)
    {
        printf("Library is full.\n\n");
        return;
    }

    if (strcmp(books[*count].ISBN, newBook.ISBN) == 0)
    {
        printf("Book already exists, try adding another book.\n");
        return;
    }

    books[*count] = newBook;
    (*count)++;
    printf("Successfully added a book to the library!\n\n");
}

int searchAuthor(char author[], Book books[], int count)
{
    int i, ctr = 0;

    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].author, author) == 0)
            ctr++;
    }

    if (ctr == 0)
        return 0;

    printf("Author has %d book/s found in the library.\n\n", ctr);
    return 1;
}

int searchBook(char title[], Book books[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            printf("Book found!\n\n");
            return 1;
        }
    }

    printf("Book not found.\n\n");
    return 0;
}

void displayBooksByYear(Book books[], int count)
{
    int i, j, isUnique, uniqueYears[count], uniqueCtr = 0;
    // uniqueYears is an array that will store the years that are unique

    // this for loop checks for all unique years and stores them in an array
    for (i = 0; i < count; i++)
    {
        // isUnique is always 1 (true) unless the current yearPublished is == to at least one member of uniqueYears
        isUnique = 1;
        for (j = 0; j < uniqueCtr; j++)
        {
            if (books[i].yearPublished == uniqueYears[j])
            {
                isUnique = 0;
                break;
            }
        }

        // only adds years to the uniqueYears array if isUnique is true
        if (isUnique == 1)
        {
            uniqueYears[uniqueCtr] = books[i].yearPublished;
            uniqueCtr++;
        }
    }

    for (i = 0; i < uniqueCtr; i++)
    {
        printf("%d:\n", uniqueYears[i]);
        for (j = 0; j < count; j++)
        {
            // function call to print the books by year in order
            uniqueOrder(books, uniqueYears, i, j);
        }
        printf("\n");
    }
}

void updateBook(Book books[], int *count, Book updateBook)
{
    int i, bookFound = 0;
    // bookFound to check if book was added successfully
    char confirmation;
    for (i = 0; i < (*count); i++)
    {
        if (strcmp(books[i].ISBN, updateBook.ISBN) == 0)
        {
            books[i] = updateBook;
            bookFound = 1;
            break;
        }
    }

    if (bookFound)
        printf("Book updated successfully.\n\n");
    else
    {
        printf("%s does not exist. Do you want to add this book instead? [y/n] ", updateBook.ISBN);
        scanf(" %[^\n]c", &confirmation);
        confirmation = toupper(confirmation);
        // reuses the addBook function if user inputs Y and adds a book at the last index
        if (confirmation == 'Y')
            addBook(books, count, updateBook);
        else
            printf("Update/add failed.\n\n");
    }
}

void deleteBook(Book books[], int *count, char title[])
{
    int i;
    for (i = getIndex(books, (*count), title); i < (*count); i++)
    {
        books[i] = books[i + 1];
    }

    (*count)--;
    printf("Successfully removed book from library.\n\n");
}

int isBookAvailable(char title[], Book books[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            if (books[i].copies != 0)
            {
                printf("Book is available.\n\n");
                return 1;
            }
        }
    }

    printf("Book is not available.\n\n");
    return 0;
}

void borrowBook(char title[], Book books[], int count, char username[], BorrowedBook borrow[], int *countBorrowed)
{
    char bDate[12], dDate[12];
    float lateFee;

    if (searchBook(title, books, count) == 0)
    {
        printf("Sorry, the book %s does not exist.\n\n", title);
        return;
    }

    if (isBookAvailable(title, books, count) == 0)
    {
        printf("Sorry, all copies of the book %s have already been borrowed.\n\n", title);
        return;
    }

    int index = getIndex(books, count, title);

    printf("Enter borrowing date: ");
    scanf(" %[^\n]s", &bDate);
    printf("Enter due date: ");
    scanf(" %[^\n]s", &dDate);
    printf("Enter late fee: ");
    scanf("%f", &lateFee);

    borrow[*countBorrowed].book = books[index];
    strcpy(borrow[*countBorrowed].username, username);
    strcpy(borrow[*countBorrowed].dueDate, dDate);
    strcpy(borrow[*countBorrowed].borrowedDate, bDate);
    borrow[*countBorrowed].lateFee = lateFee;
    books[index].copies--;
    (*countBorrowed)++;
    printf("Book borrowed succesfully!\n\n");
}

void returnBook(char title[], Book books[], int count, BorrowedBook borrow[], int *countBorrowed)
{
    if (searchBook(title, books, count) == 0)
    {
        printf("Book %s does not exist.\n", title);
        return;
    }

    if (checkBorrow(borrow, &countBorrowed, title) != 1)
    {
        printf("Book %s either has not yet been borrowed or was already returned.\n", title);
        return;
    }

    char username[50];
    printf("Enter username: ");
    scanf(" %[^\n]s", &username);

    int index = getIndex(books, count, title);
    int borrIndex = getBorrIndex(borrow, &countBorrowed, title, username);
    books[index].copies++;
    deleteBorrowed(borrow, &countBorrowed, borrIndex);
    (*countBorrowed)--;
    printf("Book returned.\n\n");
}

int getIndex(Book books[], int count, char title[])
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            return i;
            break;
        }
    }

    return 0;
}

int getBorrIndex(BorrowedBook borrow[], int **countBorrowed, char title[], char username[])
{
    int i;

    for (i = 0; i < **countBorrowed; i++)
    {
        if (strcmp(borrow[i].username, username) == 0 && strcmp(borrow[i].book.title, title) == 0)
        {
            return i;
            break;
        }
    }

    return 0;
}

int checkBorrow(BorrowedBook borrow[], int **countBorrowed, char title[])
{
    int i;

    for (i = 0; i < **countBorrowed; i++)
    {
        if (strcmp(borrow[i].book.title, title) == 0)
        {
            return 1;
            break;
        }
    }

    return 0;
}

void uniqueOrder(Book books[], int uniqueYears[], int i, int j)
{
    // prints the arrays by yearPublished
    if (books[j].yearPublished == uniqueYears[i])
    {
        printf("%s - %s by %s\n", books[j].ISBN, books[j].title, books[j].author);
    }
}

void deleteBorrowed(BorrowedBook borrow[], int **countBorrowed, int at)
{
    int i;

    for (i = at; i < **countBorrowed; i++)
        borrow[i] = borrow[i + 1];
}