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
struct st_TASK_QUEUE {
	Task* HEAD;
	void (*add)(void (*execute)(int), int data);
	void (*executeNext)();
	int elementCounter;
};

void TASK_QUEUE_ADD(void (*execute)(int), int data);
void TASK_QUEUE_EXECUTE_NEXT();

static struct st_TASK_QUEUE taskQueue = 
{
	NULL,        		// HEAD = NULL => empty queue
	TASK_QUEUE_ADD,
	TASK_QUEUE_EXECUTE_NEXT,
	0            		// clear element coutner
};

/******************************************
 * uTimer queue
 */
struct st_U_TIMER_QUEUE {
	Task* HEAD;
	void (*add)(int delay, void (*execute)(int), int data);
	void (*tick)();
	int elementCounter;
};

void U_TIMER_QUEUE_ADD(int delay, void (*execute)(int), int data);
void U_TIMER_QUEUE_TICK();

static struct st_U_TIMER_QUEUE uTimerQueue = 
{
	NULL,        		// HEAD = NULL => empty queue
	U_TIMER_QUEUE_ADD,
	U_TIMER_QUEUE_TICK,
	0            		// clear element coutner
};

/******************************************
 * mTimer queue
 */
struct st_M_TIMER_QUEUE {
	Task* HEAD;
	void (*add)(int delay, void (*execute)(int), int data);
	void (*tick)();
	int elementCounter;
};

void M_TIMER_QUEUE_ADD(int delay, void (*execute)(int), int data);
void M_TIMER_QUEUE_TICK();
/*
static struct st_M_TIMER_QUEUE mTimerQueue = 
{
	NULL,        		// HEAD = NULL => empty queue
	M_TIMER_QUEUE_ADD,
	M_TIMER_QUEUE_TICK,
	0            		// clear element coutner
};
*/

#endif