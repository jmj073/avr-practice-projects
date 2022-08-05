/*
 * task_queue.c
 *
 * Created: 2022-06-18 19:36:32
 *  Author: JMJ
 */ 

#include "task_queue.h"
#include <util/atomic.h>

_Static_assert(TASK_QUEUE_CAPACITY <= 256,
"TASK_QUEUE_CAPACITY <= 256");

#define next_step(n) (((n) + 1) % TASK_QUEUE_CAPACITY)

static struct task queue[TASK_QUEUE_CAPACITY];
static uint8_t TASKQ_PRIOR, TASKQ_NEXT;

static inline uint8_t __TASKQ_empty() {
	return TASKQ_PRIOR == TASKQ_NEXT;
}

static inline uint8_t __TASKQ_full() {
	return TASKQ_PRIOR == (TASKQ_NEXT + 1) % TASK_QUEUE_CAPACITY;
}

uint8_t TASKQ_empty() {
	return __TASKQ_empty();
}

uint8_t TASKQ_full() {
	return __TASKQ_full();
}

uint8_t TASKQ_push(struct task task)
{
	if (__TASKQ_full()) return 0;
	queue[TASKQ_NEXT = next_step(TASKQ_NEXT)] = task;
	return 1;
}

uint8_t TASKQ_push_atomic(struct task task)
{
	uint8_t ret;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
		ret = TASKQ_push(task);
	return ret;
}

struct task TASKQ_pop()
{
	if (__TASKQ_empty()) return (struct task) { 0, 0 };
	return queue[TASKQ_PRIOR = next_step(TASKQ_PRIOR)];
}

struct task TASKQ_pop_atomic()
{
	struct task ret;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
		ret = TASKQ_pop();
	return ret;
}