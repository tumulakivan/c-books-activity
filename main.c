#include <stdio.h>
#include <string.h>
#include "books.h"

int main()
{
	Book books[10];
	Book newBook; // in case a new book is to be added to the array
	int count = 0, cp, choice;
	char id[5], t[100], auth[50], dP[12];

	printf("Hello, welcome to library!\n");
	while (1)
	{
		printf("\nWhat would you like to do?\n");
		printf("1.) Add a book\n");
		printf("2.) Search for a book with a specific title\n");
		printf("3.) Search for a book from a specific author\n");
		printf("4.) Display all books by publishing year\n");

		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			printf("\nProgram terminated.\n");
			return 1;
		case 1:
			printf("\nEnter book id: ");
			scanf(" %[^\n]s", &newBook.id);
			printf("Enter book title: ");
			scanf(" %[^\n]s", &newBook.title);
			printf("Enter book author: ");
			scanf(" %[^\n]s", &newBook.author);
			printf("Enter date published: ");
			scanf(" %[^\n]s", &newBook.datePublished);
			printf("Enter number of copies: ");
			scanf("%d", &newBook.copies);
			addBook(books, &count, newBook);
			if (count > 0)
				printf("Added book successfully!\n");
			printf("%s\n", newBook.title);
			break;
		case 2:
			printf("\nEnter title search: ");
			scanf(" %[^\n]s", t);
			if (searchBook(t, books, count) == 1)
				printf("Book found!\n");
			else
				printf("Book not found.\n");
			break;
		case 3:
			printf("\nEnter author search: ");
			scanf(" %[^\n]s", auth);
			if (searchAuthor(auth, books, count) > 0)
				printf("%d book/s by %s found!\n", searchAuthor(auth, books, count), auth);
			else
				printf("No entries by %s.\n", auth);
			break;
		case 4:
			printf("\nBooks sorted by publishing year.\n");
			displayBooksByYear(books, count);
			break;
		default:
			printf("\nInvalid option.\n");
			break;
		}
	}

	return 0;
}