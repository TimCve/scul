#include "../../DataStructures/LinkedList/LinkedList.h"
#include <stdlib.h>

int main(int argc, char** argv) {
	struct LinkedList l;
	initLinkedList(&l);

	puts("attempting retrieval from index -1");
	l.retrieve(&l, -1);
}
