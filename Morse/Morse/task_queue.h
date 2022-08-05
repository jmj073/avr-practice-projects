/*
 * task_queue.h
 *
 * Created: 2022-06-18 19:36:19
 *  Author: JMJ
 */ 


#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <stdint.h>

#define TASK_QUEUE_SIZE 31
// ASSERT(TASK_QUEUE_CAPACITY <= 256)
#define TASK_QUEUE_CAPACITY (TASK_QUEUE_SIZE + 1)


struct task {
	void (*func)(uint16_t arg);
	uint16_t arg;
};

// if task_queue is full: return 0
uint8_t TASKQ_push(struct task task);
uint8_t TASKQ_push_atomic(struct task task);

struct task TASKQ_pop();
struct task TASKQ_pop_atomic();

uint8_t TASKQ_empty();
uint8_t TASKQ_full();

#endif /* TASK_QUEUE_H_ */