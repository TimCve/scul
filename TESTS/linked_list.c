#include "../DataStructures/LinkedList/LinkedList.h"
#include <stdlib.h>

void print_contents(struct LinkedList* l) {
	puts("Retrieving list contents...");
	for(int i = 0; i < l->length; i++)
		printf("index: %d | data: %d\n", i, *((int*) l->retrieve(l, i)));
}

int main(int argc, char** argv) {
	struct LinkedList l;
	initLinkedList(&l);

	puts("Inserting 10 integers (0 - 9)...");
	for(int i = 0; i < 10; i++) {
		int* data = malloc(sizeof(int));
		*data = i;
		l.insert(&l, l.length, (void*) data);
	}

	print_contents(&l);

	puts("Removing first element...");
	free((int*) l.remove(&l, 0));

	print_contents(&l);
	
	puts("Removing last element...");
	free((int*) l.remove(&l, l.length - 1));

	print_contents(&l);
}
