# SCUL - Simple C Utility Library
An extensive and free (as in freedom) library of utility APIs for the C programming language.
### Included utilities (subject to updates):
#### Data Structures:
- [Linked list](#linked-list)
- [Queue](#queue)

### Linked List
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
 * void* removeData(struct LinkedList* linked_list, int index) 
 * (keep in mind that this is a linked list of void*, meaning that removal
 * of a linked list node != freeing the void*, this is why the removeData() function
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

Compilation was tested with GCC  version 9.4.0 on Ubuntu GNU/Linux.
Please report any bugs and feel free to contribute features & fixes. 
