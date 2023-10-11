#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

int main(int argc, char *argv[])
{
    Book books[10];
    Book test[5] = {
        {"1", "first", "author1", 2002, 1},
        {"2", "second", "author2", 2005, 1},
        {"3", "third", "author3", 2001, 0},
        {"4", "fourth", "author4", 2002, 1},
        {"5", "fifth", "author5", 2005, 1}};
    Book updateTest = {"6", "sixth", "author6", 2013, 1};
    Book newBook;
    int choice, count = 5;
    char author[20];

    displayBooksByYear(test, count);
    printf("%d\n", searchAuthor("author3", test, count));
    printf("%d\n", searchBook("second", test, count));
    printf("%d\n", isBookAvailable("third", test, count));

    updateBook(test, &count, updateTest);
    deleteBook(test, &count, "fourth");
    displayBooksByYear(test, count);

    return 0;
}