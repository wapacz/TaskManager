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
void TASK_QUEUE_ADD(void (*execute)(int), int data) {
	
	Task *task_p;
	
	printf("Adding TASK ");
	
	//put into queue
	if(taskQueue.HEAD == NULL) { // => queue empty

		printf("(queue empty)\n");

		/* create new queue element */
		taskQueue.HEAD = CreateTask(execute, data);
	}
	else {  // => queue not empty

		printf("(queue not empty)\n");
	
		// find end of queue
		task_p = taskQueue.HEAD;
		while(task_p->next_p != NULL) {
			task_p = task_p->next_p;
		}

		task_p->next_p = CreateTask(execute, data);
	}
	
	// increase element counter
	taskQueue.elementCounter++;
}

void TASK_QUEUE_EXECUTE_NEXT() {

	if(taskQueue.HEAD != NULL) {
	
		printf("Executing TASK: ");
	
		// move HEAD to next elemenet and get first one
		Task* task_p = taskQueue.HEAD;
		taskQueue.HEAD = taskQueue.HEAD->next_p;
		
		// decrease element counter
		taskQueue.elementCounter--;		
		
		// execute the task
		task_p->execute(task_p->data);
		
		// clean up
		free(task_p);
	}
}


/******************************************
 * uTimer queue
 */
void U_TIMER_QUEUE_ADD(int delay, void (*execute)(int), int data) {
	
	int sum_delay;
	Task *task_p, *curr_task_p, *prev_task_p;
	
	printf("Adding delayed TASK ");
	
	//put into queue
	if(uTimerQueue.HEAD == NULL) { // => queue empty

		// start timer
		// TIMER1.start();
	
		printf("(queue empty)\n");
		printf(" = %d\n", uTimerQueue.HEAD);
		/* create new queue element */
		uTimerQueue.HEAD = CreateDelayedTask(delay, execute, data);
		printf(" = %d\n", uTimerQueue.HEAD);
		
	}
	else {  // => queue not empty

		printf("(queue not empty)\n");
	
		task_p = CreateDelayedTask(delay, execute, data);
	
		// find place where to put task
		prev_task_p = NULL;
		curr_task_p = uTimerQueue.HEAD;
		sum_delay = curr_task_p->delay;
		while(curr_task_p != NULL && sum_delay < delay) {
			printf("*");
			prev_task_p = curr_task_p;
			curr_task_p = curr_task_p->next_p;
			sum_delay += curr_task_p->delay;
		}
		
		if(prev_task_p == NULL) { // => begining of timer queue
			printf("begining of timer queue\n");
			task_p->next_p = uTimerQueue.HEAD;
			uTimerQueue.HEAD = task_p;
		} 
		else { // => not begining of timer queue
			printf("not begining of timer queue\n");
			prev_task_p->next_p = task_p;
			task_p->next_p = curr_task_p;
		}

		if(curr_task_p != NULL) { // => not end of queue
			// update delay counter
			curr_task_p->delay = curr_task_p->delay - task_p->delay;
		}
	}
	
	// increase element counter
	uTimerQueue.elementCounter++;
}

void U_TIMER_QUEUE_TICK() {

}

 
/******************************************
 * mTimer queue
 */
void M_TIMER_QUEUE_ADD(int delay, void (*execute)(int), int data) {

}

void M_TIMER_QUEUE_TICK() {

}
