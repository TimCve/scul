#include "../SysArchitecture/ThreadPool/ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define THREAD_COUNT 6
#define TASK_COUNT 100
#define CPU_INTENSIVE true

void threadTask(void* arg) {
	if(CPU_INTENSIVE) {
		/* arbitrary large multiplier
		 * (loop has to iterate constantly to consume a lot of CPU resources) */
		int loop_iterations = *((int*) arg) * 10000000;
		int loop_counter = 0;
		
		printf("Iterating %d times...\n", loop_iterations);
		while(loop_counter < loop_iterations) loop_counter++;
		printf("Done iterating %d times\n", loop_iterations);
	} else {
		int seconds = *((int*) arg);

		printf("Sleeping for %d seconds...\n", seconds);
		sleep(seconds);
		printf("Done sleeping for %d seconds\n", seconds);
	}
}

int main(int argc, char** argv) {
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
