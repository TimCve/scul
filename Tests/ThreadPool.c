#include "../scul.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define THREAD_COUNT 6
#define TASK_COUNT 100

void threadTask(void *arg) {
	int seconds = *((int*) arg);

	printf("Sleeping for %d seconds...\n", seconds);
	sleep(seconds);
	printf("Done sleeping for %d seconds\n", seconds);
}

int main(int argc, char ** argv) {
	struct ThreadPool tp;
	initThreadPool(&tp, THREAD_COUNT);

	srand(time(NULL));
	int random_numbers[TASK_COUNT];

	for(int i = 0; i < TASK_COUNT; i++) {
		random_numbers[i] = (rand() % 10) + 1;
		tp.add(&tp, threadTask, (void*) &random_numbers[i]);
	}

	tp.gracefulHalt(&tp);
}
