#include <stdio.h>

#include "task_manager.h"



void task1_Action1(int data) {
	printf("Hello world!");
}

int main(void) {
	
	//task1.execute(1);
	
	taskQueue.add(task1_Action1, 1);
	//uTimerQueue.add(100, task_Action1, 1);
	//mTimerQueue.add(100, task_Action1, 1);
	
	return 0;
}