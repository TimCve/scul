#include "LinkedList.h"

struct Node* iterateLinkedList(struct LinkedList* linked_list, int index) {
	struct Node* current_node = linked_list->head;

	for(int i = 0; i < index; i++)
		current_node = current_node->next;	

	return current_node;
}

void initLinkedList(struct LinkedList* linked_list) {
	linked_list->length = 0;

	linked_list->retrieve = retrieveData;
	linked_list->insert = insertData;
	linked_list->remove = removeData;
}

void insertData(struct LinkedList* linked_list, int index, void* data) {
	if(index > linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	struct Node* new_node = malloc(sizeof(struct Node));
	new_node->data = data;
		
	if(index == 0) {
		new_node->next = linked_list->head;
		linked_list->head = new_node;
	} else {
		new_node->next = iterateLinkedList(linked_list, index);
		iterateLinkedList(linked_list, index - 1)->next = new_node;
	}

	linked_list->length += 1;
}

void* retrieveData(struct LinkedList* linked_list, int index) {
	if(index >= linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	return iterateLinkedList(linked_list, index)->data;
}

void* removeData(struct LinkedList* linked_list, int index) {
	if(index >= linked_list->length || index < 0) {
		fprintf(stderr, "List index [%d] is out of range!\n", index);
		exit(1);
	}

	void* data;
	struct Node* next_node;
	if(index == 0) {
		data = linked_list->head->data;
		next_node = linked_list->head->next;
		free(linked_list->head);
		linked_list->head = next_node;
	} else if(index == linked_list->length - 1) {
		data = iterateLinkedList(linked_list, index)->data;
		free(iterateLinkedList(linked_list, index));
	} else {
		next_node = iterateLinkedList(linked_list, index + 1);
		data = iterateLinkedList(linked_list, index)->data;
		free(iterateLinkedList(linked_list, index));
		iterateLinkedList(linked_list, index - 1)->next = next_node;
	}
 
	linked_list->length -= 1;

	return data;
}
