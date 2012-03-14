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
	
	TaskQueue taskQ1 = TaskQueue_Create();
	TimerQueue uTimerQ = TimerQueue_Create();
	TimerQueue mTimerQ = TimerQueue_Create();
	
	TimerQueue_Add(&uTimerQ, 100, task1_Action1, 1);
	TimerQueue_Add(&uTimerQ, 200, task1_Action1, 2);
	TimerQueue_Add(&uTimerQ, 300, task1_Action1, 3);
	TimerQueue_Add(&uTimerQ, 250, task2_Action1, 4);
	TimerQueue_Add(&uTimerQ, 213, task2_Action1, 5);
	TimerQueue_Add(&uTimerQ, 13,  task2_Action1, 6);

	TimerQueue_Add(&uTimerQ, 1000, task2_Action1, 7);

	Task* task_p = uTimerQ.HEAD;
	while(task_p != NULL) {
		printf(" - %d, (data=%d)\n", task_p->delay, task_p->data);
		task_p = task_p->next_p;
	}
	
	i=1001;
	while(i--) {
		TimerQueue_Tick(&uTimerQ, &taskQ1);
	}

	i=100;
	while(i--)
		TaskQueue_ExecuteNext(&taskQ1);

	
	/*
	TaskQueue_Add(&taskQ1, task1_Action1, 1);
	TaskQueue_Add(&taskQ1, task1_Action1, 2);
	TaskQueue_Add(&taskQ1, task1_Action1, 3);
	TaskQueue_Add(&taskQ1, task1_Action1, 4);
	TaskQueue_Add(&taskQ1, task2_Action1, 1);
	
	
	
	i=100;
	while(i--)
		TaskQueue_ExecuteNext(&taskQ1);
	
	TaskQueue_Add(&taskQ1, task1_Action1, 6);
	TaskQueue_Add(&taskQ1, task1_Action1, 7);
	TaskQueue_Add(&taskQ1, task2_Action1, 2);
	TaskQueue_Add(&taskQ1, task1_Action1, 9);
	TaskQueue_Add(&taskQ1, task1_Action1, 10);
		
	i=100;
	while(i--)
		TaskQueue_ExecuteNext(&taskQ1);
	
	*/
	return 0;
}