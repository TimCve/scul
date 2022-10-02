# SCUL - Simple C Utility Library
An extensive and free (as in freedom) library of utility APIs for the C programming language.
### Included utilities (subject to updates):
#### Data Structures:
- [Linked list](#linked-list)
- [Queue](#queue)
#### System Architecture:
- [Thread pool](#thread-pool)

### Linked list
Compile `DataStructures/LinkedList/*.c` into your binary.
```C
/* USAGE INSTRUCTIONS 
 * #include "DataStructures/LinkedList/LinkedList.h" (is assumed) */

/* INITIALIZATION
 * void initLinkedList(struct LinkedList* linked_list) */
struct LinkedList linked_list;
initLinkedList(&linked_list);

/* ELEMENT INSERTION
 * void insertData(struct LinkedList* linked_list, int index, void* data) */
int* data_to_insert = malloc(sizeof(int));
*data_to_insert = 5;
linked_list.insert(&linked_list, 0, data_to_insert);

/* ELEMENT RETRIEVAL
 * void* retrieveData(struct LinkedList* linked_list, int index) */
int retrieved_data = *((int*) linked_list.retrieve(&linked_list, 0));

/* ELEMENT REMOVAL
 * void* removeNode(struct LinkedList* linked_list, int index) 
 * (keep in mind that this is a linked list of void*, meaning that removal
 * of a linked list node != freeing the void*, this is why the removeNode function
 * returns the void pointer from the node that was removed.) */
free((int*) linked_list.remove(&linked_list, 0));
```
### Queue
Compile `DataStructures/LinkedList/*.c DataStructures/Queue/*.c` into your binary.
```C
/* USAGE INSTRUCTIONS 
 * #include "DataStructures/Queue/Queue.h" (is assumed) */

/* INITIALIZATION
 * void initQueue(struct LinkedList* queue) */
struct Queue queue;
initQueue(&queue);

/* ELEMENT ENQUEUE (add element to end of queue)
 * void enqueue(struct Queue* queue, void* data) */
int* data_to_enqueue = malloc(sizeof(int));
*data_to_enqueue = 5;
queue.enqueue(&queue, data_to_enqueue);

/* ELEMENT PEEK (return element at start of queue)
 * void* peek(struct Queue* queue) */
int peeked_data = *((int*) queue.peek(&queue));

/* ELEMENT DEQUEUE (remove element at start of queue)
 * void* dequeue(struct Queue* queue) 
 * Why the call to free()? See the Linked List section. */
free((int*) queue.dequeue(&queue));
```
### Thread pool
Compile `DataStructures/LinkedList/*.c DataStructures/Queue/*.c SysArchitecture/ThreadPool/*.c` into your binary.
```C
/* USAGE INSTRUCTIONS
 * #include "SysArchitecture/ThreadPool/ThreadPool.h" (is assumed) */

/* INITIALIZATION
 * void initThreadPool(struct ThreadPool* thread_pool, int thread_count) 
 * second argument is the number of threads in the thread pool */
struct ThreadPool thread_pool;
initThreadPool(&thread_pool, 6);

/* DEFINE TASK FUNCTION 
 * Example: void task_func(void* arg) */

/* ADD TASK TO THREAD POOL
 * int threadPoolAddTask(struct ThreadPool* thread_pool, void (*func)(void*), void* arg) 
 * returns a 0 if everything went well, 1 if the thread pool is inactive */
thread_pool.add(&thread_pool, task_func, (void*) task_arg);

/* GRACEFULLY TERMINATE THREAD POOL (waits until all tasks are finished before freeing the thread pool memory
 * void threadPoolGracefulHalt(struct ThreadPool* thread_pool) */
thread_pool.gracefulHalt(&thread_pool);
```

Compilation was tested with GCC  version 9.4.0 on Ubuntu GNU/Linux.
Please report any bugs and feel free to contribute features & fixes. 
