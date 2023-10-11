typedef struct
{
    char ISBN[20];
    char title[50];
    char author[50];
    int yearPublished;
    int copies;
} Book;

typedef struct
{
    Book book;
    char username[50];
    char dueDate[12];
    char borrowedDate[12];
    float lateFee;
} BorrowedBook;

void addbook(Book books[], int *count, Book newBook);
int searchAuthor(char author[], Book books[], int count);
int searchBook(char title[], Book books[], int count);
void displayBooksByYear(Book books[], int count);
void updateBook(Book books[], int *count, Book updateBook);
void deleteBook(Book books[], int *count, char title[]);
int isBookAvailable(char title[], Book books[], int count);
void borrowBook(char title[], Book books[], int *count, char username[], BorrowedBook borrow[], int *countBorrowed);
void returnBook(char title[], Book books[], int *count, BorrowedBook borrow[], int *countBorrowed);
void uniqueOrder(Book books[], int uniqueYears[], int i, int j);
int indexViaTitle(char title[], Book books[], int count);