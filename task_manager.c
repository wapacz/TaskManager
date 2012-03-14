#include <stdlib.h>
#include <stdio.h>

#include "task_manager.h"

Task* CreateTask(void (*execute)(int), int data) {
	Task* task_p = (Task*)malloc(sizeof(Task));
	task_p->execute = execute;
	task_p->data = data;
	task_p->delay = 0;
	task_p->next_p = NULL;
	return task_p;
}

Task* CreateDelayedTask(int delay, void (*execute)(int), int data) {
	Task* task_p = (Task*)malloc(sizeof(Task));
	task_p->execute = execute;
	task_p->data = data;
	task_p->delay = delay;
	task_p->next_p = NULL;
	return task_p;
}

/******************************************
 * Normal task queue
 */
TaskQueue TaskQueue_Create() {
	TaskQueue queue = {NULL, 0};
	return queue;
}

void TaskQueue_Add(TaskQueue* this, void (*execute)(int), int data) {
	
	Task *task_p;
	
	printf("Adding TASK ");
	
	//put into queue
	if(this->HEAD == NULL) { // => queue empty

		printf("(queue empty)\n");

		/* create new queue element */
		this->HEAD = CreateTask(execute, data);
	}
	else {  // => queue not empty

		printf("(queue not empty)\n");
	
		// find end of queue
		task_p = this->HEAD;
		while(task_p->next_p != NULL) {
			task_p = task_p->next_p;
		}

		task_p->next_p = CreateTask(execute, data);
	}
	
	// increase element counter
	this->elementCounter++;
}

void TaskQueue_ExecuteNext(TaskQueue* this) {

	if(this->HEAD != NULL) {
	
		printf("Executing TASK: ");
	
		// move HEAD to next elemenet and get first one
		Task* task_p = this->HEAD;
		this->HEAD = this->HEAD->next_p;
		
		// decrease element counter
		this->elementCounter--;		
		
		// execute the task
		task_p->execute(task_p->data);
		
		// clean up
		free(task_p);
	}
}


/******************************************
 * Timer queue
 */
TimerQueue TimerQueue_Create() {
	TimerQueue queue = {NULL, 0};
	return queue;
}

void TimerQueue_Add(TimerQueue* this, int delay, void (*execute)(int), int data) {
	
	int sum_delay = 0;
	Task *new_task_p, *next_task_p, *prev_task_p;
	
	printf("Adding delayed TASK\n");
	
	if(this->HEAD == NULL) { // queue is empty
		printf(" *** START TIMER ***\n");
	}
	
	// find place where to insert task
	prev_task_p = NULL;
	next_task_p = this->HEAD;
	
	while(next_task_p != NULL) {
		
		// sumarize delay
		sum_delay += next_task_p->delay;
		
		if(sum_delay > delay) {
			sum_delay -= next_task_p->delay;
			break;
		}
		
		// set prev pointer and ...
		prev_task_p = next_task_p;
		
		// ... move poiner to next element
		next_task_p = next_task_p->next_p;
	}
	
	// prev_task_p - points to element before new_task_p
	// next_task_p - points to element after new_task_p
	
	new_task_p = CreateDelayedTask(delay - sum_delay, execute, data);
	
	if(prev_task_p != NULL) { 
		prev_task_p->next_p = new_task_p;
	}
	else {
		this->HEAD = new_task_p;
	}
	
	if(next_task_p != NULL) { 
		new_task_p->next_p = next_task_p;
		next_task_p->delay -= new_task_p->delay;
	}
	
	// increase element counter
	this->elementCounter++;
}

void TimerQueue_Tick(TimerQueue* this, TaskQueue* taskQueue) {
	if(this->HEAD != NULL) {
		this->HEAD->delay--;
		if(this->HEAD->delay == 0) { // time expired
			TaskQueue_Add(taskQueue, this->HEAD->execute, this->HEAD->data);
			this->HEAD = this->HEAD->next_p; // move HEAD to next element, even it's NULL
		}
	}
	else {
		printf(" *** STOP TIMER ****\n");
	}
}

