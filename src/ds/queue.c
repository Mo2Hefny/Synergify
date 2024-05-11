#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

/**
 * create_queue - Creates a new empty process information queue
 *
 * @return A pointer to the newly created process information queue, or NULL if memory allocation fails
 */
queue_t *create_queue()
{
	queue_t *my_queue = malloc(sizeof(queue_t));
	if (!my_queue)
	{
		exit(-1);
	}

	my_queue->head = NULL;
	my_queue->tail = NULL;
	my_queue->size = 0;

	return my_queue;
}

/**
 * enqueue - Enqueues a process into the queue
 * @param my_queue: A pointer to the process information queue
 * @param data: A pointer to the process information to be enqueued
 *
 * @return true if the process is enqueued successfully, otherwise false
 */
bool enqueue(queue_t *my_queue, void *data)
{
	queue_node_t *node = malloc(sizeof(queue_node_t));
	if (!node)
	{
		return false;
	}

	node->data = data;
	node->next = NULL;

	if (my_queue->tail == NULL)
	{
		my_queue->head = node;
	}
	else
		my_queue->tail->next = node;
	my_queue->tail = node;
	my_queue->size += 1;

	return true;
}

/**
 * dequeue - Dequeues a process from the queue
 * @param my_queue: A pointer to the process information queue
 *
 * @return A pointer to the dequeued process information, or NULL if the queue is empty
 */
void *dequeue(queue_t *my_queue)
{
	if (!my_queue->head)
		return NULL;
	void *data = my_queue->head->data;
	queue_node_t *next = my_queue->head->next;

	free(my_queue->head);
	my_queue->head = next;
	my_queue->size -= 1;
	if (my_queue->size == 0)
		my_queue->tail = NULL;
	return data;
}

/**
 * front - Retrieves the process at the front of the queue without dequeuing it
 * @param my_queue: A pointer to the process information queue
 *
 * @return A pointer to the process information at the front of the queue, or NULL if the queue is empty
 */
const void *front(queue_t *my_queue)
{
	if (!my_queue->head)
		return NULL;

	return (const void *)(my_queue->head->data);
}

/**
 * is_queue_empty - Checks if the queue is empty
 * @param my_queue: A pointer to the process information queue
 *
 * @return true if the queue is empty, otherwise false
 */
bool is_queue_empty(queue_t *my_queue)
{
	return my_queue->size == 0;
}

/**
 * queue_copy - copy my_queue to a dist queue
 * @param my_queue: the queue to be copied.
 * @param dist: the queue on which I copy the nodes.
*/
void queue_copy(queue_t *my_queue, queue_t *dist)
{
	if (!my_queue->head) return;

	queue_node_t *temp = my_queue->head;
	while (temp)
	{
		enqueue(dist, temp->data);
		temp = temp->next;
	}
}

/**
 * queue_free - Frees all memory allocated for the queue elements
 * @param my_queue: A pointer to the queue
 * @param deleteData: Determine if the data is freed or not
 *
 * Description: This function iteratively dequeues each element from the queue and frees its memory.
 */
void queue_free(queue_t *my_queue, bool deleteData)
{
	if (!my_queue)
		return;
	void *data = dequeue(my_queue);
	while (data)
	{
		if (deleteData)
			free(data);
		data = dequeue(my_queue);
	}
}
