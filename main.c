#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

int main(int argc, char *argv[])
{
    Book books[10];
    Book temp;
    BorrowedBook borrow[50];
    char author[50], title[50], username[50], isbn[50];
    int year, copies, choice, count = 0, countBorrowed = 0;

    while (1)
    {
        printf("----welcome message here----\n");
        printf("Options\n");
        printf("1 - Add a book\n");
        printf("2 - Search for an author\n");
        printf("3 - Search for a title\n");
        printf("4 - Sort books by publishing year\n");
        printf("5 - Update a book\n");
        printf("6 - Remove a book from the library\n");
        printf("7 - Inquire for availability of a book\n");
        printf("8 - Borrow a book\n");
        printf("9 - Return a book\n");
        printf("0 - Exit the library\n");
        scanf("%d", &choice);
        system("cls");

        switch (choice)
        {
        case 1:
            if (count >= 10)
            {
                printf("Library is full.\n\n");
                break;
            }

            printf("Enter ISBN: ");
            scanf(" %[^\n]", &isbn);
            printf("Enter title: ");
            scanf(" %[^\n]", &title);
            printf("Enter author: ");
            scanf(" %[^\n]", &author);
            printf("Enter year: ");
            scanf("%d", &year);
            printf("Enter number of copies: ");
            scanf("%d", &copies);

            strcpy(temp.ISBN, isbn);
            strcpy(temp.title, title);
            strcpy(temp.author, author);
            temp.yearPublished = year;
            temp.copies = copies;
            addBook(books, &count, temp);

            break;

        case 2:
            printf("Enter author: ");
            scanf(" %[^\n]", &author);

            searchAuthor(author, books, count);

            break;

        case 3:
            printf("Enter title: ");
            scanf(" %[^\n]", &title);

            searchBook(title, books, count);

            break;

        case 4:
            displayBooksByYear(books, count);

            break;

        case 5:
            printf("Enter ISBN: ");
            scanf(" %[^\n]", &isbn);
            printf("Enter title: ");
            scanf(" %[^\n]", &title);
            printf("Enter author: ");
            scanf(" %[^\n]", &author);
            printf("Enter year: ");
            scanf("%d", &year);
            printf("Enter number of copies: ");
            scanf("%d", &copies);

            strcpy(temp.ISBN, isbn);
            strcpy(temp.title, title);
            strcpy(temp.author, author);
            temp.yearPublished = year;
            temp.copies = copies;
            updateBook(books, &count, temp);

            break;

        case 6:
            if (count == 0)
            {
                printf("No books to delete\n\n");
                break;
            }

            printf("Enter title to be deleted: ");
            scanf(" %[^\n]", &title);

            deleteBook(books, &count, title);

            break;

        case 7:
            printf("Enter title: ");
            scanf(" %[^\n]", &title);

            isBookAvailable(title, books, count);

            break;

        case 8:
            printf("Enter title: ");
            scanf(" %[^\n]", &title);
            printf("Enter username: ");
            scanf(" %[^\n]", &username);

            borrowBook(title, books, count, username, borrow, &countBorrowed);

            break;

        case 9:
            printf("Enter title: ");
            scanf(" %[^\n]", &title);

            returnBook(title, books, count, borrow, &countBorrowed);

            break;

        case 0:
            printf("Thanks for using the library!\n\n");
            exit(0);
            break;

        default:
            printf("Invalid input.\n\n");
            break;
        }
    }

    return 0;
}