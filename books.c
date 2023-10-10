#include "books.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchAuthor(char author[], Book books[], int count) {
  int i, ctr = 0;

  for (i = 0; i < count; i++) {
    if (strcmp(books[i].author, author) == 0)
      ctr++;
  }

  return ctr++;
}

int searchBook(char title[], Book books[], int count) {
  int i, num = 0;

  for (i = 0; i < count; i++) {
    if (strcmp(books[i].title, title) == 0)
      num++;
  }

  return num;
}

int compareDates(const void *a, const void *b) {
  const Book *date1 = (const Book *)a;
  const Book *date2 = (const Book *)b;

  return strcmp(date1->datePublished, date2->datePublished);
}

void addBook(Book books[], int *count, Book newBook) {

  if (strcmp(books[*count].id, newBook.id) == 1)
    printf("Book already exists.\n");
  else
    books[*count] = newBook;

  (*count)++;
}

void display(Book books[], int count) {
  int i;

  for (i = 0; i < count; i++) {
    printf("\n");
    printf("Book id: %s\n", books[i].id);
    printf("Book title: %s\n", books[i].title);
    printf("Book author: %s\n", books[i].author);
    printf("Book publishing date: %s\n", books[i].datePublished);
    printf("Book number of copies: %d\n\n", books[i].copies);
  }
}

void displayBooksByYear(Book books[], int count) {
  int i;

  qsort(books, count, sizeof(Book), compareDates);
  for (i = 0; i < count; i++) {
    printf("\n");
    printf("Book id: %s\n", books[i].id);
    printf("Book title: %s\n", books[i].title);
    printf("Book author: %s\n", books[i].author);
    printf("Book publishing date: %s\n", books[i].datePublished);
    printf("Book number of copies: %d\n\n", books[i].copies);
  }
}