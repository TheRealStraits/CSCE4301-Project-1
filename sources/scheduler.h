
extern struct Task{
		int realPriority ;
		int relativePriority;
		int delay;
		void (*func)();
} TaskA, TaskB;
	
	



extern struct Queue{
	struct Task p [10];
	int first;
	int last;
}readyQ, DelayQ;


void extern QueTask(void (*function)(void), int priority);
void extern Dispatch();
void extern Init();
void extern ReRunmMe(int ms);
void extern Qdelay(struct Task);

