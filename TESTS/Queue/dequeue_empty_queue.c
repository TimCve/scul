#include "../../DataStructures/Queue/Queue.h"
#include <stdlib.h>

int main(int argc, char** argv) {
	struct Queue q;
	initQueue(&q);

	puts("Queue is empty, dequing");
	free((int*) q.dequeue(&q));
}
