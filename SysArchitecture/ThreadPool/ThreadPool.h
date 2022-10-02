#ifndef ThreadPool_h
#define ThreadPool_h

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

#include "../../DataStructures/Queue/Queue.h"

struct ThreadPool {
	pthread_mutex_t tasks_mutex;
	pthread_cond_t task_start_signal;
	pthread_t* pool;
	struct Queue tasks;
	int thread_count;
	int running_task_count;
	int running_worker_count;
	bool halt;
	bool activated;

	int (*add)(struct ThreadPool* thread_pool, void (*func)(void*), void* arg);
	void (*gracefulHalt)(struct ThreadPool* thread_pool);
};

struct ThreadTask {
	void (*func)(void*);
	void* arg;
};

void initThreadPool(struct ThreadPool* thread_pool, int thread_count);

#endif
