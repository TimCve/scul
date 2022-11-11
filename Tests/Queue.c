#include "../scul.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	struct Queue q;
	initQueue(&q);

	puts("Enqueuing 10 integers (0 - 9)...");
	for(int i = 0; i < 10; i++) {
		int *data = malloc(sizeof(int));
		*data = i;
		q.enqueue(&q, (void*) data);
	}

	puts("Peeking at first element...");
	printf("first element: %d\n", *((int*) q.peek(&q)));

	puts("Dequeuing all elements...");
	while(q.length > 0) {
		int *data = (int*) q.dequeue(&q);
		printf("dequeued %d\n", *data);	
		free(data);
	}
}
