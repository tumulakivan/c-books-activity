typedef struct Book
{
	char id[5];
	char title[100];
	char author[50];
	char datePublished[10];
	int copies;
} Book;

int searchAuthor(char author[], Book books[], int count);
int searchBook(char title[], Book books[], int count);
int compareDates(const void *a, const void *b);
void addBook(Book books[], int *count, Book newBook);
void display(Book books[], int count);
void displayBooksByYear(Book books[], int count);