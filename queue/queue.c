#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

typedef struct Queue {
    unsigned int length;
    unsigned int capacity;
    int *storage;
} Queue;

/*
    Creates a queue by allocating the appropriate amount of memory for an
    instance of the Queue struct, and initializes all of the fields of the
    struct. Also allocates memory for the queue's storage structure. 
*/
Queue *createQueue(unsigned capacity)
{
    Queue *q = malloc(sizeof(Queue));
    q->length = 0;
    q->capacity = capacity;
    q->storage = malloc(capacity * sizeof(int));
    return q;
}

/*
    Adds the given item to the end of the queue. If the queue does
    not have room, expand the queue's available storage so that it 
    does have room for the additional item.
*/
void enqueue(Queue *q, int item)
{
    if (q->length == q->capacity) {
        q->capacity += 1;
        int new_size = q->capacity * sizeof(int);
        q->storage = resize_memory(q->storage, new_size);
    }
    q->storage[q->length++] = item;
}

/*
    Removes the item at the front of the queue and returns it. 
    If the queue is empty, this function should return -1.
*/
int dequeue(Queue *q)
{
    if (q->length <= 0) {
        return -1;
    } else {
        int item = q->storage[0];
        for (unsigned int i = 0; i<(q->length-1); i++){
            q->storage[i] = q->storage[i+1];
        }
        q->length -= 1;
        return item;
    }
}

/*
    Frees the memory used to hold the queue instance and its
    associated storage. 
*/
void destroyQueue(Queue *q)
{
    if (q->storage != NULL) {
        free(q->storage);
    }
    if (q != NULL) {
        free(q);
    }
}


#ifndef TESTING
int main(void)
{
    Queue *q = createQueue(4);

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);

    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));

    destroyQueue(q);

    return 0;
}
#endif