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
	
	printf("Adding delayed TASK ");
		
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
		
		// set prev pointer nd ...
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
	
	if(next_task_p != NULL) { 
		new_task_p->next_p = next_task_p;
	}
	else { // next_task_p = NULL => begining of queue, HEAD must me updated
		this->HEAD = new_task_p;
	}
	
	 // put element in the midlle of queue
	next_task_p->delay -= new_task_p->delay;
/*




		
		//--------------------------
		
		while(next_task_p != NULL) {
			
			
			// sumarize delay value
			sum_delay = sum_delay + prev_task_p->delay; // ?
			
			// check if delay greaer then new task delay
			if(sum_delay > delay) {
				sum_delay = sum_delay - prev_task_p->delay;
				break;
			}
		}

		printf("sum_delay = %d\n", sum_delay);
		
		task_p = CreateDelayedTask(delay - sum_delay, execute, data);
	
		if(prev_task_p == NULL) { // => begining of timer queue
			printf("begining of timer queue");
			task_p->next_p = this->HEAD;
			this->HEAD = task_p;
		} 
		else { // => not begining of timer queue
			printf("not begining of timer queue");
			prev_task_p->next_p = task_p;
			task_p->next_p = next_task_p;
		}

		if(next_task_p != NULL) { // => not end of queue
			// update delay counter on the next element after
			next_task_p->delay = next_task_p->delay - task_p->delay;
		}
	}
	*/
	printf("\n");
		
	// increase element counter
	this->elementCounter++;
}

void TimerQueue_Tick(TimerQueue* this) {

}

