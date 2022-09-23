#include "ThreadPool.h"

static void* threadPoolWorker(void* arg);

void initThreadPool(struct ThreadPool* thread_pool, int thread_count) {
	thread_pool->halt = false;
	thread_pool->activated = false;

	thread_pool->thread_count = thread_count;
	thread_pool->running_worker_count = 0;
	thread_pool->running_task_count = 0;

	pthread_mutex_init(&(thread_pool->tasks_mutex), NULL);
	pthread_cond_init(&(thread_pool->task_start_signal), NULL);
	initQueue(&(thread_pool->tasks));

	thread_pool->pool = calloc(thread_count, sizeof(pthread_t));
	for(int i = 0; i < thread_count; i++)
		pthread_create(&(thread_pool->pool[i]), NULL, threadPoolWorker, (void*) thread_pool);

	thread_pool->add = threadPoolAddTask;
	thread_pool->gracefulHalt = threadPoolGracefulHalt;

	thread_pool->activated = true;
}

int threadPoolAddTask(struct ThreadPool* thread_pool, void (*func)(void*), void* arg) {	
	if(thread_pool->activated) {
		struct ThreadTask* task = malloc(sizeof(struct ThreadTask));
		task->func = func;
		task->arg = arg;

		pthread_mutex_lock(&(thread_pool->tasks_mutex));	
		thread_pool->tasks.enqueue(&(thread_pool->tasks), (void*) task);
		pthread_mutex_unlock(&(thread_pool->tasks_mutex));
	
		pthread_cond_signal(&(thread_pool->task_start_signal));

		return 0;
	} else return 1;
}

void threadPoolGracefulHalt(struct ThreadPool* thread_pool) {
	thread_pool->halt = true;
	thread_pool->activated = false;

	pthread_mutex_lock(&(thread_pool->tasks_mutex));
	pthread_cond_broadcast(&(thread_pool->task_start_signal));	
	pthread_mutex_unlock(&(thread_pool->tasks_mutex));

	for(int i = 0; i < thread_pool->thread_count; i++)
		pthread_join(thread_pool->pool[i], NULL);

	free(thread_pool->pool);

	pthread_mutex_destroy(&(thread_pool->tasks_mutex));
	pthread_cond_destroy(&(thread_pool->task_start_signal));
}

static void* threadPoolWorker(void* arg) {
	struct ThreadPool* thread_pool = (struct ThreadPool*) arg;
	struct ThreadTask task;

	while(!thread_pool->halt && !thread_pool->activated) continue;
	while(true) {
		pthread_mutex_lock(&(thread_pool->tasks_mutex));

		while(!thread_pool->halt && thread_pool->tasks.length == 0) {
			pthread_cond_wait(&(thread_pool->task_start_signal), &(thread_pool->tasks_mutex));
		}

		if(thread_pool->tasks.length > 0) {
			task = *((struct ThreadTask*) thread_pool->tasks.peek(&(thread_pool->tasks)));
			free((struct ThreadTask*) thread_pool->tasks.dequeue(&(thread_pool->tasks)));

			pthread_mutex_unlock(&(thread_pool->tasks_mutex));

			thread_pool->running_task_count++;
			(*(task.func))(task.arg);
			thread_pool->running_task_count--;
		} else {
			pthread_mutex_unlock(&(thread_pool->tasks_mutex));
			break;
		}
		
		if(thread_pool->tasks.length > 0)
			pthread_cond_signal(&(thread_pool->task_start_signal));
	}

	pthread_exit(NULL);
	return NULL;
}
