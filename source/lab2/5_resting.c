#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
	char* title;
	char* author;
	struct Book* next;
};
typedef struct Book Book;

Book* create_book(char* title, char* author) {
	Book* b = malloc(sizeof(Book));
	b->title = title;
	b->author = author;
	return b;
}

Book* create_books() {
	Book* ulder = create_book("Cleaning the streets Beyond the Gate", "Ulder Ravengard");
	Book* drizzt = create_book("Beyond the depths of the Underdark", "Drizzt Do'Urden");
	Book* elminster = create_book("Ancient Aberrations and how to prevent them", "Elminster Aumar");
	Book* neera = create_book("Killing people with cows: the ins and outs of Wild Magic", "Neera");

	ulder->next = drizzt;
	drizzt->next = elminster;
	elminster->next = neera;
	neera->next = NULL;

    return ulder;
}

void print_books(Book* library) {
	Book* ptr = library;
    while(ptr) {
        printf("%s, by %s\n", ptr->title, ptr->author);
        ptr = ptr->next;
    }
}

void add_book(Book* library, Book* book) {
	Book* ptr = library;
	while(ptr->next) {
		ptr = ptr->next;
	}
	ptr->next = book;
	book->next = NULL;
}

void add_book_beginning(Book** library, Book* book) {
	book->next = *library;
	*library = book;
}

int main() {
    Book* library = create_books();
    Book* newbook = create_book("My adventures", "The Hero");
    //add_book(library, newbook);
    add_book_beginning(&library, newbook);

    print_books(library);
    return 0;
}