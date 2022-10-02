#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

struct LinkedList {
	struct Node* head;
	int length;

	void* (*retrieve)(struct LinkedList* linked_list, int index);
	void (*insert)(struct LinkedList* linked_list, int index, void* data);
	void* (*remove)(struct LinkedList* linked_list, int index);
};

void initLinkedList(struct LinkedList* linked_list);

#endif
