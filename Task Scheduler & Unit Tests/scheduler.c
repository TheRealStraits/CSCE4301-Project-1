#include "C:\Users\pc\Desktop\tt\tt\MDK-ARM\functinQ.h"

void QueTask(void (*function)(void), int sad);
void Dispatch();
void Init();
void ReRunmMe(int ms); 
struct Queue readyQ;
struct Queue DelayQ;
void   Qdelay(struct Task);






void Init(){
	readyQ.first= 0;
	readyQ.last = 0;
	DelayQ.first = 0;
	DelayQ.last = 0;
	
}

void QueTask(void (*function)(void), int prio){
	struct Task temp;
	temp.realPriority = prio;
	temp.relativePriority = prio;
	temp.func = function;
	readyQ.p[readyQ.first++] = temp;
	readyQ.last++;
}

void Dispatch(){
	int maxprio = 0;
	int current;
	int execute = 0;
	for(int i = 0;  i < readyQ.last; i++){
		current = readyQ.p[i].relativePriority;
		if( current> maxprio){
				maxprio = current;
				execute = i;
		}
		
	}
	readyQ.p[execute].relativePriority = -1;
	readyQ.first = execute;
	readyQ.p[execute].func();

}

void ReRunMe(int ms){
	readyQ.p[readyQ.first].relativePriority = readyQ.p[readyQ.first].realPriority;
	readyQ.p[readyQ.first].delay = ms;
	
	DelayQ.p[DelayQ.first++] = readyQ.p[readyQ.first];
	DelayQ.last++;
}

void Qdelay(struct Task delayed){
	int i;
	for  (i = 0; i<DelayQ.last;i++){
		if (DelayQ.p[i].delay==0){
			QueTask(DelayQ.p[i].func, DelayQ.p[i].realPriority);
			
			
		}
		
		
	}
	
	
	
	
}


















