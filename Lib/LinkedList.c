#include <stdio.h>
#include <stdlib.h>
#include "../scul.h"

void *retrieveData(struct LinkedList *linked_list, int index);
void insertData(struct LinkedList *linked_list, int index, void *data);
void *removeData(struct LinkedList *linked_list, int index);

static struct Node *iterateLinkedList(struct LinkedList *linked_list, int index, struct Node *init_node, int init_index) {
	struct Node *current_node;
	int i = 0;
	
	if(init_node == NULL || init_index == 0) {
		current_node = linked_list->head;
	} else {
		current_node = init_node;
		i = init_index;
	}

	for(i; i < index; i++)
		current_node = current_node->next;	

	return current_node;
}

void initLinkedList(struct LinkedList *linked_list) {
	linked_list->length = 0;

	linked_list->retrieve = retrieveData;
	linked_list->insert = insertData;
	linked_list->remove = removeNode;
}

void insertData(struct LinkedList *linked_list, int index, void *data) {
	if(index > linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	struct Node *new_node = malloc(sizeof(struct Node));
	new_node->data = data;
		
	if(index == 0) {
		new_node->next = linked_list->head;
		linked_list->head = new_node;
	} else {
		struct Node *prev_node = iterateLinkedList(linked_list, index - 1, NULL, 0);

		new_node->next = iterateLinkedList(linked_list, index, prev_node, index - 1);
		prev_node->next = new_node;
	}

	linked_list->length += 1;
}

void *retrieveData(struct LinkedList *linked_list, int index) {
	if(index >= linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	return iterateLinkedList(linked_list, index, NULL, 0)->data;
}

<<<<<<< HEAD:Lib/LinkedList.c
void *removeData(struct LinkedList *linked_list, int index) {
=======
void* removeNode(struct LinkedList* linked_list, int index) {
>>>>>>> 35d8209257f305851136151fa743b24860629bb8:DataStructures/LinkedList/LinkedList.c
	if(index >= linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	void *data;
	struct Node *next_node;
	if(index == 0) {
		data = linked_list->head->data;
		next_node = linked_list->head->next;
		free(linked_list->head);
		linked_list->head = next_node;
	} else if(index == linked_list->length - 1) {
		struct Node *removed_node = iterateLinkedList(linked_list, index, NULL, 0);
		data = removed_node->data;
		free(removed_node);
	} else {
		struct Node *prev_node = iterateLinkedList(linked_list, index - 1, NULL, 0);
		struct Node *removed_node = iterateLinkedList(linked_list, index, prev_node, index - 1);

		next_node = iterateLinkedList(linked_list, index + 1, prev_node, index - 1);
		data = removed_node->data;
		free(removed_node);
		prev_node->next = next_node;
	}
 
	linked_list->length -= 1;

	return data;
}
