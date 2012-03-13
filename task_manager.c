#include <stdlib.h>
#include <stdio.h>

#include "task_manager.h"

void TASK_ADD(void (*execute)(int), int data) {
	
	Task* task_p;
	
	//put into queue
	if(taskQueue.HEAD == NULL) { // => queue empty

		/* create new queue element */
		task_p = (Task*)malloc(sizeof(Task));
		task_p->execute = execute;
		task_p->data = data;
		task_p->next_p = NULL;
	
		taskQueue.HEAD = task_p;
	}
	else {  // => queue not empty
		
		// find end of queue
		task_p = taskQueue.HEAD;
		while(task_p->next_p != NULL)
			task_p = task_p->next_p;
		
		task_p->next_p = (Task*)malloc(sizeof(Task));
		task_p = task_p->next_p;
		task_p->execute = execute;
		task_p->data = data;
		task_p->next_p = NULL;
	}

	printf("TASK added\n");
}

void TASK_EXECUTE_NEXT() {
	if(taskQueue.HEAD != NULL) {
		Task* task = taskQueue.HEAD;
		taskQueue.HEAD = taskQueue.HEAD->next_p;
	}
}