# CSCE4301 Project 1

This project is that of a task scheduler that operates as an RTOS on the STM32. The aim of the project is to be able to queue and dispatch tasks using the implemented Task Scheduler. The designed scheduler uses a combination of struct datatypes and C functions in order to accomplish its objective of queuing different tasks that perform different functionalities on the STM32 Microcontroller. 

## Task Scheduler

### How does it work?

The different tasks are initialsed at the beginning of the project with all the necessary implementations. The user can then use then start queuing the different tasks and include their priority along with them using the ***QueTask()*** function. Once the tasks have been queued accordingly. The ***Dispatch()*** function can be run in order to start popping tasks from the queue and start the program. There are other functions that can be used in the API such as the ***ReRunMe()*** & ***Init()*** functions which you can see the description for in the functions section. 

### Functions

_All of the different API functions are described here. This section details how the functions work, what they accept as arguments and how to use them._

#### `Init()`
The system is initialized by a single call to this function. This function creates and initializes all needed data structures. This function essentially intialises all the different queues that are goin to be utilised as well as the different tasks that are going to be used.

#### `QueTask(taskPointer, taskPriority)`
This function inserts the different tasks into the ready queue (array of structs containing the task and its priority). The function takes in as arguments the task pointer as well as the priority given to this task. Both arguments are used in order to add the task into the ready queue (array). 

#### `ReRunMe(tickDelay)`


#### `Dispatch()`


## Scheduler Implementations

_This section describes the different real life implementations that have been used in order to test the task scheduler in different scenarios._

### Temprature Sensor

This temperature sensor was implemented using the RS3231 RTC module. The implementation starts by setting the appropriate registers inside the module and then starts reading the input (`Task #1`) with a 30 second delay. Once the temprature passes a certain threshhold, the temprature triggers an alarm in the form of a flashing LED (`Task #3`). The reading taken by the temprature is evaluated (`Task #2`) every 30 seconds after the reading has been taken. The setting of the Threshold using the UART feature has not been implemented due to some technical difficulties that have been encoutered with the USB to TTL module.

### Parking Sensor

This parking sensor was implemented using the HC-SR04 Ultrasonic sensor. The implementation starts by reading the echo pin of the sensor and counting how long it has been in the UP state (`Task #1`). This value indicates how long for the ultrasonic frequency to be transmitted and received. Using this time we can calculate the distance (`Task #2`) between the Ultrasonic sensor and the object in front of it. This distance is evaluated every 0.5 seconds. At a certain distance, a buzzer starts beeping at a certain frequency (`Task #3`). That frequency increase the closer an object is from the sensor. The ultrasonic sensor was implemented using polling methods since the timer interrupts were not functioning properly on our STM32. 

## How to run the scheduler and the implementations : 
