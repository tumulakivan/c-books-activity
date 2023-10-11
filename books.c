#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "books.h"

void addBook(Book books[], int *count, Book newBook)
{
    if (strcmp(books[*count].ISBN, newBook.ISBN) == 0)
        printf("Book already exists, try adding another book.\n");
    else
    {
        books[*count] = newBook;
        (*count)++;
    }
}

int searchAuthor(char author[], Book books[], int count)
{
    int i, ctr = 0;

    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].author, author) == 0)
            ctr++;
    }

    return ctr;
}

int searchBook(char title[], Book books[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
            return 1;
    }

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
        printf("Book updated successfully\n\n");
    else
    {
        printf("%s does not exist. Do you want to add this book instead? [y/n] ", updateBook.ISBN);
        scanf(" %[^\n]c", &confirmation);
        confirmation = toupper(confirmation);
        // reuses the addBook function if user inputs Y and adds a book at the last index
        if (confirmation == 'Y')
            addBook(books, count, updateBook);
        else
            printf("Update/add failed.\n");
    }
}

void deleteBook(Book books[], int *count, char title[])
{
    int i;
    for (i = indexViaTitle(title, books, (*count)); i < (*count); i++)
    {
        books[i] = books[i + 1];
    }

    (*count)--;
}

int isBookAvailable(char title[], Book books[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
        {
            if (books[i].copies == 0)
                return 0;
        }
    }

    return 1;
}

void uniqueOrder(Book books[], int uniqueYears[], int i, int j)
{
    // prints the arrays by yearPublished
    if (books[j].yearPublished == uniqueYears[i])
    {
        printf("%s: %s by %s\n", books[j].ISBN, books[j].title, books[j].author);
    }
}

int indexViaTitle(char title[], Book books[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(books[i].title, title) == 0)
            return i;
    }
}