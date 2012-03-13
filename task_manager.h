#ifndef _TASK_MANAGER_
#define _TASK_MANAGER_

typedef struct st_Task {
	void (*execute) (int data);
	int data;
	struct st_Task* next_p;
} Task;

struct st_TASK_H {
	Task* HEAD;
	void (*add)(void (*execute)(int), int data);
	void (*executeNext)();
};

void TASK_ADD(void (*execute)(int), int data);
void TASK_EXECUTE_NEXT();

static struct st_TASK_H taskQueue = 
	{
		NULL,        // HEAD = NULL => empty queue
		TASK_ADD,
		TASK_EXECUTE_NEXT
	};

#endif