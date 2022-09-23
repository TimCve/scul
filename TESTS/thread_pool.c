#include "../SysArchitecture/ThreadPool/ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 6

void waitSeconds(void* arg) {
	int seconds = *((int*) arg);

	printf("Sleeping for %d seconds...\n", seconds);
	sleep(seconds);
	printf("Done sleeping for %d seconds\n", seconds);
}

int main(int argc, char** argv) {
	struct ThreadPool tp;
	initThreadPool(&tp, THREAD_COUNT);

	srand(time(NULL));
	int random_numbers[100];

	for(int i = 0; i < 100; i++) {
		random_numbers[i] = (rand() % 10) + 1;
		tp.add(&tp, waitSeconds, (void*) &random_numbers[i]);
	}

	tp.gracefulHalt(&tp);
}
