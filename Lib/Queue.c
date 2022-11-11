#include <stdio.h>
#include <stdlib.h>
#include "../scul.h"

void *peek(struct Queue *queue);
void *dequeue(struct Queue *queue);
void enqueue(struct Queue *queue, void *data);

void initQueue(struct Queue *queue) {	
	queue->length = 0;
	initLinkedList(&(queue->linked_list));

	queue->peek = peek;
	queue->dequeue = dequeue;
	queue->enqueue = enqueue;
}

void *peek(struct Queue *queue) {
	void *retrieved_data;
	if(queue->length > 0) retrieved_data = queue->linked_list.retrieve(&(queue->linked_list), 0);

	return retrieved_data;
}

void *dequeue(struct Queue *queue) {
	void *retrieved_data = queue->linked_list.retrieve(&(queue->linked_list), 0);
	queue->linked_list.remove(&(queue->linked_list), 0);	
	queue->length -= 1;

	return retrieved_data;
}

void enqueue(struct Queue *queue, void *data) {
	queue->linked_list.insert(&(queue->linked_list), queue->length, data);
	queue->length += 1;
}
