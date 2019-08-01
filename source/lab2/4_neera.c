#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*sorter)(char*, char*);

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

Book* find_min(Book* library) {
	Book* min = library;
	Book* ptr = library;
	while(ptr) {
		if(sorter(ptr->author, min->author)) {
			min = ptr;
		}
		ptr = ptr->next;
	}
	printf("found min: %s\n", min->author);
	return min;
}

void swap(Book* one, Book* two) {
	printf("swapping %s with %s\n", one->author, two->author);
	char* tmpTitle = one->title;
	char* tmpAuthor = one->author;

	one->title = two->title;
	one->author = two->author;
	two->title = tmpTitle;
	two->author = tmpAuthor;
}

void sort_books(Book* library) {
	printf("sorting books, head: %s\n", (library ? library->author : "none"));
	if(library == NULL)
		return;

	Book* min = find_min(library);
	swap(library, min);
	sort_books(library->next);
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

int asc(char* a, char* b) {
	return strcmp(a, b) < 0;
}
int desc(char* a, char* b) {
	return strcmp(a, b) > 0;
}

void neera_encounter() {
	sorter = &desc;
}

int main() {
	sorter = &asc;
    Book* library = create_books();
    neera_encounter();

    sort_books(library);
    printf("\n");
    print_books(library);               // should print the above list ([title], by [author])
    return 0;
}