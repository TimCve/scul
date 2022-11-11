#ifndef scul_h
#define scul_h

#include <stdbool.h>
#include <pthread.h>

struct Node {
	void *data;
	struct Node *next;
};

struct LinkedList {
	struct Node *head;
	int length;
	void *(*retrieve)(struct LinkedList *linked_list, int index);
	void (*insert)(struct LinkedList *linked_list, int index, void *data);
	void *(*remove)(struct LinkedList *linked_list, int index);
};

void initLinkedList(struct LinkedList *linked_list);

struct Queue {
	int length;
	struct LinkedList linked_list;	
	void *(*peek)(struct Queue *queue);
	void *(*dequeue)(struct Queue *queue);
	void (*enqueue)(struct Queue *queue, void *data);
};

void initQueue(struct Queue *queue);

struct ThreadPool {
	pthread_mutex_t tasks_mutex;
	pthread_cond_t task_start_signal;
	pthread_t *pool;
	struct Queue tasks;
	int thread_count;
	int running_task_count;
	int running_worker_count;
	bool halt;
	bool activated;
	int (*add)(struct ThreadPool *thread_pool, void (*func)(void*), void *arg);
	void (*gracefulHalt)(struct ThreadPool *thread_pool);
};

struct ThreadTask {
	void (*func)(void*);
	void *arg;
};

void initThreadPool(struct ThreadPool *thread_pool, int thread_count);

#endif
