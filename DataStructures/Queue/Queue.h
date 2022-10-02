#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdlib.h>

#include "../LinkedList/LinkedList.h"

struct Queue {
	int length;
	struct LinkedList linked_list;
	
	void* (*peek)(struct Queue* queue);
	void* (*dequeue)(struct Queue* queue);
	void (*enqueue)(struct Queue* queue, void* data);
};

void initQueue(struct Queue* queue);

#endif
