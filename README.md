# CSCE4301 Project 1

This project is that of a task scheduler that operates as an RTOS on the STM32. The aim of the project is to be able to queue and dispatch tasks using the implemented Task Scheduler. The designed scheduler uses a combination of struct datatypes and C functions in order to accomplish its objective of queuing different tasks that perform different functionalities on the STM32 Microcontroller. 

## Task Scheduler

### How does it work?

The different tasks are initialsed at the beginning of the project with all the necessary implementations. The user can then use then start queuing the different tasks and include their priority along with them using the ***QueTask()*** function. Once the tasks have been queued accordingly. The ***Dispatch()*** function can be run in order to start popping tasks from the queue and start the program. There are other functions that can be used in the API such as the ***ReRunMe()*** & ***Init()*** functions which you can see the description for in the functions section. 

#### The Ready Queue & Delay Queue

The Ready Queue and Delay Queue are both arrays of structs of strcuts. These structs contain task structs that have a pointer that points to the task functions as well as the priority given to the tasks. Another element that is stored along with these tasks is their relative priority which is essentially used in order to figure out which task has the highest (thus being the one that is run first). In order to remove/pop tasks from the queue, their realtive priorities are set to `-1`. We also have a variable that stores the delay of tasks. Finally, when it comes to the outer queue struct, two integer variables store the index of the `first` and `last` elements in the queue, therefore making it circular.

- Task Struct : `extern struct Task{ int realPriority ;	int relativePriority;	int delay;	void (*func)(); }; `
- Queue Struct : `extern struct Queue{ struct Task p [10];	int first;	int last; }; `  - _The queue can only store around 10 tasks_

### Functions

_All of the different API functions are described here. This section details how the functions work, what they accept as arguments and how to use them._

#### `Init()`
The system is initialized by a single call to this function. This function creates and initializes all needed data structures. This function essentially intialises all the different queues that are goin to be utilised as well as the different tasks that are going to be used. In code, the function just sets all the queue first & last values to 0.

#### `QueTask(taskPointer, taskPriority)`
This function inserts the different tasks into the ready queue (array of structs containing the task and its priority). The function takes in as arguments the task pointer as well as the priority given to this task. Both arguments are used in order to add the task into the ready queue (array). 

A temporary struct is set up at beginning of the call where all of the task information is stored including the prioirity given to the task. That temporary struct is then stored into the Ready Queue array. Following this procedure, the `first` and `last` integers are updated to indicate where the queue starts and ends.

#### `ReRunMe(tickDelay)`

This function is used in order to re-run a task that has been recently dispatched. It can be run by the task itself. It takes in as arguments, only the tick delay. This essentially dictates how long the task has to wait before it can be re-run. This is why we have another array of structs that stores the tasks that currently have delay. These tasks are not queued in the Ready Queue until their delays equal 0. Only then are they queued to the ready queue using the `QueTask()` function. The delay value of the tasks inside the Delay Queue is decremented every SysTick.

#### `Dispatch()`

The Dispatch function goes through the array of structs and calculates the relative priority of each task and compares it to the `maxprio` value which stores the highest priority and `execute` stores the index of the task to which that priority belongs. The for loop of the dispatch goes as follows, for more details :

```
int maxprio = 0;
int current;
int execute = 0;
for(int i = 0;  i < readyQ.last; i++)
{
	current = readyQ.p[i].relativePriority;
	if( current> maxprio)
	{
			maxprio = current;
			execute = i;
	}
}
 ```
 
## Unit Tests

_In order to make sure that the task scheduler is working properly, we needed to design a few unit testing scenarios. These testing units, use different color LEDs which are operated by different tasks. This enables us to make sure that each API function is working properly. Unfortunately, we were not able to make sure whether or not the API is functional from within an interrupt handler due to some technical difficulties with the UART._

In order to discover how the different tasks were being dispatched we had to be able to differentiate between them. We have done so by assigning different tasks, different LED colour toggles. We then proceeded to make sure that each API function is working. 

We started out by looking at the basics, which were the queuing of tasks as well as the dispatching of tasks. We initialised two tasks that toggled two different coloured LEDs. Having one run for a smaller period than the other. 

```
void task2(void)
{
	int i =0;
	for( i = 0; i<10; i++)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		HAL_Delay(55);
	}
}
```

Next we proceeded to test the priority queuing by giving the tasks different priorities. As mentioned before, the `Dispatch()` function executes tasks based on the one with the highest priority. Once the function completes all of the tasks in the queue array, it moves back to the begginning of the array and restarts. We were also able to test and see if task queuing can be nested, which essentially means check whehter or not we can queue a task from within another task, like so :

```
void task4(void) 
{
	for(int i =0; i = 0; i<6; i++)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		HAL_Delay(50);
	}
	QueTask(task1,5);
	QueTask(task7,5);
}
```

Next, we wanted to test how the `ReRunMe()` function operates properly. We have therefore inputted the function inside the tasks we had and then had them queue with different delays. Finally, we wanted to test the extents of this task scheduler and therefore have implemented all of the API functions at the same time (which is what is provided in the repository folder title "Task Scheduler & Test Units"). Again, Unfortunately, we were not able to make sure whether or not the API is functional from within an interrupt handler due to some technical difficulties with the UART.

## Sample Applications

_This section describes the different real life implementations that have been used in order to test the task scheduler in different scenarios._

### Temprature Sensor

This temperature sensor was implemented using the RS3231 RTC module. The implementation starts by setting the appropriate registers inside the module and then starts reading the input (`Task #1`) with a 30 second delay. Once the temprature passes a certain threshhold, the temprature triggers an alarm in the form of a flashing LED (`Task #3`). The reading taken by the temprature is evaluated (`Task #2`) every 30 seconds after the reading has been taken. The setting of the Threshold using the UART feature has not been implemented due to some technical difficulties that have been encoutered with the USB to TTL module.

### Parking Sensor

This parking sensor was implemented using the HC-SR04 Ultrasonic sensor. The implementation starts by reading the echo pin of the sensor and counting how long it has been in the UP state (`Task #1`). This value indicates how long for the ultrasonic frequency to be transmitted and received. Using this time we can calculate the distance (`Task #2`) between the Ultrasonic sensor and the object in front of it. This distance is evaluated every 0.5 seconds. At a certain distance, a buzzer starts beeping at a certain frequency (`Task #3`). That frequency increase the closer an object is from the sensor. The ultrasonic sensor was implemented using polling methods since the timer interrupts were not functioning properly on our STM32. 

## How to Run the Scheduler and the Implementations

Include the header and C file inside the project folder (make sure to remember the path in which the headers are stored and make sure to change the header file path inside the header file and the main project file). Make sure to initialise the appropriate GPIO ports and communication ports necessary for running the appropiate applications. Then you are free to use the API functions.
