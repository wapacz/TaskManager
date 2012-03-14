#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

typedef struct st_Task {
	void (*execute) (int data);
	int data;
	int delay;
	struct st_Task* next_p;
} Task;

Task* CreateTask(void (*execute)(int), int data);
Task* CreateDelayedTask(int delay, void (*execute)(int), int data);

/******************************************
 * Normal task queue
 */
typedef struct st_TASK_QUEUE {
	Task* HEAD;
	int elementCounter;
} TaskQueue;
TaskQueue TaskQueue_Create();
void TaskQueue_Add(TaskQueue* this, void (*execute)(int), int data);
void TaskQueue_ExecuteNext(TaskQueue* this);


/******************************************
 * Timer queue
 */
typedef struct st_TIMER_QUEUE {
	Task* HEAD;
	int elementCounter;
} TimerQueue;
TimerQueue TimerQueue_Create();
void TimerQueue_Add(TimerQueue* this, int delay, void (*execute)(int), int data);
void TimerQueue_Tick(TimerQueue* this);

#endif