#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
struct Book {
	char title[100];
	char author[100];
};
typedef struct Book Book;

Book* create_books() {
	Book ulder = {
		"Cleaning the streets Beyond the Gate",
		"Ulder Ravengard"
	};
	Book drizzt = {
		"Beyond the depths of the Underdark",
		"Drizzt Do'Urden"
	};
	Book elminster = {
		"Ancient Aberrations and how to prevent them",
		"Elminster Aumar"
	};
	Book neera = {
		"Killing people with cows: the ins and outs of Wild Magic",
		"Neera"
	};

    Book* library = malloc(sizeof(Book) * SIZE);
    library[0] = ulder;
    library[1] = drizzt;
    library[2] = elminster;
    library[3] = neera;

    return library;
}

void print_books(Book* library) {
	Book* ptr = library;
    for(int i = 0; i < SIZE; i++) {
        printf("%s, by %s\n", ptr->title, ptr->author);
        ptr++;
    }
}

int main() {
    Book* library = create_books();
    print_books(library);               // should print the above list ([title], by [author])
    return 0;
}