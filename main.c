#include <stdio.h>

#include "task_manager.h"

void task1_Action1(int data) {
	printf("task1_Action1 [%d]\n", data);
}

void task2_Action1(int data) {
	printf("task2_Action1 [%d]\n", data);
}

int main(void) {
	int i;
	
	//uTimerQueue.add(100, task1_Action1, 1);
	//uTimerQueue.add(200, task1_Action1, 1);
	//uTimerQueue.add(150, task1_Action1, 1);
	//printf(" = %d\n", uTimerQueue.HEAD);
		
	
	
	//task1.execute(1);
	
	taskQueue.add(task1_Action1, 1);
	taskQueue.add(task1_Action1, 2);
	taskQueue.add(task1_Action1, 3);
	taskQueue.add(task1_Action1, 4);
	taskQueue.add(task2_Action1, 1);
	//uTimerQueue.add(100, task_Action1, 1);
	//mTimerQueue.add(100, task_Action1, 1);
	
	Task* task_p = taskQueue.HEAD;
	while(task_p != NULL) {
		printf(" - %d\n", task_p->delay);
		task_p = task_p->next_p;
	}
	
	i=100;
	while(i--)
		taskQueue.executeNext();
	
	taskQueue.add(task1_Action1, 6);
	taskQueue.add(task1_Action1, 7);
	taskQueue.add(task2_Action1, 2);
	taskQueue.add(task1_Action1, 9);
	taskQueue.add(task1_Action1, 10);
		
	i=100;
	while(i--)
		taskQueue.executeNext();
	
	
	return 0;
}